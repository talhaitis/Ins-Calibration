# INS Calibration

This repository contains a project for calibrating inertial sensor data, focusing on **x-axis** measurements for two different sensor types:

1. **MEMS (ADI)** sensor (text files, 100 Hz)
2. **RLG (LN100)** sensor (binary files, 64 Hz)

The calibration involves computing **bias** and **scale factors** for the x-axis **gyroscope** and **accelerometer** using “up” and “down” measurements. Additionally, this repository references the **six-position static test** approach, which is a general method for calibrating all axes by placing the sensor in six orientations.

---

## Six-Position Static Test Method

In the six-position static test, the inertial sensor is placed in a level orientation so that each sensitive axis can be alternately oriented “up” or “down.” By measuring the sensor outputs in these six orientations (one for each axis pointing up/down), we can estimate:

- **Accelerometer Bias and Scale**  
  If \(Z_{\text{up}}\) is the measured acceleration when the axis is “up” (ideally \(-g\)) and \(Z_{\text{down}}\) is the measured acceleration when the axis is “down” (ideally \(+g\)), then:

  \[
  b = \frac{Z_{\text{up}} + Z_{\text{down}}}{2}, \quad
  S = \frac{(Z_{\text{down}} - Z_{\text{up}}) - 2g}{2g},
  \]

  where \(b\) is the bias, \(S\) is the scale factor, and \(g\) is the gravitational acceleration (\(\approx 9.81\,\text{m/s}^2\)).

- **Gyroscope Bias and Scale**  
  If \(\omega_{\text{up}}\) is the measured angular rate when the axis is “up” and \(\omega_{\text{down}}\) is the measured rate when the axis is “down,” assuming Earth’s rotation rate \(\omega_e\) and latitude \(\phi\), then:

  \[
  b_{\omega} = \frac{\omega_{\text{up}} + \omega_{\text{down}}}{2}, \quad
  S_{\omega} = \frac{(\omega_{\text{up}} - \omega_{\text{down}}) - 2\,\omega_e\,\sin(\phi)}{2\,\omega_e\,\sin(\phi)}.
  \]

This test allows you to isolate the **bias** (by averaging up/down) and the **scale factor** (by seeing how the measured difference compares to the expected \(2g\) for accelerometers or \(2\omega_e\sin(\phi)\) for gyroscopes).

In this project, we **focus on the x-axis** portion of that approach, though the code can be extended to full 3D (six positions total) if needed.

---

## Single-Axis Model and Formulas

For the x-axis, we use:

- **Bias**:  
  \[
  b = \frac{\text{meanUp} + \text{meanDown}}{2}.
  \]

- **Scale (Accelerometer)**:  
  \[
  S_{\text{accel}} = \frac{(\text{meanDown} - \text{meanUp}) - 2g}{2g}.
  \]

- **Scale (Gyroscope)**:  
  \[
  S_{\omega} = \frac{(\text{meanUp} - \text{meanDown}) - 2\,\omega_e\,\sin(\phi)}{2\,\omega_e\,\sin(\phi)},
  \]
  where \(\omega_e\) is Earth’s rotation in deg/s and \(\phi\) is latitude in radians.

**Correction**:  
Once \(b\) and \(S\) are known, raw measurements \(m\) can be corrected as:
- **Down**: \(\text{true} = \frac{m - b}{1 + S}\)
- **Up**:   \(\text{true} = \frac{b - m}{1 + S}\)

---

## Repository Branches

- **general-six-position-static**  
  This branch contains a more general approach suitable for a six-position test, potentially calibrating all axes (x, y, z).

- **x-axis-calibration**  
  This branch is strictly focused on **x-axis** calibration. It reads data from “x_up” and “x_down” files, computes bias and scale, and applies corrections only to the x-axis channels for both the gyroscope and accelerometer.

---

## Directory Structure

INS Calibration/ ├── CMakeLists.txt ├── data/ │ ├── x_adi_down.txt # MEMS sensor "down" data (text) │ ├── x_adi_up.txt # MEMS sensor "up" data (text) │ ├── x_LN100_down.ins # RLG sensor "down" data (binary) │ └── x_LN100_up.ins # RLG sensor "up" data (binary) ├── include/ │ ├── reader.h # File-reading functions │ ├── statistics.h # Single-axis statistics (mean, variance, etc.) │ └── calibration.h # Single-axis bias/scale formulas & correction ├── src/ │ ├── reader.cpp # Implementation of readTextFile / readBinaryFile │ ├── statistics.cpp # Implementation of computeMean, etc. │ ├── calibration.cpp # Implementation of bias/scale & correction │ └── main.cpp # Main program orchestrating everything └── results/ # Output folder for corrected data files



---

## Building

Use **CMake**:

```bash
mkdir build
cd build
cmake ..
make
