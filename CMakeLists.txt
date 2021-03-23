cmake_minimum_required(VERSION 2.8.3)
project(sparcslib)

add_compile_options(-std=c++11)

set(EIGEN3_INCLUDE_DIR /usr/include/eigen3)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  gazebo_ros
)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
find_package (gazebo REQUIRED)

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES sparcslib
#  CATKIN_DEPENDS roscpp rospy
  DEPENDS gazebo_ros message_runtime
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${GAZEBO_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
)

link_directories(${GAZEBO_LIBRARY_DIRS})

add_library (sparcsnode SHARED src/sparcsnode.cpp src/kalman_filter.cpp)
target_link_libraries (sparcsnode ${catkin_LIBRARIES})
add_dependencies(sparcsnode ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_library (systems_lib SHARED src/systems.cpp)

add_library(trajectory_printer SHARED src/trajectory_printer.cpp)
target_link_libraries(trajectory_printer ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES})
add_dependencies(trajectory_printer ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_library(movable_object SHARED src/movable_object.cpp)
target_link_libraries(movable_object ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES})
add_dependencies(movable_object ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_library(force_control SHARED src/force_control.cpp)
target_link_libraries(force_control ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES})
add_dependencies(force_control ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(force_control_node src/force_control_node.cpp src/pid.cpp)
target_link_libraries(force_control_node ${catkin_LIBRARIES} sparcsnode)
add_dependencies(force_control_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(uav_pid_ctrl src/uav_pid_ctrl_node.cpp include/controller.cpp src/uav.cpp)
target_link_libraries(uav_pid_ctrl ${catkin_LIBRARIES} sparcsnode systems_lib)
add_dependencies(uav_pid_ctrl ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


### Install

install (DIRECTORY include
    DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
    FILES_MATCHING PATTERN "*.h")

add_subdirectory (src/matlab_gen)






