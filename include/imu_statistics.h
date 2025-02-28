#ifndef IMU_STATISTICS_H
#define IMU_STATISTICS_H

#include <vector>
#include "reader.h" // This provides the ImuRecord struct.

// Structure to hold the mean values for each channel.
struct ImuMean {
    double x_gyro;
    double y_gyro;
    double z_gyro;
    double x_accel;
    double y_accel;
    double z_accel;
};

// Structure to hold the variance for each channel.
struct ImuVariance {
    double x_gyro;
    double y_gyro;
    double z_gyro;
    double x_accel;
    double y_accel;
    double z_accel;
};

// Structure to hold the standard deviation for each channel.
struct ImuStd {
    double x_gyro;
    double y_gyro;
    double z_gyro;
    double x_accel;
    double y_accel;
    double z_accel;
};

// Structure to hold the standard deviation for each channel.
struct ImuMeanStd {
    double x_gyro;
    double y_gyro;
    double z_gyro;
    double x_accel;
    double y_accel;
    double z_accel;
};

// Computes the mean for each channel (x_gyro, y_gyro, z_gyro, x_accel, y_accel, z_accel)
// from a vector of ImuRecord in one pass.
ImuMean computeImuMean(const std::vector<ImuRecord>& data);

// Computes the variance for each channel given the data and its mean.
ImuVariance computeImuVariance(const std::vector<ImuRecord>& data, const ImuMean &mean);

// Computes the standard deviation for each channel given the variance.
ImuStd computeImuStd(const ImuVariance &variance);

ImuMeanStd computeImuMeanStd(const ImuStd &std, double data_size);




#endif // IMU_STATISTICS_H
