#include "../core/matrix/bindings.cpp"
#include "../core/fft/bindings.cpp"
#include "../core/stats/bindings.cpp"

static PyMethodDef FastSciMethods[] = {
    // matrix/bindings.cpp
    {"matmul", py_matmul, METH_VARARGS, "Matrix multiplication"},
    {"add_arrays", py_add_arrays, METH_VARARGS, "Add arrays"},
    {"add_scalar", py_add_scalar, METH_VARARGS, "Add scalar to array"},
    {"mul_scalar", py_mul_scalar, METH_VARARGS, "Multiply array by scalar"},
    // fft/bindings.cpp
    {"fft", py_fft, METH_VARARGS, "Compute FFT"},
    // stats/bindings.cpp
    {"mean", py_mean, METH_VARARGS, "Compute mean"},
    {"stddev", py_stddev, METH_VARARGS, "Compute standard deviation"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef fastscimodule = {
    PyModuleDef_HEAD_INIT,
    "fastsci.core",
    NULL,
    -1,
    FastSciMethods
};

PyMODINIT_FUNC PyInit_core(void) {
    return PyModule_Create(&fastscimodule);
}
