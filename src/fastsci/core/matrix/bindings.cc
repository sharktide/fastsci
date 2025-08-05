#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "../core.h"

static PyObject* py_matmul(PyObject* self, PyObject* args) {
    Py_buffer a_buf, b_buf;
    Py_ssize_t M, N, K;

    if (!PyArg_ParseTuple(args, "y*y*nnn", &a_buf, &b_buf, &M, &N, &K))
        return NULL;

    if (a_buf.len != M * N * sizeof(double) || b_buf.len != N * K * sizeof(double)) {
        PyErr_SetString(PyExc_ValueError, "Input buffer sizes do not match dimensions");
        PyBuffer_Release(&a_buf);
        PyBuffer_Release(&b_buf);
        return NULL;
    }

    double* C = (double*)malloc(sizeof(double) * M * K);
    if (!C) {
        PyBuffer_Release(&a_buf);
        PyBuffer_Release(&b_buf);
        return PyErr_NoMemory();
    }

    matmul((double*)a_buf.buf, (double*)b_buf.buf, C, M, N, K);

    PyObject* result = PyBytes_FromStringAndSize((const char*)C, sizeof(double) * M * K);
    free(C);
    PyBuffer_Release(&a_buf);
    PyBuffer_Release(&b_buf);
    return result;
}

static PyObject* py_add_scalar(PyObject* self, PyObject* args) {
    Py_buffer a_buf;
    double scalar;

    if (!PyArg_ParseTuple(args, "y*d", &a_buf, &scalar))
        return NULL;

    int size = a_buf.len / sizeof(double);
    double* out = (double*)malloc(sizeof(double) * size);
    if (!out) {
        PyBuffer_Release(&a_buf);
        return PyErr_NoMemory();
    }

    add_scalar((double*)a_buf.buf, scalar, out, size);

    PyObject* result = PyBytes_FromStringAndSize((const char*)out, sizeof(double) * size);
    free(out);
    PyBuffer_Release(&a_buf);
    return result;
}

static PyObject* py_mul_scalar(PyObject* self, PyObject* args) {
    Py_buffer a_buf;
    double scalar;

    if (!PyArg_ParseTuple(args, "y*d", &a_buf, &scalar))
        return NULL;

    int size = a_buf.len / sizeof(double);
    double* out = (double*)malloc(sizeof(double) * size);
    if (!out) {
        PyBuffer_Release(&a_buf);
        return PyErr_NoMemory();
    }

    mul_scalar((double*)a_buf.buf, scalar, out, size);

    PyObject* result = PyBytes_FromStringAndSize((const char*)out, sizeof(double) * size);
    free(out);
    PyBuffer_Release(&a_buf);
    return result;
}

static PyMethodDef MatrixMethods[] = {
    {"matmul", py_matmul, METH_VARARGS, "Matrix multiplication"},
    {"add_scalar", py_add_scalar, METH_VARARGS, "Add scalar to array"},
    {"mul_scalar", py_mul_scalar, METH_VARARGS, "Multiply array by scalar"},
    {NULL, NULL, 0, NULL}
};
