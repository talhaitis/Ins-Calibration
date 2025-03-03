#include "calibration.h"
#include <stdexcept>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

// Ensure that calibration.h is correct and ends with:
// #endif // CALIBRATION_H

double computeBias(double meanUp, double meanDown)
{
    return (meanUp + meanDown) / 2.0;
}

double computeScale(double meanUp, double meanDown, bool isGyro)
{

    // Global constants for calibration
    const double g = 9.81;                                 // gravitational acceleration (m/s²)
    const double earthRotationDegPerSec = 15.041 / 3600.0; // Earth's rotation in deg/s
    const double latitudeDeg = 51.0784;                    // fixed latitude in degrees
    const double latitudeRad = latitudeDeg * M_PI / 180.0; // latitude in radians
    if (isGyro)
    {
        // Gyro scale: S = ((meanUp - meanDown) - 2*ω_e*sin(φ))/(2*ω_e*sin(φ))
        double denom = 2.0 * earthRotationDegPerSec * std::sin(latitudeRad);
        return ((meanUp - meanDown) - denom) / denom;
    }
    else
    {
        // Accelerometer scale: S = ((meanDown - meanUp) - 2*g)/(2*g)
        return ((meanDown - meanUp) - 2.0 * g) / (2.0 * g);
    }
}

void applyXGyroCalibrationAndSave(const std::vector<double> &rawData,
                                  double bias,
                                  double scale,
                                  bool isDown,
                                  const std::string &outFilename)
{
    std::vector<double> corrected;
    corrected.reserve(rawData.size());

    // For down orientation: corrected = (raw - bias)/(1+scale)
    // For up orientation:   corrected = (bias - raw)/(1+scale)
    for (double raw : rawData)
    {
        double correctedVal = 0.0;
        if (isDown)
            correctedVal = (raw - bias) / (1.0 + scale);
        else
            correctedVal = (bias - raw) / (1.0 + scale);
        corrected.push_back(correctedVal);
    }

    std::ofstream outFile(outFilename);
    if (!outFile.is_open())
    {
        std::cerr << "Error opening file for writing: " << outFilename << std::endl;
        return;
    }
    for (double cVal : corrected)
        outFile << cVal << "\n";
    outFile.close();
    std::cout << "Corrected x-axis gyro data saved to " << outFilename << std::endl;
}

void applyXAccelCalibrationAndSave(const std::vector<double> &rawData,
                                   double bias,
                                   double scale,
                                   bool isDown,
                                   const std::string &outFilename)
{
    std::vector<double> corrected;
    corrected.reserve(rawData.size());

    // For down orientation: corrected = (raw - bias)/(1+scale)
    // For up orientation:   corrected = (bias - raw)/(1+scale)
    for (double raw : rawData)
    {
        double correctedVal = 0.0;
        if (isDown)
            correctedVal = (raw - bias) / (1.0 + scale);
        else
            correctedVal = (bias - raw) / (1.0 + scale);
        corrected.push_back(correctedVal);
    }

    std::ofstream outFile(outFilename);
    if (!outFile.is_open())
    {
        std::cerr << "Error opening file for writing: " << outFilename << std::endl;
        return;
    }
    for (double cVal : corrected)
        outFile << cVal << "\n";
    outFile.close();
    std::cout << "Corrected x-axis accel data saved to " << outFilename << std::endl;
}
