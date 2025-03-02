#ifndef CORRECTION_H
#define CORRECTION_H

#include "reader.h"      // Defines ImuRecord.
#include "calibration.h" // Defines Bias.
#include <vector>
#include <string>

/**
 * @brief Apply bias correction to raw IMU data.
 *
 * For each measurement record, subtract the bias from the corresponding sensor channels.
 *
 * @param data  The raw IMU data.
 * @param bias  The bias (for both gyro and accel) to subtract.
 * @return std::vector<ImuRecord> The bias-corrected IMU data.
 */
std::vector<ImuRecord> applyBiasCorrection(const std::vector<ImuRecord>& data, const Bias& bias);

/**
 * @brief Write IMU data to a text file.
 *
 * Each row in the file will have 6 space-delimited values:
 * x_gyro y_gyro z_gyro x_accel y_accel z_accel.
 *
 * @param data     The IMU data to write.
 * @param filename The output file name.
 */
void writeImuDataToFile(const std::vector<ImuRecord>& data, const std::string& filename);

#endif // CORRECTION_H
