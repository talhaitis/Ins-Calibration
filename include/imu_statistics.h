#ifndef IMU_STATISTICS_H
#define IMU_STATISTICS_H

#include <vector>
#include "reader.h" // This provides the ImuRecord struct.

// A structure to hold the mean values for each channel.
struct ImuMean {
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

#endif // IMU_STATISTICS_H
