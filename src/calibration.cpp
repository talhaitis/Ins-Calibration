#include "calibration.h"
#include <cmath>

Bias calculateBias(const ImuMean &meanUp, const ImuMean &meanDown)
{
    Bias sensorBias;
    sensorBias.x_gyro = (meanUp.x_gyro + meanDown.x_gyro) / 2.0;
    sensorBias.y_gyro = (meanUp.y_gyro + meanDown.y_gyro) / 2.0;
    sensorBias.z_gyro = (meanUp.z_gyro + meanDown.z_gyro) / 2.0;

    sensorBias.x_accel = (meanUp.x_accel + meanDown.x_accel) / 2.0;
    sensorBias.y_accel = (meanUp.y_accel + meanDown.y_accel) / 2.0;
    sensorBias.z_accel = (meanUp.z_accel + meanDown.z_accel) / 2.0;

    return sensorBias;
}

Scale calculateScale(const ImuMean &meanUp, const ImuMean &meanDown)
{
    Scale sensorScale;

    // ------------------------------
    // 1) Gyro Scale Calculation
    // ------------------------------
    // Earth’s rotation in deg/hour = 15.041 deg/h
    // Convert to deg/s: 15.041 / 3600 ~ 0.004178 deg/s
    const double earthRotationDegPerSec = 15.041 / 3600.0;

    // Latitude in degrees (example)
    const double latitudeDeg = 51.0784;
    // Convert latitude to radians
    const double latitudeRad = latitudeDeg * M_PI / 180.0;

    // 2 * ω_e * sin(φ)
    const double denomGyro = 2.0 * earthRotationDegPerSec * std::sin(latitudeRad);

    // For each gyro axis: [ (meanUp - meanDown) - 2ω_e sin(φ) ] / [ 2ω_e sin(φ) ]
    sensorScale.x_gyro = ((meanUp.x_gyro - meanDown.x_gyro) - denomGyro) / denomGyro;
    sensorScale.y_gyro = ((meanUp.y_gyro - meanDown.y_gyro) - denomGyro) / denomGyro;
    sensorScale.z_gyro = ((meanUp.z_gyro - meanDown.z_gyro) - denomGyro) / denomGyro;

    // ------------------------------
    // 2) Accelerometer Scale Calculation
    // ------------------------------
    // Gravity in m/s^2
    const double g = 9.81;

    // S = [ (Z_down) - (Z_up) - 2*g ] / [ 2*g ]
    sensorScale.x_accel = ((meanDown.x_accel - meanUp.x_accel) - 2.0 * g) / (2.0 * g);
    sensorScale.y_accel = ((meanDown.y_accel - meanUp.y_accel) - 2.0 * g) / (2.0 * g);
    sensorScale.z_accel = ((meanDown.z_accel - meanUp.z_accel) - 2.0 * g) / (2.0 * g);

    return sensorScale;
}




// Calculate uncertainty in bias.
// For bias = (meanUp + meanDown)/2, uncertainty: σ_bias = 0.5*sqrt(sigmaUp^2 + sigmaDown^2)
Bias calculateBiasUncertainty(const ImuMeanStd &meanStdUp, const ImuMeanStd &meanStdDown)
{
    Bias biasUnc;
    biasUnc.x_gyro  = 0.5 * std::sqrt(meanStdUp.x_gyro  * meanStdUp.x_gyro  + meanStdDown.x_gyro  * meanStdDown.x_gyro);
    biasUnc.y_gyro  = 0.5 * std::sqrt(meanStdUp.y_gyro  * meanStdUp.y_gyro  + meanStdDown.y_gyro  * meanStdDown.y_gyro);
    biasUnc.z_gyro  = 0.5 * std::sqrt(meanStdUp.z_gyro  * meanStdUp.z_gyro  + meanStdDown.z_gyro  * meanStdDown.z_gyro);
    biasUnc.x_accel = 0.5 * std::sqrt(meanStdUp.x_accel * meanStdUp.x_accel + meanStdDown.x_accel * meanStdDown.x_accel);
    biasUnc.y_accel = 0.5 * std::sqrt(meanStdUp.y_accel * meanStdUp.y_accel + meanStdDown.y_accel * meanStdDown.y_accel);
    biasUnc.z_accel = 0.5 * std::sqrt(meanStdUp.z_accel * meanStdUp.z_accel + meanStdDown.z_accel * meanStdDown.z_accel);
    return biasUnc;
}


// Calculate combined scale uncertainty for both accelerometer and gyroscope.
// This function returns a Scale structure, where:
//  - For accelerometer: uncertainty = 1/(2*g)*sqrt(sigmaUp_accel^2 + sigmaDown_accel^2)
//  - For gyroscope: uncertainty = 1/(2*ω_e*sin(latitude))*sqrt(sigmaUp_gyro^2 + sigmaDown_gyro^2)
Scale calculateScaleUncertainty(const ImuMeanStd &meanStdUp, const ImuMeanStd &meanStdDown)
{
    Scale scaleUnc;
    // Accelerometer uncertainty:
    const double g = 9.81;
    const double latitudeDeg = 51.0;
    scaleUnc.x_accel = (1.0 / (2.0 * g)) * std::sqrt((meanStdUp.x_accel * meanStdUp.x_accel) + meanStdDown.x_accel * meanStdDown.x_accel);
    scaleUnc.y_accel = (1.0 / (2.0 * g)) * std::sqrt(meanStdUp.y_accel * meanStdUp.y_accel + meanStdDown.y_accel * meanStdDown.y_accel);
    scaleUnc.z_accel = (1.0 / (2.0 * g)) * std::sqrt(meanStdUp.z_accel * meanStdUp.z_accel + meanStdDown.z_accel * meanStdDown.z_accel);
    
    // Gyroscope uncertainty:
    const double earthRotationDegPerSec = 15.041 / 3600.0;
    double latitudeRad = latitudeDeg * M_PI / 180.0;
    double C = 2.0 * earthRotationDegPerSec * std::sin(latitudeRad);
    scaleUnc.x_gyro = (1.0 / C) * std::sqrt(meanStdUp.x_gyro * meanStdUp.x_gyro + meanStdDown.x_gyro * meanStdDown.x_gyro);
    scaleUnc.y_gyro = (1.0 / C) * std::sqrt(meanStdUp.y_gyro * meanStdUp.y_gyro + meanStdDown.y_gyro * meanStdDown.y_gyro);
    scaleUnc.z_gyro = (1.0 / C) * std::sqrt(meanStdUp.z_gyro * meanStdUp.z_gyro + meanStdDown.z_gyro * meanStdDown.z_gyro);
    
    return scaleUnc;
}

