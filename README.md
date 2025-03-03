# INS Calibration

This repository contains a project for calibrating inertial sensor data, focusing on **x-axis** measurements for two different sensor types:

1. **MEMS (ADI)** sensor (text files, 100 Hz)
2. **RLG (LN100)** sensor (binary files, 64 Hz)

The calibration involves computing **bias** and **scale factors** for the x-axis **gyroscope** and **accelerometer** using “up” and “down” measurements. Additionally, this repository references the **six-position static test** approach, which is a general method for calibrating all axes by placing the sensor in six orientations.

---
## Six-Position Static Test Method

In the six-position static test, the inertial sensor is placed so that **each sensitive axis** (x, y, z) can be alternately oriented “up” or “down.” By measuring the sensor outputs in these six orientations, you can isolate both the **bias** and **scale factor** for each axis.

### Accelerometer Bias and Scale

- **`Z_up`**: The measured acceleration when the axis is “up” (ideally `-g`).
- **`Z_down`**: The measured acceleration when the axis is “down” (ideally `+g`).
- **`g`**: Gravitational acceleration (≈ 9.81 m/s²).

The bias `b` and scale `S` are computed from:

b = (Z_up + Z_down) / 2

S = [ (Z_down - Z_up ) - 2g ] / (2g)

perl
Copy

### Gyroscope Bias and Scale

- **`omega_up`**: The measured angular rate when the axis is “up.”
- **`omega_down`**: The measured angular rate when the axis is “down.”
- **`omega_e`**: Earth’s rotation in deg/s.
- **`phi`**: The local latitude in radians.

The bias `b_omega` and scale `S_omega` are computed from:

b_omega = (omega_up + omega_down) / 2

S_omega = [ (omega_up - omega_down ) - 2 * omega_e * sin(phi) ] / [ 2 * omega_e * sin(phi) ]

markdown
Copy

By averaging the “up” and “down” measurements, you **isolate the bias**, and by comparing their difference to the expected `2*g` (for accelerometers) or `2 * omega_e * sin(phi)` (for gyroscopes), you **determine the scale factor**.

> **Note**: In this project, we focus on the **x-axis** portion of the six-position static test, but the same logic applies to the y and z axes for a full 3D calibration.
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
---

## Building

Use **CMake**:

```bash
mkdir build
cd build
cmake ..
make
