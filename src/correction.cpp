#include "correction.h"
#include <fstream>
#include <iostream>
#include <cmath>

std::vector<ImuRecord> correctDownData(const std::vector<ImuRecord> &data,
                                       const Bias &bias,
                                       const Scale &scale)
{
    std::vector<ImuRecord> correctedData;
    correctedData.reserve(data.size());

    for (const auto &rec : data)
    {
        ImuRecord corrected;
        corrected.epoch = rec.epoch; // keep the same timestamp

        // Gyro: true = (measured - bias) / (1 + scale)
        corrected.x_gyro = (rec.x_gyro - bias.x_gyro) / (1.0 + scale.x_gyro);
        corrected.y_gyro = (rec.y_gyro - bias.y_gyro) / (1.0 + scale.y_gyro);
        corrected.z_gyro = (rec.z_gyro - bias.z_gyro) / (1.0 + scale.z_gyro);

        // Accel: same formula
        corrected.x_accel = (rec.x_accel - bias.x_accel) / (1.0 + scale.x_accel);
        corrected.y_accel = (rec.y_accel - bias.y_accel) / (1.0 + scale.y_accel);
        corrected.z_accel = (rec.z_accel - bias.z_accel) / (1.0 + scale.z_accel);

        correctedData.push_back(corrected);
    }
    return correctedData;
}

void writeImuDataToFile(const std::vector<ImuRecord> &data, const std::string &filename)
{
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    for (const auto &rec : data)
    {
        outFile << rec.epoch << " " << rec.x_gyro << " " << rec.y_gyro << " " << rec.z_gyro << " "
                << rec.x_accel << " " << rec.y_accel << " " << rec.z_accel << "\n";
    }
    outFile.close();
}
