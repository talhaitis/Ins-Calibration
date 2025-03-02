%% Plot One Axis per Figure for MEMS Down Gyroscope Data

% File path for MEMS Down data (text file)
memsDownFile = 'data/x_adi_down.txt';

% Load the data (assumed to be space‐delimited with 6 columns: 
% [x_gyro, y_gyro, z_gyro, x_accel, y_accel, z_accel])
memsDownData = load(memsDownFile);

% Define the sample rate (100 Hz)
sampleRate = 100;  
numSamples = size(memsDownData, 1);
time = (0:numSamples-1)' / sampleRate;  % time vector in seconds

% Plot the X-axis gyroscope data in its own figure
figure;
plot(memsDownData(:,1), memsDownData(:,2), 'r-', 'LineWidth', 1.5);
xlabel('Time (s)');
ylabel('Gyro X (deg/s)');
title('MEMS Down - Gyroscope X-Axis');

% Plot the Y-axis gyroscope data in its own figure
figure;
plot(memsDownData(:,1), memsDownData(:,3), 'g-', 'LineWidth', 1.5);
xlabel('Time (s)');
ylabel('Gyro Y (deg/s)');
title('MEMS Down - Gyroscope Y-Axis');

% Plot the Z-axis gyroscope data in its own figure
figure;
plot(memsDownData(:,1), memsDownData(:,4), 'b-', 'LineWidth', 1.5);
xlabel('Time (s)');
ylabel('Gyro Z (deg/s)');
title('MEMS Down - Gyroscope Z-Axis');
