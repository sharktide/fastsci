#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "../core/matrix/bindings.hpp"
#include "../core/transforms/bindings.hpp"
#include "../core/stats/bindings.hpp"


// Forward declarations for submodules
extern PyObject* PyInit_matrix(void);
extern PyObject* PyInit_stats(void);
extern PyObject* PyInit_fft(void);

static struct PyModuleDef coremodule = {
    PyModuleDef_HEAD_INIT,
    "fastsci.core",
    NULL,
    -1,
    NULL
};

PyMODINIT_FUNC PyInit_core(void) {
    PyObject* core = PyModule_Create(&coremodule);
    if (!core) return NULL;

    PyObject* matrix = PyInit_matrix();
    PyObject* stats  = PyInit_stats();
    PyObject* transforms = PyInit_transforms();

    if (!matrix || !stats || !transforms) return NULL;

    PyModule_AddObject(core, "matrix", matrix);
    PyModule_AddObject(core, "stats", stats);
    PyModule_AddObject(core, "transforms", transforms);

    return core;
}
