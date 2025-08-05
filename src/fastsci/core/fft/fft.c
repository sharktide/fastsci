#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "fft.h"
#include <math.h>

#define PI 3.14159265358979323846

void fft(const double* input, double* output_real, double* output_imag, size_t N) {
    for (size_t k = 0; k < N; ++k) {
        double sum_real = 0.0;
        double sum_imag = 0.0;
        for (size_t n = 0; n < N; ++n) {
            double angle = -2.0 * PI * k * n / N;
            sum_real += input[n] * cos(angle);
            sum_imag += input[n] * sin(angle);
        }
        output_real[k] = sum_real;
        output_imag[k] = sum_imag;
    }
}
