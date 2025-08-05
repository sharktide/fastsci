#include "main.h"

void add_scalar(const double* a, double scalar, double* out, int size) {
    for (int i = 0; i < size; ++i) {
        out[i] = a[i] + scalar;
    }
}

void mul_scalar(const double* a, double scalar, double* out, int size) {
    for (int i = 0; i < size; ++i) {
        out[i] = a[i] * scalar;
    }
}
