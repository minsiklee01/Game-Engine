#pragma once
#include <Python.h>

PyMODINIT_FUNC PyInit_keyboard(void);

PyDoc_STRVAR(engine_keyboard_isKeyPressed_doc,
    ".. function:: isKeyPressed(key)\n"
    "\n"
    "   Returns True if key is pressed.\n"
    "\n"
    "   :return: Bool.\n"
  );
PyObject* isKeyPressed(PyObject *self, PyObject *args);