#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>

/**
 * @brief Compute the mean of a vector of values.
 */
double computeMean(const std::vector<double>& data);

/**
 * @brief Compute the variance of a vector of values, given the mean.
 */
double computeVariance(const std::vector<double>& data, double mean);

/**
 * @brief Compute the standard deviation from the variance.
 */
double computeStdDev(double variance);

/**
 * @brief Compute the standard error of the mean (mean std dev).
 */
double computeMeanStdDev(double stdDev, size_t n);

#endif // STATISTICS_H
