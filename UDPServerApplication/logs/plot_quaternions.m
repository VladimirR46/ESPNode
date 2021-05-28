clear; clc; close all;

% load actuatorPWM.mat
% load Battery.mat
% load ManualControlSetpoint.mat
% load SensorAccel.mat
% load SensorGyro.mat
% load SensorMag.mat

temp = load("experiment3_new.mat");
imu3 = temp.imu3; 

time = (imu3.time - min(imu3.time))*10^(-6);

% imu3.time = imu3.time * 10^(-9);


% Quaternions
figure('Name', 'IMU Quaternions 1', 'Color', 'w');
plot(time, imu3.q01, ':',  'LineWidth', 2, 'Color', 'r'); hold on;
plot(time, imu3.q11, '--', 'LineWidth', 2, 'Color', 'b');
plot(time, imu3.q21, '-',  'LineWidth', 1, 'Color', 'k');
plot(time, imu3.q31, '-.', 'LineWidth', 3, 'Color', [0.2 0.7 0]);
grid on; grid minor;
ax = gca;
ax.GridAlpha = 0.6;
ax.LineWidth = 0.5;
ax.MinorGridLineStyle = '-';
ax.MinorGridAlpha = 0.2;
ax.FontName = 'Times New Roman';
ax.FontSize = 18;
ax.XLim = [0; max(time)];
xlabel_handle = xlabel('$$t$$, s');
xlabel_handle.Interpreter = 'latex';
ylabel_handle = ylabel('$$q$$');
ylabel_handle.Interpreter = 'latex';
legend_handle = legend('$$q_0$$', '$$q_1$$', '$$q_2$$', '$$q_3$$');
legend_handle.Interpreter = 'latex';


figure('Name', 'IMU Quaternions 2', 'Color', 'w');
plot(time, imu3.q02, ':',  'LineWidth', 2, 'Color', 'r'); hold on;
plot(time, imu3.q12, '--', 'LineWidth', 2, 'Color', 'b');
plot(time, imu3.q22, '-',  'LineWidth', 1, 'Color', 'k');
plot(time, imu3.q32, '-.', 'LineWidth', 3, 'Color', [0.2 0.7 0]);
grid on; grid minor;
ax = gca;
ax.GridAlpha = 0.6;
ax.LineWidth = 0.5;
ax.MinorGridLineStyle = '-';
ax.MinorGridAlpha = 0.2;
ax.FontName = 'Times New Roman';
ax.FontSize = 18;
ax.XLim = [0; max(time)];
xlabel_handle = xlabel('$$t$$, s');
xlabel_handle.Interpreter = 'latex';
ylabel_handle = ylabel('$$q$$');
ylabel_handle.Interpreter = 'latex';
legend_handle = legend('$$q_0$$', '$$q_1$$', '$$q_2$$', '$$q_3$$');
legend_handle.Interpreter = 'latex';


figure('Name', 'IMU Quaternions 3', 'Color', 'w');
plot(time, imu3.q03, ':',  'LineWidth', 2, 'Color', 'r'); hold on;
plot(time, imu3.q13, '--', 'LineWidth', 2, 'Color', 'b');
plot(time, imu3.q23, '-',  'LineWidth', 1, 'Color', 'k');
plot(time, imu3.q33, '-.', 'LineWidth', 3, 'Color', [0.2 0.7 0]);
grid on; grid minor;
ax = gca;
ax.GridAlpha = 0.6;
ax.LineWidth = 0.5;
ax.MinorGridLineStyle = '-';
ax.MinorGridAlpha = 0.2;
ax.FontName = 'Times New Roman';
ax.FontSize = 18;
ax.XLim = [0; max(time)];
xlabel_handle = xlabel('$$t$$, s');
xlabel_handle.Interpreter = 'latex';
ylabel_handle = ylabel('$$q$$');
ylabel_handle.Interpreter = 'latex';
legend_handle = legend('$$q_0$$', '$$q_1$$', '$$q_2$$', '$$q_3$$');
legend_handle.Interpreter = 'latex';
