#ifndef FASTSCI_FFT_H
#define FASTSCI_FFT_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void fft(const double* input, double* output_real, double* output_imag, size_t size);

#ifdef __cplusplus
}
#endif

#endif
