clearvars 

%% Model description

mass = 0.01;
g = 9.8;

A = [0, 1; 0, 0];
B = [0; 1/mass];
C = [1, 0];
D = [0];

real_time_factor = 0.1;
Ts = 0.01;

sys = ss (A, B, C, D);

%% Nominal LQR Design


Q = diag ([1, 0.01]);
R = diag ([0.01]);

K = lqr (sys, Q, R);

Nx = blkdiag ([1; 0], [1; 0], [1; 0]);

%% Robust LQR Designs

Ae = [0, C; zeros(2,1), A];
Be = [0; B];
Ce = [0, C];
Qe = blkdiag(10, Q);
sys_e = ss (Ae, Be, Ce, D);
K_robust = lqr (sys_e, Qe, R);

K_i = K_robust(1);
K_pd = K_robust(2:3);
K_tot = blkdiag (K_pd, K_pd, K_pd);

E = eye(6);
reorder_mx = [E(:,1), E(:,3), E(:,5), E(:,2), E(:,4), E(:,6)];



