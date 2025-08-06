#ifndef FASTSCI_MATMUL_H
#define FASTSCI_MATMUL_H
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void matmul(const double* A, const double* B, double* C, size_t M, size_t N, size_t K);
void add_scalar(const double* a, double scalar, double* out, size_t size);
void mul_scalar(const double* a, double scalar, double* out, size_t size);

#ifdef __cplusplus
}
#endif

#endif
