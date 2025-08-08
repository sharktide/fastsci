#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "../core.h"
#include "../../bindings/converters.c"
#include "bindings.hpp"
#include "main.h"

static PyObject* py_mean(PyObject* self, PyObject* args) {
    Py_buffer buf;
    if (!PyArg_ParseTuple(args, "y*", &buf)) return NULL;
    double result = mean((double*)buf.buf, buf.len / sizeof(double));
    PyBuffer_Release(&buf);
    return PyFloat_FromDouble(result);
}

static PyObject* py_stddev(PyObject* self, PyObject* args) {
    Py_buffer buf;
    if (!PyArg_ParseTuple(args, "y*", &buf)) return NULL;
    double result = stddev((double*)buf.buf, buf.len / sizeof(double));
    PyBuffer_Release(&buf);
    return PyFloat_FromDouble(result);
}

static PyMethodDef StatsMethods[] = {
    {"mean", py_mean, METH_VARARGS, "Compute mean of array"},
    {"stddev", py_stddev, METH_VARARGS, "Compute standard deviation"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef stats_module = {
    PyModuleDef_HEAD_INIT,
    "fastsci.core.stats",
    "Statistical operations submodule",
    -1,
    StatsMethods
};

extern "C" PyMODINIT_FUNC PyInit_stats(void) {
    return PyModule_Create(&stats_module);
}