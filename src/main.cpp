#include "reader.h"            // readTextFile, readBinaryFile
#include "statistics.h"        // computeMean, computeVariance, etc.
#include "calibration.h"       // computeBias, computeScale
#include <iostream>
#include <vector>
#include <string>

int main()
{
    // 1) Create vectors to hold x-axis data for MEMS (ADI) sensor.
    std::vector<ImuRecord> memsDownData, memsUpData;

    // 2) Create vectors to hold x-axis data for RLG (LN100) sensor.
    std::vector<ImuRecord> rlgDownData, rlgUpData;

    // 3) Load the data
    // MEMS text files
    readTextFile("../data/x_adi_down.txt", memsDownData);
    readTextFile("../data/x_adi_up.txt",   memsUpData);

    // RLG binary files
    readBinaryFile("../data/x_LN100_down.ins", rlgDownData);
    readBinaryFile("../data/x_LN100_up.ins",   rlgUpData);

    // ----------------------------
    // MEMS Sensor (ADI) at 100 Hz
    // ----------------------------

    // Extract x-axis gyro & accel into separate vectors for the "down" data
    std::vector<double> memsDownGyro, memsDownAccel;
    for (const auto &rec : memsDownData) {
        memsDownGyro.push_back(rec.x_gyro);
        memsDownAccel.push_back(rec.x_accel);
    }

    // Extract x-axis gyro & accel for the "up" data
    std::vector<double> memsUpGyro, memsUpAccel;
    for (const auto &rec : memsUpData) {
        memsUpGyro.push_back(rec.x_gyro);
        memsUpAccel.push_back(rec.x_accel);
    }

    // Compute means for MEMS x-axis
    double memsDownGyroMean  = computeMean(memsDownGyro);
    double memsUpGyroMean    = computeMean(memsUpGyro);
    double memsDownAccelMean = computeMean(memsDownAccel);
    double memsUpAccelMean   = computeMean(memsUpAccel);

    // (Optionally compute variance, std, etc.)
    // double memsDownGyroVar = computeVariance(memsDownGyro, memsDownGyroMean);
    // double memsDownGyroStd = computeStdDev(memsDownGyroVar);
    // ... similarly for up, accel, etc.

    // Compute single-axis bias & scale for MEMS gyro
    double memsGyroBias  = computeBias(memsUpGyroMean, memsDownGyroMean);
    double memsGyroScale = computeScale(memsUpGyroMean, memsDownGyroMean, /*isGyro=*/true);

    // Compute single-axis bias & scale for MEMS accel
    double memsAccelBias  = computeBias(memsUpAccelMean, memsDownAccelMean);
    double memsAccelScale = computeScale(memsUpAccelMean, memsDownAccelMean, /*isGyro=*/false);

    // Print MEMS results
    std::cout << "MEMS (ADI) X-Axis Calibration:\n";
    std::cout << "  Gyro Bias:  "  << memsGyroBias  << "\n";
    std::cout << "  Gyro Scale: "  << memsGyroScale << "\n";
    std::cout << "  Accel Bias: "  << memsAccelBias << "\n";
    std::cout << "  Accel Scale: " << memsAccelScale << "\n\n";

    // ----------------------------
    // RLG Sensor (LN100) at 64 Hz
    // ----------------------------

    // Extract x-axis gyro & accel into separate vectors for the "down" data
    std::vector<double> rlgDownGyro, rlgDownAccel;
    for (const auto &rec : rlgDownData) {
        rlgDownGyro.push_back(rec.x_gyro);
        rlgDownAccel.push_back(rec.x_accel);
    }

    // Extract x-axis gyro & accel for the "up" data
    std::vector<double> rlgUpGyro, rlgUpAccel;
    for (const auto &rec : rlgUpData) {
        rlgUpGyro.push_back(rec.x_gyro);
        rlgUpAccel.push_back(rec.x_accel);
    }

    // Compute means for RLG x-axis
    double rlgDownGyroMean  = computeMean(rlgDownGyro);
    double rlgUpGyroMean    = computeMean(rlgUpGyro);
    double rlgDownAccelMean = computeMean(rlgDownAccel);
    double rlgUpAccelMean   = computeMean(rlgUpAccel);

    // Compute single-axis bias & scale for RLG gyro
    double rlgGyroBias  = computeBias(rlgUpGyroMean, rlgDownGyroMean);
    double rlgGyroScale = computeScale(rlgUpGyroMean, rlgDownGyroMean, /*isGyro=*/true);

    // Compute single-axis bias & scale for RLG accel
    double rlgAccelBias  = computeBias(rlgUpAccelMean, rlgDownAccelMean);
    double rlgAccelScale = computeScale(rlgUpAccelMean, rlgDownAccelMean, /*isGyro=*/false);

    // Print RLG results
    std::cout << "RLG (LN100) X-Axis Calibration:\n";
    std::cout << "  Gyro Bias:  "  << rlgGyroBias  << "\n";
    std::cout << "  Gyro Scale: "  << rlgGyroScale << "\n";
    std::cout << "  Accel Bias: "  << rlgAccelBias << "\n";
    std::cout << "  Accel Scale: " << rlgAccelScale << "\n";

    applyXGyroCalibrationAndSave(memsDownGyro, memsGyroBias, memsGyroScale, true, "../results/mems_down_gyro_corrected.txt");
    applyXGyroCalibrationAndSave(memsDownAccel, memsAccelBias, memsAccelScale, true, "../results/mems_down_accel_corrected.txt");


    return 0;
}
