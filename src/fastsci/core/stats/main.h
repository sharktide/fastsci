#ifndef FASTSCI_STATS_H
#define FASTSCI_STATS_H
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

double mean(const double* data, size_t size);

double stddev(const double* data, size_t size);

void add_arrays(const double* a, const double* b, double* out, int size);

#ifdef __cplusplus
}
#endif

#endif
