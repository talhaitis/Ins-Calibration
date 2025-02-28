#ifndef READER_H
#define READER_H

#include <string>
#include <vector>


struct ImuRecord {
    double epoch;
    double x_gyro;
    double y_gyro;
    double z_gyro;
    double x_accel;
    double y_accel;
    double z_accel;
};

// Function prototypes for reading IMU data into a vector of ImuRecord
bool readTextFile(const std::string& fileName, std::vector<ImuRecord>& data);
bool readBinaryFile(const std::string& fileName, std::vector<ImuRecord>& data);

#endif // READER_H
