#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <stdexcept>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

/**
 * @brief Structure to hold bias & scale for x-axis gyro & accel.
 */
struct XAxisCalibration
{
    double gyroBias;
    double gyroScale;
    double accelBias;
    double accelScale;
};

/**
 * @brief Compute x-axis bias from up/down means for gyro or accel.
 *
 * For example, bias = (meanUp + meanDown)/2.
 */
double computeBias(double meanUp, double meanDown);

/**
 * @brief Compute x-axis scale from up/down means for gyro or accel.
 *
 * E.g., for accel: scale = ((meanDown - meanUp) - 2*g)/(2*g).
 */
double computeScale(double meanUp, double meanDown, bool isGyro);

/**
 * @brief Apply x-axis calibration correction to a vector of raw measurements and save the corrected values to a file.
 *
 * The correction formula is different for down and up orientations:
 *   If isDown is true (down orientation):
 *     corrected = (raw - bias) / (1 + scale)
 *   If isDown is false (up orientation):
 *     corrected = (bias - raw) / (1 + scale)
 *
 * @param rawData   A vector of raw x-axis measurements.
 * @param bias      The bias for the x-axis.
 * @param scale     The scale factor for the x-axis.
 * @param isDown    true if the data is from the down orientation, false if up.
 * @param outFilename The output file path where the corrected data will be saved.
 */
void applyXGyroCalibrationAndSave(const std::vector<double> &rawData,
                              double bias,
                              double scale,
                              bool isDown,
                              const std::string &outFilename);

                              void applyXAccelCalibrationAndSave(const std::vector<double> &rawData,
                                double bias,
                                double scale,
                                bool isDown,
                                const std::string &outFilename);

#endif // CALIBRATION_H
