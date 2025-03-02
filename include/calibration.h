#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "imu_statistics.h"  // Provides the ImuMean and ImuStd structs
#include <string>
#include <iostream>

// Structure for bias calibration results.
struct Bias {
    double x_gyro;
    double y_gyro;
    double z_gyro;
    double x_accel;
    double y_accel;
    double z_accel;
};

// Structure for scale calibration results.
struct Scale {
    double x_gyro;
    double y_gyro;
    double z_gyro;
    double x_accel;
    double y_accel;
    double z_accel;
};

/**
 * @brief Calculate the bias (for both gyro and accel) as the average of "up" and "down" mean measurements.
 *
 * @param meanUp   Mean measurement in the "up" orientation.
 * @param meanDown Mean measurement in the "down" orientation.
 * @return Bias    The computed bias for each channel.
 */
Bias calculateBias(const ImuMean &meanUp, const ImuMean &meanDown);

/**
 * @brief Calculate the scale factors for both gyro and accelerometer.
 *
 * For gyro:
 *   S_gyro = ((meanUp.gyro - meanDown.gyro) - 2*ω_e*sin(φ)) / (2*ω_e*sin(φ)),
 * where ω_e = 15.041/3600 (deg/s) and φ (latitude) is fixed (here, 51.0784°).
 *
 * For accelerometer:
 *   S_accel = ((meanDown.accel - meanUp.accel) - 2*g) / (2*g),
 * where g = 9.81 m/s².
 *
 * @param meanUp   Mean measurement in the "up" orientation.
 * @param meanDown Mean measurement in the "down" orientation.
 * @return Scale   The computed scale factors for each channel.
 */
Scale calculateScale(const ImuMean &meanUp, const ImuMean &meanDown);

/**
 * @brief Calculate the uncertainty in the bias.
 *
 * For bias = (meanUp + meanDown)/2, the uncertainty is:
 *   σ_bias = 0.5 * sqrt(σ_up² + σ_down²)
 *
 * @param stdUp   Standard deviation (ImuStd) for the "up" measurement.
 * @param stdDown Standard deviation (ImuStd) for the "down" measurement.
 * @return ImuStd The computed uncertainty in the bias for each channel.
 */
Bias calculateBiasUncertainty(const ImuMeanStd &stdMeanUp, const ImuMeanStd &stdMeanDown);

/**
 * @brief Calculate the uncertainty in the scale factors for both accelerometer and gyroscope.
 *
 * For accelerometer:
 *   S_accel = ((Z_down - Z_up) - 2*g) / (2*g)
 * and its uncertainty is:
 *   σ_S_accel = (1/(2*g)) * sqrt(σ_up² + σ_down²)
 *
 * For gyroscope:
 *   S_gyro = ((ω_up - ω_down) - 2*ω_e*sin(φ)) / (2*ω_e*sin(φ))
 * and its uncertainty is:
 *   σ_S_gyro = (1/(2*ω_e*sin(φ))) * sqrt(σ_up² + σ_down²),
 * where ω_e = 15.041/3600 (deg/s) and φ is the latitude (in degrees).
 *
 * @param stdUp   Standard deviation (ImuStd) for the "up" measurement.
 * @param stdDown Standard deviation (ImuStd) for the "down" measurement.
 * @param latitudeDeg Local latitude in degrees (for gyro uncertainty).
 * @return Scale  The computed uncertainty in the scale factors (each field represents σ for that channel).
 */
Scale calculateScaleUncertainty(const ImuMeanStd &stdMeanUp, const ImuMeanStd &stdMeanDown);



#endif // CALIBRATION_H
