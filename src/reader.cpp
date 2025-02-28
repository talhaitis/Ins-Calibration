#include "reader.h"
#include <iostream>
#include <fstream>

bool readTextFile(const std::string &fileName, std::vector<ImuRecord> &data)
{

    std::ifstream infile(fileName);
    if (!infile.is_open())
    {
        std::cerr << "Error: Could not open txt file:" << fileName << "\n";
        return false;
    }
    ImuRecord record;
    // Expect each line to have 6 doubles:
    // x_gyro y_gyro z_gyro x_accel y_accel z_accel

        while (infile >> record.epoch >>record.x_gyro >> record.y_gyro >> record.z_gyro >> record.x_accel >> record.y_accel >> record.z_accel)
        {
            data.push_back(record);
        }

    infile.close();
    return true;
}

bool readBinaryFile(const std::string &fileName, std::vector<ImuRecord> &data)
{
    std::ifstream infile(fileName, std::ios::binary);

    if (!infile.is_open())
    {
        std::cerr << "Error: Could not open txt file:" << fileName << "\n";
        return false;
    }

    ImuRecord record;
    // Read until EOF. Assumes file is just a sequence of ImuRecord structs.
    while (infile.read(reinterpret_cast<char *>(&record), sizeof(ImuRecord)))
    {
        data.push_back(record);
    }

    infile.close();
    return true;
}