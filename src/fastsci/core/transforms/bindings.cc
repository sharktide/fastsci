#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <vector>
#include "../core.h"

static PyObject* py_fft(PyObject* self, PyObject* args) {
    Py_buffer buf;
    if (!PyArg_ParseTuple(args, "y*", &buf)) return NULL;

    size_t N = buf.len / sizeof(double);
    const double* input = (double*)buf.buf;

    std::vector<double> output_real(N);
    std::vector<double> output_imag(N);

    fft(input, output_real.data(), output_imag.data(), N);

    PyObject* real_list = PyList_New(N);
    PyObject* imag_list = PyList_New(N);
    for (size_t i = 0; i < N; ++i) {
        PyList_SetItem(real_list, i, PyFloat_FromDouble(output_real[i]));
        PyList_SetItem(imag_list, i, PyFloat_FromDouble(output_imag[i]));
    }

    PyBuffer_Release(&buf);
    return PyTuple_Pack(2, real_list, imag_list);
}

static PyMethodDef TransformsMethods[] = {
    {"fft", py_fft, METH_VARARGS, "Compute FFT of array"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef transforms_module = {
    PyModuleDef_HEAD_INIT,
    "fastsci.core.stats",
    "Statistical operations submodule",
    -1,
    TransformsMethods
};

extern "C" PyMODINIT_FUNC PyInit_transforms(void) {
    return PyModule_Create(&transforms_module);
}