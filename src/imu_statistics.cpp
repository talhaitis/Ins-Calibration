#include "imu_statistics.h"
#include <stdexcept>
#include <cmath>

// Compute the mean values of the sensor channels.
ImuMean computeImuMean(const std::vector<ImuRecord>& data)
{
    if (data.empty())
    {
        throw std::invalid_argument("Data vector is empty");
    }

    ImuMean mean = {0, 0, 0, 0, 0, 0};
    for (const auto &rec : data)
    {
        mean.x_gyro  += rec.x_gyro;
        mean.y_gyro  += rec.y_gyro;
        mean.z_gyro  += rec.z_gyro;
        mean.x_accel += rec.x_accel;
        mean.y_accel += rec.y_accel;
        mean.z_accel += rec.z_accel;
    }
    double n = static_cast<double>(data.size());
    mean.x_gyro  /= n;
    mean.y_gyro  /= n;
    mean.z_gyro  /= n;
    mean.x_accel /= n;
    mean.y_accel /= n;
    mean.z_accel /= n;

    return mean;
}

// Compute the variance for each sensor channel.
ImuVariance computeImuVariance(const std::vector<ImuRecord>& data, const ImuMean &mean)
{
    if (data.empty())
    {
        throw std::invalid_argument("Data vector is empty");
    }
    ImuVariance variance = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    for (const auto &rec : data)
    {
        double diff = rec.x_gyro - mean.x_gyro;
        variance.x_gyro += diff * diff;
        
        diff = rec.y_gyro - mean.y_gyro;
        variance.y_gyro += diff * diff;
        
        diff = rec.z_gyro - mean.z_gyro;
        variance.z_gyro += diff * diff;
        
        diff = rec.x_accel - mean.x_accel;
        variance.x_accel += diff * diff;
        
        diff = rec.y_accel - mean.y_accel;
        variance.y_accel += diff * diff;
        
        diff = rec.z_accel - mean.z_accel;
        variance.z_accel += diff * diff;
    }
    double n = static_cast<double>(data.size());
    variance.x_gyro  /= n;
    variance.y_gyro  /= n;
    variance.z_gyro  /= n;
    variance.x_accel /= n;
    variance.y_accel /= n;
    variance.z_accel /= n;

    return variance;
}

// Compute the standard deviation from the variance.
ImuStd computeImuStd(const ImuVariance &variance) {
    ImuStd std;
    std.x_gyro  = std::sqrt(variance.x_gyro);
    std.y_gyro  = std::sqrt(variance.y_gyro);
    std.z_gyro  = std::sqrt(variance.z_gyro);
    std.x_accel = std::sqrt(variance.x_accel);
    std.y_accel = std::sqrt(variance.y_accel);
    std.z_accel = std::sqrt(variance.z_accel);
    return std;
}

ImuMeanStd computeImuMeanStd(const ImuStd &std, double data_size){
    ImuMeanStd meanStd;
    meanStd.x_gyro = std.x_gyro / data_size;
    meanStd.y_gyro = std.y_gyro / data_size;
    meanStd.z_gyro = std.z_gyro / data_size;
    meanStd.x_accel = std.x_accel / data_size;
    meanStd.y_accel = std.y_accel / data_size;
    meanStd.z_accel = std.z_accel / data_size;

    return meanStd;

}