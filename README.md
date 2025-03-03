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

## Single-Axis Bias and Scale Factor Calculation

This section describes how we compute the **bias** and **scale factor** for the x-axis of both the accelerometer and the gyroscope. The approach assumes we have two sets of mean measurements:

- **`meanUp`**: The average measurement when the sensor axis is oriented “up.”
- **`meanDown`**: The average measurement when the sensor axis is oriented “down.”

---

### Bias

To find the x-axis bias `b`, we take the average of `meanUp` and `meanDown`:

b = (meanUp + meanDown) / 2

yaml
Copy

This formula applies to both the gyroscope and the accelerometer. Essentially, it centers the measurement by assuming that the midpoint between the “up” and “down” readings is the zero-bias reference.

---

### Scale Factor

The scale factor differs for the accelerometer and the gyroscope, because each has a different expected difference between the “up” and “down” orientations.

1. **Accelerometer**  

S_accel = [ (meanDown - meanUp) - 2g ] / (2g)

markdown
Copy
where:
- `g` is gravitational acceleration (≈ 9.81 m/s²),
- `(meanDown - meanUp)` should ideally be `2*g` if there were no scale error.

2. **Gyroscope**  

S_gyro = [ (meanUp - meanDown) - 2 * omega_e * sin(phi) ] / [ 2 * omega_e * sin(phi) ]

markdown
Copy
where:
- `omega_e` is Earth’s rotation rate (in deg/s),
- `phi` is the local latitude (in radians),
- `(meanUp - meanDown)` should ideally be `2 * omega_e * sin(phi)` if there were no scale error.

---

### Correcting Raw Measurements

Once you have `b` (bias) and `S` (scale factor), you can correct any raw measurement `m` using:

- **Down orientation**:
corrected = (m - b) / (1 + S)

markdown
Copy
- **Up orientation**:
corrected = (b - m) / (1 + S)

markdown
Copy

where:
- `m` is the raw measurement (gyro or accel),
- `b` is the computed bias,
- `S` is the computed scale factor,
- “Down” means the sensor axis was oriented so that it should measure +g (for accelerometer) or +earth rotation (for gyroscope),
- “Up” means the sensor axis was oriented the opposite way.

By applying these formulas, you remove the sensor’s bias and adjust for scale errors, resulting in a corrected (“true”) measurement for the x-axis.
----
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
