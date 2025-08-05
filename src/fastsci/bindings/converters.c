#include <Python.h>

int get_double_array(PyObject* obj, double** out, Py_ssize_t* size) {
    Py_buffer view;
    if (PyObject_GetBuffer(obj, &view, PyBUF_SIMPLE) != 0)
        return -1;
    *out = (double*)view.buf;
    *size = view.len / sizeof(double);
    return 0;
}
