#include "statistics.h"
#include <stdexcept>
#include <cmath>

double computeMean(const std::vector<double>& data)
{
    if (data.empty()) {
        throw std::invalid_argument("Data is empty.");
    }
    double sum = 0.0;
    for (double val : data) {
        sum += val;
    }
    return sum / data.size();
}

double computeVariance(const std::vector<double>& data, double mean)
{
    if (data.empty()) {
        throw std::invalid_argument("Data is empty.");
    }
    double sumSq = 0.0;
    for (double val : data) {
        double diff = val - mean;
        sumSq += diff * diff;
    }
    return sumSq / data.size();
}

double computeStdDev(double variance)
{
    return std::sqrt(variance);
}

double computeMeanStdDev(double stdDev, size_t n)
{
    if (n == 0) {
        throw std::invalid_argument("n must be > 0.");
    }
    return stdDev / std::sqrt(static_cast<double>(n));
}
