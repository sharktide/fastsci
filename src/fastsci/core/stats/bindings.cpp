#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "../core.h"

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

static PyObject* py_add_arrays(PyObject* self, PyObject* args) {
    Py_buffer a_buf, b_buf;

    if (!PyArg_ParseTuple(args, "y*y*", &a_buf, &b_buf))
        return NULL;

    if (a_buf.len != b_buf.len) {
        PyErr_SetString(PyExc_ValueError, "Input arrays must be the same size");
        PyBuffer_Release(&a_buf);
        PyBuffer_Release(&b_buf);
        return NULL;
    }

    int size = a_buf.len / sizeof(double);
    double* out = (double*)malloc(sizeof(double) * size);
    if (!out) {
        PyBuffer_Release(&a_buf);
        PyBuffer_Release(&b_buf);
        return PyErr_NoMemory();
    }

    add_arrays((double*)a_buf.buf, (double*)b_buf.buf, out, size);

    PyObject* result = PyBytes_FromStringAndSize((const char*)out, sizeof(double) * size);
    free(out);
    PyBuffer_Release(&a_buf);
    PyBuffer_Release(&b_buf);
    return result;
}


static PyMethodDef StatsMethods[] = {
    {"mean", py_mean, METH_VARARGS, "Compute mean of array"},
    {"stddev", py_stddev, METH_VARARGS, "Compute standard deviation"},
    {"add_arrays", py_add_arrays, METH_VARARGS, "Element-wise array addition"},
    {NULL, NULL, 0, NULL}
};
