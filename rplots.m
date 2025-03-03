%% Plot Raw vs. Bias-Corrected MEMS Down Data for Gyro X-Axis (Using Sample Index)
% This script loads the raw and bias-corrected MEMS down data files, each with 7 columns.
% It then plots the Gyro X-axis data (column 2) versus sample index.

%% Load Raw Data
rawFile = 'data/x_adi_down.txt';  % Ensure the file path and extension are correct.
rawData = load(rawFile);          % rawData is assumed to be numeric with 7 columns.

% Use sample index as the x-axis (ignore column 1)
sampleIndex = (1:size(rawData, 1))';

% Extract Gyro X-axis data (column 2)
rawGyroX = rawData(:,2);

% Plot raw Gyro X data
figure;
plot(sampleIndex, rawGyroX, 'r-', 'LineWidth', 1.5);
xlabel('Sample Number');
ylabel('Gyro X (deg/s)');
title('Raw MEMS Down - Gyro X-Axis');
grid on;

%% Load Bias-Corrected Data
correctedFile = 'results/x_adi_down_corrected.txt';  % Ensure the file path and extension are correct.
correctedData = load(correctedFile);  % Assumes same format: 7 columns per row.

% Use sample index for corrected data
sampleIndexCorrected = (1:size(correctedData, 1))';

% Extract Gyro X-axis data (column 2)
correctedGyroX = correctedData(:,2);

% Plot bias-corrected Gyro X data
figure;
plot(sampleIndexCorrected, correctedGyroX, 'b-', 'LineWidth', 1.5);
xlabel('Sample Number');
ylabel('Gyro X (deg/s)');
title('Bias-Corrected MEMS Down - Gyro X-Axis');
grid on;
