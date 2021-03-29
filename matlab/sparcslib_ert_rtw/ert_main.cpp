//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ert_main.cpp
//
// Code generated for Simulink model 'sparcslib'.
//
// Model version                  : 1.4
// Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
// C/C++ source code generated on : Tue Sep 17 15:55:55 2019
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Emulation hardware selection:
//    Differs from embedded hardware (MATLAB Host)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include <stdio.h>
#include <stdlib.h>
#include "sparcslib.h"
#include "sparcslib_private.h"
#include "rtwtypes.h"
#include "limits.h"
#include "linuxinitialize.h"
#include "MW_custom_RTOS_header.h"
#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "std_msgs/String.h"
#include "rosgraph_msgs/Clock.h"
#define UNUSED(x)                      x = x

void ROS_myRTOSInit(double baseRatePeriod, int numSubrates);
static void publishDone(bool status);
volatile boolean_T runModel = true;
sem_t stopSem;
sem_t termSem;
sem_t baserateTaskSem;
pthread_t terminateThread;
pthread_t schedulerThread;
pthread_t baseRateThread;
unsigned long threadJoinStatus[8];
int terminatingmodel = 0;
int subratePriority[0];

// Base rate task
void *baseRateTask(void *arg)
{
  runModel = (rtmGetErrorStatus(sparcslib_M) == (NULL));
  while (runModel) {
    sem_wait(&baserateTaskSem);
    runModel = (rtmGetErrorStatus(sparcslib_M) == (NULL));
    if (runModel) {
      sparcslib_step();

      // Get model outputs here
      publishDone(true);
    }
  }

  sem_post(&termSem);
  pthread_exit((void *)0);
}

void exitTask(int sig)
{
  switch (sig){
   case SIGINT:
    ROS_WARN("Ctrl-C detected...");
    break;

   case SIGTERM:
    ROS_WARN("Programm killed...");
    break;

   case SIGUSR1:                       // Missing time slot
    break;

   default:
    ROS_WARN("Programm received signal %d", sig);
    break;
  }

  rtmSetErrorStatus(sparcslib_M, "stopping the model");
  sem_post(&baserateTaskSem);
}

void *terminateTask(void *arg)
{
  int i;
  int ret;
  sem_wait(&termSem);
  terminatingmodel = 1;
  printf("** Terminating the model \"%s\" **\n", "sparcslib");
  fflush(stdout);

  // Wait for baseRate task to complete
  ret = pthread_join(baseRateThread, (void**)&threadJoinStatus);
  CHECK_STATUS(ret, 0, "pthread_join");

  // Disable rt_OneStep() here

  // Terminate model
  sparcslib_terminate();

  // Shutdown the ROS
  ros::shutdown();
  sem_post(&stopSem);
  return NULL;
}

int main(int argc, char **argv)
{
  void slros_node_init(int argc, char** argv);
  slros_node_init(argc, argv);
  printf("** Starting the model \"%s\" **\n", "sparcslib");
  fflush(stdout);
  rtmSetErrorStatus(sparcslib_M, 0);

  // Initialize model
  sparcslib_initialize();
  ROS_myRTOSInit(0.01, 0);

  // Wait for stop semaphore
  sem_wait(&stopSem);
  return 0;
}

// ----------------------------
// RTOS-specific declarations
// ----------------------------
typedef struct {
  double period;
} baseRateInfo_t;

extern pthread_attr_t attr;
extern baseRateInfo_t info;
extern struct sched_param sp;

// MW_NUM_SUBRATES is set to 0 if we are in single-tasking mode or number of subrates are 0 
#define MW_SP_SCHED_FIFO               ((MW_NUMBER_SUBRATES > 0) || !defined(MW_SCHED_OTHER))
#ifdef MW_RTOS_DEBUG
#define MW_DEBUG_LOG(str)              printf(str); fflush(stdout)
#else
#define MW_DEBUG_LOG(str)
#endif

static volatile bool modelRuns;
static int overrunCnt;

// Global variables to be accessed from the model
uint32_t _clock_msg_sec;
uint32_t _clock_msg_nsec;

// ----------------------------
// Internally visible functions
// ----------------------------
static void setThreadPriority(const int priority, pthread_attr_t *attr, struct
  sched_param *sp)
{

#if MW_SP_SCHED_FIFO

  int status;
  sp->sched_priority = priority;
  status = pthread_attr_setschedparam(attr, sp);
  CHECK_STATUS(status, 0, "pthread_attr_setschedparam");

#endif

}

static void publishDone(bool status)
{
  static std_msgs::String msg;
  if (status == false) {               // Publish name of the model name
    msg.data = "-sparcslib";
  } else {
    msg.data = "+sparcslib";
  }

  publisherDone.publish(msg);
  if (status == true) {
    modelRuns = false;
  }
}

static void SubscriberCB(const rosgraph_msgs::Clock &msg)
{
  static bool termFlag = false;
  static bool waitingFlag = false;
  static int stateFlag = 1;
  const uint32_t baseRateNanoSec = (uint32_t)(MW_BASERATE_PERIOD * 1E9);
  static uint64_t nextTimeSlot = baseRateNanoSec;
  uint64_t longTime;
  if ((1 == stateFlag) && (0U != msg.clock.nsec) ) {
    ROS_INFO("Waiting for time synchronization at time %u.000000000",
             msg.clock.sec + 1U);
  }

  if (false != termFlag) {
    return;
  }

  longTime = ((uint64_t)msg.clock.sec * 1000000000ULL) + (uint64_t)
    msg.clock.nsec;

  // Check if time fits into model steps
  if ((0 == stateFlag) && (true == waitingFlag) ) {
    if (longTime > nextTimeSlot) {
      fflush(stdout);
      ROS_FATAL("The clock missed time slot at %f for the model step. Actual clock = %.6f\n",
                nextTimeSlot/1E9, (double)longTime/1E9);
      fflush(stderr);
      exitTask(SIGUSR1);
      termFlag = true;
      return;
    }
  }

  // Store into global variable published clock topic
  _clock_msg_sec = msg.clock.sec;
  _clock_msg_nsec = msg.clock.nsec;

  // Starting the model code at time of "nsec" at 0ns
  if (false == waitingFlag) {
    if (0U == msg.clock.nsec) {
      waitingFlag = true;
      ROS_INFO("It's %.6f, here we go ...", (double)longTime/1E9);
      modelRuns = true;
      sem_post(&baserateTaskSem);      // Launch for first time
      nextTimeSlot = longTime + baseRateNanoSec;
    } else {
      // Check if there was not termination in the meantime
      runModel = (rtmGetErrorStatus(sparcslib_M) == (NULL));
      if (runModel == false) {
        termFlag = true;
      } else {
      }
    }
  } else {
    if ((msg.clock.nsec % baseRateNanoSec) == 0U) {
      // Overrun check
      if (false != modelRuns) {
        overrunCnt++;
        ROS_ERROR("Overrun %d", overrunCnt);
      }

      modelRuns = true;
      sem_post(&baserateTaskSem);
      nextTimeSlot += baseRateNanoSec;
    } else {
    }
  }

  if (stateFlag > 0) {
    stateFlag--;
  }
}

void *ROSschedulerTask(void *arg)
{
  MW_DEBUG_LOG("ROS schedulerTask entered\n");
  std::string sClockTopic = "/clock";
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe(sClockTopic, 10, &SubscriberCB);
  if (sub == NULL) {
    ROS_INFO("Error: cannot subscribe the '%s'", sClockTopic.c_str());
    return NULL;
  }

  ros::spin();
  return NULL;
}

void ROS_myRTOSInit(double baseRatePeriod, int numSubrates)
{
  int i;
  int status;
  size_t stackSize;
  unsigned long cpuMask = 0x1;
  unsigned int len = sizeof(cpuMask);
  if (!MW_IS_CONCURRENT) {
    // All threads created by this process will run on a single CPU
    status = sched_setaffinity(0, len, (cpu_set_t *) &cpuMask);
    CHECK_STATUS(status, 0, "sched_setaffinity");
  }

#if MW_SP_SCHED_FIFO && !defined (_POSIX_THREAD_PRIORITY_SCHEDULING)

  fprintf(stderr, "Priority scheduling is NOT supported by your system.\n");
  fprintf(stderr, "The generated code will not run correctly because your\n");
  fprintf(stderr, "model contains multiple rates and uses multi-tasking\n");
  fprintf(stderr, "code generation mode. You can only run the generated code\n");
  fprintf(stderr, "in single-tasking mode in your system. Open\n");
  fprintf(stderr, "Simulation -> Configuration Parameters -> Solver dialog\n");
  fprintf(stderr,
          "and set \"Tasking mode for periodic sample times\" parameter to SingleTasking.\n");
  fprintf(stderr,
          "Re-build the Simulink model with the new settings and try executing the generated code again.\n");
  fflush(stderr);
  exit(EXIT_FAILURE);

#endif

#if MW_SP_SCHED_FIFO

  // Need root privileges for real-time scheduling
  {
    uid_t euid = geteuid();
    if (euid != 0) {
      fprintf(stderr,
              "You must have root privileges to run the generated code because\n");
      fprintf(stderr,
              "generated code requires SCHED_FIFO scheduling class to run correctly.\n");
      fprintf(stderr,
              "Try running the executable with the following command: sudo ./<executable name>\n");
      fflush(stderr);
      exit(EXIT_FAILURE);
    }
  }

#endif

  status = sem_init(&baserateTaskSem, 0, 0);
  CHECK_STATUS(status, 0, "sem_init:baserateTaskSemSem");
  status = sem_init(&stopSem, 0, 0);
  CHECK_STATUS(status, 0, "sem_init:stopSem");
  status = sem_init(&termSem, 0, 0);
  CHECK_STATUS(status, 0, "sem_init:termSem");

#if MW_SP_SCHED_FIFO

  // Set scheduling policy of the main thread to SCHED_FIFO
  sp.sched_priority = sched_get_priority_max(SCHED_FIFO);
  status = sched_setscheduler(0, SCHED_FIFO, &sp);
  CHECK_STATUS(status, 0, "sched_setscheduler");

#endif

  // Create threads executing the Simulink model
  pthread_attr_init(&attr);
  status = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
  CHECK_STATUS(status, 0, "pthread_attr_setinheritsched");

#if MW_SP_SCHED_FIFO

  status = pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

#else

  status = pthread_attr_setschedpolicy(&attr, SCHED_OTHER);

#endif

  CHECK_STATUS(status, 0, "pthread_attr_setschedpolicy");
  status = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  CHECK_STATUS(status, 0, "pthread_attr_setdetachstate");

  // Set thread stack size if necessary
  status = pthread_attr_getstacksize(&attr, &stackSize);
  CHECK_STATUS(status, 0, "pthread_attr_getstacksize");
  if (stackSize < STACK_SIZE) {
    // Make sure that stackSize is a multiple of 8
    stackSize = (STACK_SIZE + 7) & (~0x7);
    pthread_attr_setstacksize(&attr, stackSize);
    CHECK_STATUS(status, 0, "pthread_attr_setstacksize");
  }

  signal(SIGTERM, exitTask);           // kill
  signal(SIGHUP, exitTask);            // kill -HUP
  signal(SIGINT, exitTask);            // Interrupt from keyboard Ctr-C
  signal(SIGQUIT, exitTask);           // Quit from keyboard

#ifdef MW_HAS_MULTIPLE_RATES

  MW_DEBUG_LOG("**creating subrate task threads**\n");
  for (i = 0; i < MW_NUMBER_SUBRATES; i++) {
    taskId[i] = i;
    status = sem_init(&subrateTaskSem[i], 0, 0);
    CHECK_STATUS(status, 0, "sem_init");
    setThreadPriority(subratePriority[i], &attr, &sp);
    status = pthread_create(&subRateThread[i], &attr, (void *) subrateTask,
      (void *)&taskId[i]);
    CHECK_STATUS(status, 0, "pthread_create");

#ifdef COREAFFINITYREQUIRED

    if (coreAffinity[i] >= 0) {
      cpu_set_t cpuset;
      CPU_ZERO(&cpuset);
      CPU_SET(coreAffinity[i], &cpuset);
      ret = pthread_setaffinity_np(subRateThread[i], sizeof(cpu_set_t), &cpuset);
      CHECK_STATUS(ret, "pthread_setaffinity_np");
    }

#endif

  }

#endif

  MW_DEBUG_LOG("**creating the base rate task thread**\n");
  setThreadPriority(MW_BASERATE_PRIORITY, &attr, &sp);
  status = pthread_create(&baseRateThread, &attr, &baseRateTask, NULL);
  CHECK_STATUS(status, 0, "pthread_create");
  MW_DEBUG_LOG("**creating the terminate thread**\n");
  setThreadPriority(MW_BASERATE_PRIORITY, &attr, &sp);
  status = pthread_create(&terminateThread, &attr, &terminateTask, NULL);
  CHECK_STATUS(status, 0, "pthread_create");
  MW_DEBUG_LOG("**creating the scheduler thread**\n");
  setThreadPriority(MW_BASERATE_PRIORITY, &attr, &sp);
  info.period = MW_BASERATE_PERIOD;
  status = pthread_create(&schedulerThread, &attr, &ROSschedulerTask, (void *)
    &info);
  CHECK_STATUS(status, 0, "pthread_create");

#ifdef MW_HAS_APERIODIC_TASKS

  MW_DEBUG_LOG("**creating asynchronously triggered task threads**\n");
  sp.sched_priority = MW_BASERATE_PRIORITY - 1;
  for (i = 0; i < MW_NUMBER_APERIODIC_TASKS; i++) {
    status = pthread_create(&asyncThread[i], &attr, (void *) pAsyncTasks[i],
      NULL);
    CHECK_STATUS(status, 0, "pthread_create");
  }

#endif

#ifdef MW_NEEDS_BACKGROUND_TASK

  MW_DEBUG_LOG("**creating the background thread**\n");
  status = pthread_attr_setschedpolicy(&attr, SCHED_OTHER);
  CHECK_STATUS(status, 0, "pthread_attr_setschedpolicy");
  setThreadPriority(0, &attr, &sp);
  status = pthread_create(&backgroundThread, &attr, (void *) backgroundTask,
    NULL);
  CHECK_STATUS(status, 0, "pthread_create");

#endif

  pthread_attr_destroy(&attr);
  fflush(stdout);
}

//
// File trailer for generated code.
//
// [EOF]
//
