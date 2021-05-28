clear; clc; close all;

%% legend
% 1 - time 

%% IMU 1
% 2 - ax1
% 3 - ay1
% 4 - az1
% 5 - gx1
% 6 - gy1
% 7 - gz1
% 8 - mx1
% 9 - my1
% 10 - mz1
% 11 - q0
% 12 - q1
% 13 - q2
% 14 - q3
% 15 - Yaw1
% 16 - Pitch1
% 17 - Roll1
%% IMU 2
% 18 - ax2
% 19 - ay2
% 20 - az2
% 21 - gx2
% 22 - gy2
% 23 - gz2
% 24 - mx2
% 25 - my2
% 26 - mz2
% 27 - q0
% 28 - q1
% 29 - q2
% 30 - q3
% 31 - Yaw2
% 32 - Pitch2
% 33 - Roll2
%% IMU 3
% 34 - ax3
% 35 - ay3
% 36 - az3
% 37 - gx3
% 38 - gy3
% 39 - gz3
% 40 - mx3
% 41 - my3
% 42 - mz3
% 43 - q0
% 44 - q1
% 45 - q2
% 46 - q3
% 47 - Yaw3
% 48 - Pitch3
% 49 - Roll3
%%

temp = load("0-Module1.txt");
imu1 = temp.imu3; 

time = (imu3.time - min(imu3.time))*10^(-6);

% imu3.time = imu3.time * 10^(-9);


% Acceleration
figure('Name', 'IMU Acceleration 1', 'Color', 'w');
subplot(3, 1, 1);
plot(time, imu3.ax1, '-',  'LineWidth', 1, 'Color', 'k'); hold on;
grid on; grid minor;
ax = gca;
ax.GridAlpha = 0.6;
ax.LineWidth = 0.5;
ax.MinorGridLineStyle = '-';
ax.MinorGridAlpha = 0.2;
ax.FontName = 'Times New Roman';
ax.FontSize = 14;
ax.XLim = [0; max(time)];
ax.YLim = [min([imu3.ax1; imu3.ay1; imu3.az1]); max([imu3.ax1; imu3.ay1; imu3.az1])];
xlabel_handle = xlabel('$$t$$, s');
xlabel_handle.Interpreter = 'latex';
ylabel_handle = ylabel('$$a$$, m/s$$^2$$');
ylabel_handle.Interpreter = 'latex';
legend_handle = legend('$$a_x$$');
legend_handle.Interpreter = 'latex';

subplot(3, 1, 2);
plot(time, imu3.ay1, '-',  'LineWidth', 1, 'Color', 'r');
grid on; grid minor;
ax = gca;
ax.GridAlpha = 0.6;
ax.LineWidth = 0.5;
ax.MinorGridLineStyle = '-';
ax.MinorGridAlpha = 0.2;
ax.FontName = 'Times New Roman';
ax.FontSize = 14;
ax.XLim = [0; max(time)];
ax.YLim = [min([imu3.ax1; imu3.ay1; imu3.az1]); max([imu3.ax1; imu3.ay1; imu3.az1])];
xlabel_handle = xlabel('$$t$$, s');
xlabel_handle.Interpreter = 'latex';
ylabel_handle = ylabel('$$a$$, m/s$$^2$$');
ylabel_handle.Interpreter = 'latex';
legend_handle = legend('$$a_y$$');
legend_handle.Interpreter = 'latex';

subplot(3, 1, 3);
plot(time, imu3.az1, '-',  'LineWidth', 1, 'Color', 'b');
grid on; grid minor;
ax = gca;
ax.GridAlpha = 0.6;
ax.LineWidth = 0.5;
ax.MinorGridLineStyle = '-';
ax.MinorGridAlpha = 0.2;
ax.FontName = 'Times New Roman';
ax.FontSize = 14;
ax.XLim = [0; max(time)];
ax.YLim = [min([imu3.ax1; imu3.ay1; imu3.az1]); max([imu3.ax1; imu3.ay1; imu3.az1])];
xlabel_handle = xlabel('$$t$$, s');
xlabel_handle.Interpreter = 'latex';
ylabel_handle = ylabel('$$a$$, m/s$$^2$$');
ylabel_handle.Interpreter = 'latex';
legend_handle = legend('$$a_z$$');
legend_handle.Interpreter = 'latex';

