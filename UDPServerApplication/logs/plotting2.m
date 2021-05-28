load experiment3_FULL.mat


%time = (imu3.time - min(imu3.time))*10^(-6);

%% Acceleration
figure('Name','IMU (Acceleration)');
subplot(3,1,1);
plot(imu3.time,imu3.ax1,imu3.time,imu3.ay1,imu3.time,imu3.az1,'LineWidth',3);
title('Acceleration (imu sensor_{1})');
xlabel('time (microsec)');
ylabel('[m/s^2]');
legend('a_x','a_y','a_z');
subplot(3,1,2);
plot(imu3.time,imu3.ax2,imu3.time,imu3.ay2,imu3.time,imu3.az2,'LineWidth',3);
title('Acceleration (imu sensor_{2})');
xlabel('time (microsec)');
ylabel('[m/s^2]');
legend('a_x','a_y','a_z');
subplot(3,1,3);
plot(imu3.time,imu3.ax3,imu3.time,imu3.ay3,imu3.time,imu3.az3,'LineWidth',3);
title('Acceleration (imu sensor_{3})');
xlabel('time (microsec)');
ylabel('[m/s^2]');
legend('a_x','a_y','a_z');

%% Speed
figure('Name','IMU (Speed)');
subplot(3,1,1);
plot(imu3.time,imu3.gx1,imu3.time,imu3.gy1,imu3.time,imu3.gz1,'LineWidth',3);
title('Speed (imu sensor_{1})');
xlabel('time (microsec)');
ylabel('[deg/s]');
legend('g_x','g_y','g_z');
subplot(3,1,2);
plot(imu3.time,imu3.gx2,imu3.time,imu3.gy2,imu3.time,imu3.gz2,'LineWidth',3);
title('Speed (imu sensor_{2})');
xlabel('time (microsec)');
ylabel('[deg/s]');
legend('g_x','g_y','g_z');
subplot(3,1,3);
plot(imu3.time,imu3.gx3,imu3.time,imu3.gy3,imu3.time,imu3.gz3,'LineWidth',3);
title('Speed (imu sensor_{3})');
xlabel('time (microsec)');
ylabel('[deg/s]');
legend('g_x','g_y','g_z');
grid on;

%% Magnetic
figure('Name','IMU (Magnetic)');
subplot(3,1,1);
plot(imu3.time,imu3.mx1,imu3.time,imu3.my1,imu3.time,imu3.mz1,'LineWidth',3);
title('Magnetic (imu sensor_{1})');
xlabel('time (microsec)');
ylabel('[gauss]');
legend('m_x','m_y','m_z');
subplot(3,1,2);
plot(imu3.time,imu3.mx2,imu3.time,imu3.my2,imu3.time,imu3.mz2,'LineWidth',3);
title('Magnetic (imu sensor_{2})');
xlabel('time (microsec)');
ylabel('[gauss]');
legend('m_x','m_y','m_z');
subplot(3,1,3);
plot(imu3.time,imu3.mx3,imu3.time,imu3.my3,imu3.time,imu3.mz3,'LineWidth',3);
title('Magnetic (imu sensor_{3})');
xlabel('time (microsec)');
ylabel('[gauss]');
legend('m_x','m_y','m_z');
grid on;

%% Quaternions
figure('Name','IMU (Quaternions)');
subplot(3,1,1);
plot(imu3.time,imu3.q01,imu3.time,imu3.q11,imu3.time,imu3.q21,imu3.time,imu3.q31,'LineWidth',3);
title('Quaternions (imu sensor_{1})');
xlabel('time (microsec)');
ylabel('radians');
legend('q_0','q_1','q_2','q_3');
subplot(3,1,2);
plot(imu3.time,imu3.q02,imu3.time,imu3.q12,imu3.time,imu3.q22,imu3.time,imu3.q32,'LineWidth',3);
title('Quaternions (imu sensor_{2})');
xlabel('time (microsec)');
ylabel('radians');
legend('q_0','q_1','q_2','q_3');
subplot(3,1,3);
plot(imu3.time,imu3.q03,imu3.time,imu3.q13,imu3.time,imu3.q23,imu3.time,imu3.q33,'LineWidth',3);
title('Quaternions (imu sensor_{3})');
xlabel('time (microsec)');
ylabel('radians');
legend('q_0','q_1','q_2','q_3');


%% Euler Angles
figure('Name','IMU (Euler Angles)');
subplot(3,1,1);
plot(imu3.time,imu3.Yaw1,imu3.time,imu3.Pitch1,imu3.time,imu3.Roll1,'LineWidth',3);
title('Imu sensor_{2}');
xlabel('time (microsec)');
ylabel('degrees');
legend('Yaw','Pitch','Roll');
subplot(3,1,2);
plot(imu3.time,imu3.Yaw2,imu3.time,imu3.Pitch2,imu3.time,imu3.Roll2,'LineWidth',3);
title('Imu sensor_{2}');
xlabel('time (microsec)');
ylabel('degrees');
legend('Yaw','Pitch','Roll');
subplot(3,1,3);
plot(imu3.time,imu3.Yaw3,imu3.time,imu3.Pitch3,imu3.time,imu3.Roll3,'LineWidth',3);
title('Imu sensor_{3}');
xlabel('time (microsec)');
ylabel('degrees');
legend('Yaw','Pitch','Roll');

