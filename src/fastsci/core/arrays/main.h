#ifndef FASTSCI_ARRAYS_H
#define FASTSCI_ARRAYS_H
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void add_arrays(const double* a, const double* b, double* out, int size);

#ifdef __cplusplus
}
#endif

#endif
