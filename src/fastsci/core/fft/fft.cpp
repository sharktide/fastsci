#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "main.h"
#include <complex>
#include <cmath>
#include <vector>
#include <stddef.h>

constexpr double PI = 3.141592653589793238462643383279502884;

extern "C" void fft(const double* input, double* output_real, double* output_imag, size_t N) {
    std::complex<double>* X = new std::complex<double>[N];
    for (size_t k = 0; k < N; ++k) {
        std::complex<double> sum(0.0, 0.0);
        for (size_t n = 0; n < N; ++n) {
            double angle = -2.0 * PI * k * n / N;
            sum += std::polar(input[n], angle);
        }
        X[k] = sum;
    }
    for (size_t i = 0; i < N; ++i) {
        output_real[i] = X[i].real();
        output_imag[i] = X[i].imag();
    }
    delete[] X;
}

