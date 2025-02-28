#include "reader.h"
#include "imu_statistics.h"
#include <iostream>
#include <vector>
#include <fstream>

int main()
{
    // Create vectors to hold the data from each file.
    std::vector<ImuRecord> xAdiDown, xAdiUp;
    std::vector<ImuRecord> xLN100Down, xLN100Up;

    // Load the data from each file.
    // (Ensure the file paths are correct relative to your build/working directory.)
    readTextFile("../data/x_adi_down.txt", xAdiDown);
    readTextFile("../data/x_adi_up.txt", xAdiUp);
    readBinaryFile("../data/x_LN100_down.ins", xLN100Down);
    readBinaryFile("../data/x_LN100_up.ins", xLN100Up);

    // Compute the means for each file.
    ImuMean adiDownMean, adiUpMean, ln100DownMean, ln100UpMean;

    try
    {
        // Compute the means for each file.
        adiDownMean = computeImuMean(xAdiDown);
        adiUpMean = computeImuMean(xAdiUp);
        ln100DownMean = computeImuMean(xLN100Down);
        ln100UpMean = computeImuMean(xLN100Up);

        // Print the computed means to the console.
        std::cout << "ADI Down Mean:" << std::endl;
        std::cout << "  Gyro:  (" << adiDownMean.x_gyro << ", "
                  << adiDownMean.y_gyro << ", " << adiDownMean.z_gyro << ")" << std::endl;
        std::cout << "  Accel: (" << adiDownMean.x_accel << ", "
                  << adiDownMean.y_accel << ", " << adiDownMean.z_accel << ")" << std::endl;

        std::cout << "\nADI Up Mean:" << std::endl;
        std::cout << "  Gyro:  (" << adiUpMean.x_gyro << ", "
                  << adiUpMean.y_gyro << ", " << adiUpMean.z_gyro << ")" << std::endl;
        std::cout << "  Accel: (" << adiUpMean.x_accel << ", "
                  << adiUpMean.y_accel << ", " << adiUpMean.z_accel << ")" << std::endl;

        std::cout << "\nLN100 Down Mean:" << std::endl;
        std::cout << "  Gyro:  (" << ln100DownMean.x_gyro << ", "
                  << ln100DownMean.y_gyro << ", " << ln100DownMean.z_gyro << ")" << std::endl;
        std::cout << "  Accel: (" << ln100DownMean.x_accel << ", "
                  << ln100DownMean.y_accel << ", " << ln100DownMean.z_accel << ")" << std::endl;

        std::cout << "\nLN100 Up Mean:" << std::endl;
        std::cout << "  Gyro:  (" << ln100UpMean.x_gyro << ", "
                  << ln100UpMean.y_gyro << ", " << ln100UpMean.z_gyro << ")" << std::endl;
        std::cout << "  Accel: (" << ln100UpMean.x_accel << ", "
                  << ln100UpMean.y_accel << ", " << ln100UpMean.z_accel << ")" << std::endl;

        // Write the computed means to separate files in the results folder.
        {
            std::ofstream outFile("../results/ADI_Down_Mean.txt");
            if (outFile.is_open())
            {
                outFile << "ADI Down Mean:\n";
                outFile << "Gyro:  (" << adiDownMean.x_gyro << ", "
                        << adiDownMean.y_gyro << ", " << adiDownMean.z_gyro << ")\n";
                outFile << "Accel: (" << adiDownMean.x_accel << ", "
                        << adiDownMean.y_accel << ", " << adiDownMean.z_accel << ")\n";
                outFile.close();
            }
            else
            {
                std::cerr << "Error opening output file for ADI Down Mean." << std::endl;
            }
        }

        {
            std::ofstream outFile("../results/ADI_Up_Mean.txt");
            if (outFile.is_open())
            {
                outFile << "ADI Up Mean:\n";
                outFile << "Gyro:  (" << adiUpMean.x_gyro << ", "
                        << adiUpMean.y_gyro << ", " << adiUpMean.z_gyro << ")\n";
                outFile << "Accel: (" << adiUpMean.x_accel << ", "
                        << adiUpMean.y_accel << ", " << adiUpMean.z_accel << ")\n";
                outFile.close();
            }
            else
            {
                std::cerr << "Error opening output file for ADI Up Mean." << std::endl;
            }
        }

        {
            std::ofstream outFile("../results/LN100_Down_Mean.txt");
            if (outFile.is_open())
            {
                outFile << "LN100 Down Mean:\n";
                outFile << "Gyro:  (" << ln100DownMean.x_gyro << ", "
                        << ln100DownMean.y_gyro << ", " << ln100DownMean.z_gyro << ")\n";
                outFile << "Accel: (" << ln100DownMean.x_accel << ", "
                        << ln100DownMean.y_accel << ", " << ln100DownMean.z_accel << ")\n";
                outFile.close();
            }
            else
            {
                std::cerr << "Error opening output file for LN100 Down Mean." << std::endl;
            }
        }

        {
            std::ofstream outFile("../results/LN100_Up_Mean.txt");
            if (outFile.is_open())
            {
                outFile << "LN100 Up Mean:\n";
                outFile << "Gyro:  (" << ln100UpMean.x_gyro << ", "
                        << ln100UpMean.y_gyro << ", " << ln100UpMean.z_gyro << ")\n";
                outFile << "Accel: (" << ln100UpMean.x_accel << ", "
                        << ln100UpMean.y_accel << ", " << ln100UpMean.z_accel << ")\n";
                outFile.close();
            }
            else
            {
                std::cerr << "Error opening output file for LN100 Up Mean." << std::endl;
            }
        }
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error computing mean: " << e.what() << std::endl;
        return 1;
    }

    ImuVariance adiDownVariance = computeImuVariance(xAdiDown, adiDownMean);
    ImuVariance adiUpVariance = computeImuVariance(xAdiUp, adiUpMean);
    ImuVariance ln100DownVariance = computeImuVariance(xLN100Down, ln100DownMean);
    ImuVariance ln100UpVariance = computeImuVariance(xLN100Up, ln100UpMean);

    std::cout << "ADI Down Variance:" << std::endl;
    std::cout << "  Gyro:  (" << adiDownVariance.x_gyro << ", "
              << adiDownVariance.y_gyro << ", " << adiDownVariance.z_gyro << ")" << std::endl;
    std::cout << "  Accel: (" << adiDownVariance.x_accel << ", "
              << adiDownVariance.y_accel << ", " << adiDownVariance.z_accel << ")" << std::endl;

    std::cout << "\nADI Up Variance:" << std::endl;
    std::cout << "  Gyro:  (" << adiUpVariance.x_gyro << ", "
              << adiUpVariance.y_gyro << ", " << adiUpVariance.z_gyro << ")" << std::endl;
    std::cout << "  Accel: (" << adiUpVariance.x_accel << ", "
              << adiUpVariance.y_accel << ", " << adiUpVariance.z_accel << ")" << std::endl;

    std::cout << "\nLN100 Down Variance:" << std::endl;
    std::cout << "  Gyro:  (" << ln100DownVariance.x_gyro << ", "
              << ln100DownVariance.y_gyro << ", " << ln100DownVariance.z_gyro << ")" << std::endl;
    std::cout << "  Accel: (" << ln100DownVariance.x_accel << ", "
              << ln100DownVariance.y_accel << ", " << ln100DownVariance.z_accel << ")" << std::endl;

    std::cout << "\nLN100 Up Variance:" << std::endl;
    std::cout << "  Gyro:  (" << ln100UpVariance.x_gyro << ", "
              << ln100UpVariance.y_gyro << ", " << ln100UpVariance.z_gyro << ")" << std::endl;
    std::cout << "  Accel: (" << ln100UpVariance.x_accel << ", "
              << ln100UpVariance.y_accel << ", " << ln100UpVariance.z_accel << ")" << std::endl;

    ImuStd adiDownStd = computeImuStd(adiDownVariance);
    ImuStd adiUpStd= computeImuStd(adiUpVariance);
    ImuStd ln100DownStd= computeImuStd(ln100DownVariance);
    ImuStd ln100UpStd = computeImuStd(ln100UpVariance);


    std::cout << "ADI Down Standard Deviation:" << std::endl;
    std::cout << "  Gyro:  (" << adiDownStd.x_gyro << ", "
              << adiDownStd.y_gyro << ", " << adiDownStd.z_gyro << ")" << std::endl;
    std::cout << "  Accel: (" << adiDownStd.x_accel << ", "
              << adiDownStd.y_accel << ", " << adiDownStd.z_accel << ")" << std::endl;

    std::cout << "\nADI Up Standard Deviation:" << std::endl;
    std::cout << "  Gyro:  (" << adiUpStd.x_gyro << ", "
              << adiUpStd.y_gyro << ", " << adiUpStd.z_gyro << ")" << std::endl;
    std::cout << "  Accel: (" << adiUpStd.x_accel << ", "
              << adiUpStd.y_accel << ", " << adiUpStd.z_accel << ")" << std::endl;

    std::cout << "\nLN100 Down Standard Deviation:" << std::endl;
    std::cout << "  Gyro:  (" << ln100DownStd.x_gyro << ", "
              << ln100DownStd.y_gyro << ", " << ln100DownStd.z_gyro << ")" << std::endl;
    std::cout << "  Accel: (" << ln100DownStd.x_accel << ", "
              << ln100DownStd.y_accel << ", " << ln100DownStd.z_accel << ")" << std::endl;

    std::cout << "\nLN100 Up Standard Deviation:" << std::endl;
    std::cout << "  Gyro:  (" << ln100UpStd.x_gyro << ", "
              << ln100UpStd.y_gyro << ", " << ln100UpStd.z_gyro << ")" << std::endl;
    std::cout << "  Accel: (" << ln100UpStd.x_accel << ", "
              << ln100UpStd.y_accel << ", " << ln100UpStd.z_accel << ")" << std::endl;

    

    return 0;
}
