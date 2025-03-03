# INS Calibration

This repository contains a project for calibrating inertial sensor data. The project focuses on calibrating the **x-axis** measurements for two different sensor types:

- **MEMS (ADI)** sensor (sampled at 100 Hz, provided as text files)
- **RLG (LN100)** sensor (sampled at 64 Hz, provided as binary files)

Calibration involves computing the bias and scale factors for both the gyroscope and the accelerometer along the x-axis using "up" and "down" measurements.

## Project Overview

The sensor measurement model used in the calibration is as follows:

### Bias Calculation

For both sensors, the bias is calculated as the average of the "up" and "down" mean values:
\[
b = \frac{\text{meanUp} + \text{meanDown}}{2}
\]

### Scale Factor Calculation

The formulas differ for the accelerometer and the gyroscope:

- **Accelerometer:**

  In the down orientation, the accelerometer is expected to measure approximately \(+g\) (where \(g = 9.81\, \text{m/s}^2\)), while in the up orientation, it should measure approximately \(-g\). The scale factor is computed as:
  \[
  S_{\text{accel}} = \frac{(\text{meanDown} - \text{meanUp}) - 2g}{2g}
  \]
  
- **Gyroscope:**

  For the gyroscope, the expected difference is based on Earth’s rotation. If \(\omega_e\) is the Earth’s rotation rate in deg/s (converted from 15.041°/hour) and \(\phi\) is the local latitude, then the scale factor is computed as:
  \[
  S_{\omega} = \frac{(\text{meanUp} - \text{meanDown}) - 2\,\omega_e\,\sin(\phi)}{2\,\omega_e\,\sin(\phi)}
  \]
  where:
  - \(\omega_e = \frac{15.041}{3600}\) deg/s,
  - \(\phi\) is in degrees (converted to radians for the sine function).

### Correction of Raw Measurements

To correct a raw measurement \(m\) using the computed bias \(b\) and scale factor \(S\), the following formula is applied:

- **For the Down Orientation:**
  \[
  \text{corrected} = \frac{m - b}{1 + S}
  \]
- **For the Up Orientation:**
  \[
  \text{corrected} = \frac{b - m}{1 + S}
  \]

## Repository Branches

- **general-six-position-static:**  
  This branch contains a general implementation that supports six-position, full 3D calibration. It is useful if you later decide to extend your calibration to all axes.

- **x-axis-calibration:**  
  This branch is dedicated to the assignment requirements and implements calibration **only** for the x-axis of the gyroscope and accelerometer. All computations, statistics (mean, variance, standard deviation, etc.), and corrections are applied solely to the x-axis data.

## Project Structure

