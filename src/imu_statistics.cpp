#include "imu_statistics.h"
#include <stdexcept>

ImuMean computeImuMean(const std::vector<ImuRecord>& data) {
    if (data.empty()) {
        throw std::invalid_argument("Data vector is empty");
    }
    
    ImuMean mean = {0, 0, 0, 0, 0, 0};
    for (const auto& rec : data) {
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
