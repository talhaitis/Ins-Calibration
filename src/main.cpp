#include "reader.h"         // Provides ImuRecord and readTextFile/readBinaryFile.
#include "imu_statistics.h" // Provides computeImuMean(), computeImuVariance(), computeImuStd(), etc.
#include "calibration.h"    // Provides calculateBias() and calculateScale().
#include "correction.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

//---------------------------------------------------------------------
// Template function for printing any IMU-like struct.
// The struct must have these public fields:
//   x_gyro, y_gyro, z_gyro, x_accel, y_accel, z_accel.
//---------------------------------------------------------------------
template <typename T>
void printImuData(const T &data, const std::string &label, const std::string &dataType)
{
    std::cout << label << " " << dataType << ":\n";
    std::cout << "  Gyro:  (" << data.x_gyro << ", "
              << data.y_gyro << ", " << data.z_gyro << ")\n";
    std::cout << "  Accel: (" << data.x_accel << ", "
              << data.y_accel << ", " << data.z_accel << ")\n";
}

//---------------------------------------------------------------------
// Helper function to write an ImuMean to a file.
//---------------------------------------------------------------------
void writeImuMeanToFile(const ImuMean &data, const std::string &label,
                        const std::string &filename)
{
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Error opening output file: " << filename << std::endl;
        return;
    }
    outFile << label << " " << "Mean:\n";
    outFile << "  Gyro:  (" << data.x_gyro << ", "
            << data.y_gyro << ", " << data.z_gyro << ")\n";
    outFile << "  Accel: (" << data.x_accel << ", "
            << data.y_accel << ", " << data.z_accel << ")\n";
    outFile.close();
}

//---------------------------------------------------------------------
// Main program
//---------------------------------------------------------------------
int main()
{
    // 1) Create vectors to hold data from each file.
    // MEMS (ADI) sensor at 100 Hz:
    std::vector<ImuRecord> memsDownData, memsUpData;
    // RLG (LN100) sensor at 64 Hz:
    std::vector<ImuRecord> rlgDownData, rlgUpData;

    // 2) Load the data (ensure the file paths are correct).
    readTextFile("../data/x_adi_down.txt", memsDownData);
    readTextFile("../data/x_adi_up.txt", memsUpData);
    readBinaryFile("../data/x_LN100_down.ins", rlgDownData);
    readBinaryFile("../data/x_LN100_up.ins", rlgUpData);

    // 3) Compute the means for each file.
    ImuMean memsDownMean, memsUpMean, rlgDownMean, rlgUpMean;
    try
    {
        memsDownMean = computeImuMean(memsDownData);
        memsUpMean = computeImuMean(memsUpData);
        rlgDownMean = computeImuMean(rlgDownData);
        rlgUpMean = computeImuMean(rlgUpData);

        // 4) Print means to console using our template function.
        printImuData(memsDownMean, "MEMS Down", "Mean");
        std::cout << std::endl;
        printImuData(memsUpMean, "MEMS Up", "Mean");
        std::cout << std::endl;
        printImuData(rlgDownMean, "RLG Down", "Mean");
        std::cout << std::endl;
        printImuData(rlgUpMean, "RLG Up", "Mean");
        std::cout << std::endl;

        // 5) Write means to files in the results folder.
        writeImuMeanToFile(memsDownMean, "MEMS Down", "../results/MEMS_Down_Mean.txt");
        writeImuMeanToFile(memsUpMean, "MEMS Up", "../results/MEMS_Up_Mean.txt");
        writeImuMeanToFile(rlgDownMean, "RLG Down", "../results/RLG_Down_Mean.txt");
        writeImuMeanToFile(rlgUpMean, "RLG Up", "../results/RLG_Up_Mean.txt");
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error computing mean: " << e.what() << std::endl;
        return 1;
    }

    // 6) Compute variance and standard deviation.
    ImuVariance memsDownVar = computeImuVariance(memsDownData, memsDownMean);
    ImuVariance memsUpVar = computeImuVariance(memsUpData, memsUpMean);
    ImuVariance rlgDownVar = computeImuVariance(rlgDownData, rlgDownMean);
    ImuVariance rlgUpVar = computeImuVariance(rlgUpData, rlgUpMean);

    ImuStd memsDownStd = computeImuStd(memsDownVar);
    ImuStd memsUpStd = computeImuStd(memsUpVar);
    ImuStd rlgDownStd = computeImuStd(rlgDownVar);
    ImuStd rlgUpStd = computeImuStd(rlgUpVar);

    // 7) Print variance and standard deviation.
    printImuData(memsDownVar, "MEMS Down", "Variance");
    std::cout << std::endl;
    printImuData(memsUpVar, "MEMS Up", "Variance");
    std::cout << std::endl;
    printImuData(rlgDownVar, "RLG Down", "Variance");
    std::cout << std::endl;
    printImuData(rlgUpVar, "RLG Up", "Variance");
    std::cout << std::endl;

    printImuData(memsDownStd, "MEMS Down", "Std Dev");
    std::cout << std::endl;
    printImuData(memsUpStd, "MEMS Up", "Std Dev");
    std::cout << std::endl;
    printImuData(rlgDownStd, "RLG Down", "Std Dev");
    std::cout << std::endl;
    printImuData(rlgUpStd, "RLG Up", "Std Dev");
    std::cout << std::endl;

    // 8) Compute Mean Std

    ImuMeanStd memsDownMeanStd = computeImuMeanStd(memsDownStd, memsDownData.size());
    ImuMeanStd memsUpMeanStd = computeImuMeanStd(memsUpStd, memsUpData.size()) ;
    ImuMeanStd rlgDownMeanStd = computeImuMeanStd(rlgDownStd, rlgDownData.size());
    ImuMeanStd rlgUpMeanStd = computeImuMeanStd(rlgUpStd, rlgUpData.size());


    printImuData(memsDownMeanStd, "MEMS Down", "Mean Std Dev");
    std::cout << std::endl;
    printImuData(memsUpMeanStd, "MEMS Up", "Mean Std Dev");
    std::cout << std::endl;
    printImuData(rlgDownMeanStd, "RLG Down", "Mean Std Dev");
    std::cout << std::endl;
    printImuData(rlgUpMeanStd, "RLG Up", "Mean Std Dev");
    std::cout << std::endl;

    // 9) Compute calibration parameters (Bias and Scale) for both sensors.
    Bias memsBias = calculateBias(memsUpMean, memsDownMean);
    Scale memsScale = calculateScale(memsUpMean, memsDownMean);

    Bias rlgBias = calculateBias(rlgUpMean, rlgDownMean);
    Scale rlgScale = calculateScale(rlgUpMean, rlgDownMean);

    // 10) Print calibration results.
    printImuData(memsBias, "MEMS", "Bias");
    std::cout << std::endl;
    printImuData(memsScale, "MEMS", "Scale");
    std::cout << std::endl;

    printImuData(rlgBias, "RLG", "Bias");
    std::cout << std::endl;
    printImuData(rlgScale, "RLG", "Scale");
    std::cout << std::endl;

    // 9) Bias and Scale Uncertainity
    Bias memesBiasUnc = calculateBiasUncertainty(memsUpMeanStd, memsDownMeanStd);
    Scale memesScaleUnc = calculateScaleUncertainty(memsUpMeanStd, memsDownMeanStd);

    Bias rlgBiasUnc = calculateBiasUncertainty(rlgUpMeanStd, rlgDownMeanStd);
    Scale rlgScaleUnc = calculateScaleUncertainty(rlgUpMeanStd, rlgDownMeanStd);

    printImuData(memesBiasUnc, "MEMs Bias Uncertainity", "Bias Uncertainity");
    std::cout << std::endl;
    printImuData(memesScaleUnc, "MEMs Scale Uncertainity", "Scale Uncertanity");
    std::cout << std::endl;


    printImuData(rlgBiasUnc, "RLG Bias Uncertainity", "Bias Uncertainity");
    std::cout << std::endl;
    printImuData(rlgScaleUnc, "RLG Scale Uncertainity", "Scale Uncertainity");
    std::cout << std::endl;


    std::vector<ImuRecord> correctedData = correctDownData(memsDownData, memsBias, memsScale);

    // Write the corrected data to a new file.
    writeImuDataToFile(correctedData, "../results/x_adi_down_corrected.txt");

    // Optionally, print a message.
    std::cout << "Bias correction applied and results saved to ../results/x_adi_down_corrected.txt\n";


    return 0;
}
