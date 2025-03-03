#ifndef CORRECTION_H
#define CORRECTION_H

#include "reader.h"      // Defines ImuRecord.
#include "calibration.h" // Defines Bias.
#include <vector>
#include <string>

std::vector<ImuRecord> correctDownData(const std::vector<ImuRecord> &data,
                                       const Bias &bias,
                                       const Scale &scale);
void writeImuDataToFile(const std::vector<ImuRecord> &data, const std::string &filename);

#endif // CORRECTION_H
