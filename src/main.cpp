#include "reader.h"
#include "imu_statistics.h"
#include <iostream>
#include <vector>
#include <fstream>

int main() {
    // Create vectors to hold the data from each file.
    std::vector<ImuRecord> xAdiDown, xAdiUp;
    std::vector<ImuRecord> xLN100Down, xLN100Up;

    // Load the data from each file.
    // (Ensure the file paths are correct relative to your build/working directory.)
    readTextFile("../data/x_adi_down.txt", xAdiDown);
    readTextFile("../data/x_adi_up.txt",   xAdiUp);
    readBinaryFile("../data/x_LN100_down.ins", xLN100Down);
    readBinaryFile("../data/x_LN100_up.ins",   xLN100Up);

    try {
        // Compute the means for each file.
        ImuMean adiDownMean   = computeImuMean(xAdiDown);
        ImuMean adiUpMean     = computeImuMean(xAdiUp);
        ImuMean ln100DownMean = computeImuMean(xLN100Down);
        ImuMean ln100UpMean   = computeImuMean(xLN100Up);

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
            if (outFile.is_open()) {
                outFile << "ADI Down Mean:\n";
                outFile << "Gyro:  (" << adiDownMean.x_gyro << ", " 
                        << adiDownMean.y_gyro << ", " << adiDownMean.z_gyro << ")\n";
                outFile << "Accel: (" << adiDownMean.x_accel << ", " 
                        << adiDownMean.y_accel << ", " << adiDownMean.z_accel << ")\n";
                outFile.close();
            } else {
                std::cerr << "Error opening output file for ADI Down Mean." << std::endl;
            }
        }
        
        {
            std::ofstream outFile("../results/ADI_Up_Mean.txt");
            if (outFile.is_open()) {
                outFile << "ADI Up Mean:\n";
                outFile << "Gyro:  (" << adiUpMean.x_gyro << ", " 
                        << adiUpMean.y_gyro << ", " << adiUpMean.z_gyro << ")\n";
                outFile << "Accel: (" << adiUpMean.x_accel << ", " 
                        << adiUpMean.y_accel << ", " << adiUpMean.z_accel << ")\n";
                outFile.close();
            } else {
                std::cerr << "Error opening output file for ADI Up Mean." << std::endl;
            }
        }
        
        {
            std::ofstream outFile("../results/LN100_Down_Mean.txt");
            if (outFile.is_open()) {
                outFile << "LN100 Down Mean:\n";
                outFile << "Gyro:  (" << ln100DownMean.x_gyro << ", " 
                        << ln100DownMean.y_gyro << ", " << ln100DownMean.z_gyro << ")\n";
                outFile << "Accel: (" << ln100DownMean.x_accel << ", " 
                        << ln100DownMean.y_accel << ", " << ln100DownMean.z_accel << ")\n";
                outFile.close();
            } else {
                std::cerr << "Error opening output file for LN100 Down Mean." << std::endl;
            }
        }
        
        {
            std::ofstream outFile("../results/LN100_Up_Mean.txt");
            if (outFile.is_open()) {
                outFile << "LN100 Up Mean:\n";
                outFile << "Gyro:  (" << ln100UpMean.x_gyro << ", " 
                        << ln100UpMean.y_gyro << ", " << ln100UpMean.z_gyro << ")\n";
                outFile << "Accel: (" << ln100UpMean.x_accel << ", " 
                        << ln100UpMean.y_accel << ", " << ln100UpMean.z_accel << ")\n";
                outFile.close();
            } else {
                std::cerr << "Error opening output file for LN100 Up Mean." << std::endl;
            }
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error computing mean: " << e.what() << std::endl;
        return 1;
    }

    // Now you can use these mean values to compute bias and scale factors for each sensor axis.
    return 0;
}
