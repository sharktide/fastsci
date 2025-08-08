#include <math.h>
#include "main.h"
#include <stddef.h>
double mean(const double* data, size_t size) {
    double sum = 0.0;
    for (size_t i = 0; i < size; ++i)
        sum += data[i];
    return sum / size;
}

double stddev(const double* data, size_t size) {
    double avg = mean(data, size);
    double sum_sq = 0.0;
    for (size_t i = 0; i < size; ++i)
        sum_sq += (data[i] - avg) * (data[i] - avg);
    return sqrt(sum_sq / size);
}
