#include "joystick.h"
#include <SFML/Graphics.hpp>

// joystick function: isConnected

PyDoc_STRVAR(engine_joystick_isconnected_doc,
  ".. function:: isConnected(num)\n"
  "\n"
  "   Returns True if joystick(num) is connected.\n"
  "\n"
  "   :return: Bool.\n"
);

static PyObject* isConnected(PyObject *self, PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if(nargs != 1) {
      // error!
      printf("engine.joystick.isConnected expects 1 int as arguments\n");
      PyErr_BadArgument();
  }
  PyObject *pJoystickNum = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pJoystickNum)) {
      Py_XDECREF(pJoystickNum);
      PyErr_SetString(PyExc_TypeError, "Argument must be an integer");
      PyErr_BadArgument();
  }
  int joystickNum = PyLong_AsLong(pJoystickNum);
 
  if(sf::Joystick::isConnected(joystickNum)) Py_RETURN_TRUE;
  Py_RETURN_FALSE;
}

// joystick function: isButtonPressed

PyDoc_STRVAR(engine_joystick_isButtonPressed_doc,
  ".. function:: isButtonPressed(num, num)\n"
  "\n"
  "   Returns True if joystick(num) button(num) is pressed.\n"
  "\n"
  "   :return: Bool.\n"
);

static PyObject* isButtonPressed(PyObject *self, PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if(nargs != 2) {
      // error!
      printf("engine.joystick.isButtonPressed: expected 2 arguments \n");
      PyErr_BadArgument();
  }
  PyObject *pJoystickNum = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pJoystickNum)) {
      Py_XDECREF(pJoystickNum);
      PyErr_SetString(PyExc_TypeError, "Argument must be an integer");
      PyErr_BadArgument();
  }
  int joystickNum = PyLong_AsLong(pJoystickNum);
  PyObject *pBtnNum = PyTuple_GetItem(args, 1);
  if (!PyLong_Check(pBtnNum)) {
      Py_XDECREF(pBtnNum);
      PyErr_SetString(PyExc_TypeError, "Argument must be an integer");
      PyErr_BadArgument();
  }
  int btnNum = PyLong_AsLong(pBtnNum);
 
  if(sf::Joystick::isButtonPressed(joystickNum, btnNum)) Py_RETURN_TRUE;
  Py_RETURN_FALSE;
}

// joystick function: getAxisPosition

PyDoc_STRVAR(engine_joystick_getAxisPosition_doc,
  ".. function:: getAxisPosition(num, string)\n"
  "\n"
  "   Returns current position of the axis of joystick num.\n"
  "   If the joystick is not connected, this function returns 0.\n"
  "\n"
  "   :return: Current position of the axis, in range [-100 .. 100]\n"
);

static PyObject* getAxisPosition(PyObject *self, PyObject *args) {
  Py_ssize_t nargs = PyTuple_GET_SIZE(args);
  if(nargs != 2) {
      // error!
      printf("engine.joystick.getAxisPosition: expected 2 arguments \n");
      PyErr_BadArgument();
  }
  PyObject *pJoystickNum = PyTuple_GetItem(args, 0);
  if (!PyLong_Check(pJoystickNum)) {
      Py_XDECREF(pJoystickNum);
      PyErr_SetString(PyExc_TypeError, "First argument must be an integer");
      PyErr_BadArgument();
  }
  int joystickNum = PyLong_AsLong(pJoystickNum);
  if (!sf::Joystick::isConnected(joystickNum)) return PyLong_FromLong(0);
  
  PyObject *pAxis = PyTuple_GetItem(args, 1);
  if (!PyUnicode_Check(pAxis)) {
      PyErr_SetString(PyExc_TypeError, "Second argument must be a string");
      return NULL;
  }

  const char* axisName = PyUnicode_AsUTF8(pAxis);
  sf::Joystick::Axis axis;

  if (strcmp(axisName, "x") == 0) {
      axis = sf::Joystick::X;
  } else if (strcmp(axisName, "y") == 0) {
      axis = sf::Joystick::Y;
  } else {
      PyErr_SetString(PyExc_ValueError, "Axis must be 'x' or 'y'");
      return NULL;
  }

  float value = sf::Joystick::getAxisPosition(joystickNum, axis);
  return PyFloat_FromDouble(value);
}

// joystick methods
static PyMethodDef joystick_methods[] = {
  {"isConnected", isConnected, METH_VARARGS, engine_joystick_isconnected_doc},
  {"isButtonPressed", isButtonPressed, METH_VARARGS, engine_joystick_isButtonPressed_doc},
  {"getAxisPosition", getAxisPosition, METH_VARARGS, engine_joystick_getAxisPosition_doc},
  {NULL, NULL, 0, NULL}
};

// joystick definition
static struct PyModuleDef joystick_def = {
  PyModuleDef_HEAD_INIT,
  "joystick",
  NULL,
  -1,
  joystick_methods
};

// joystick initialization function
PyMODINIT_FUNC PyInit_joystick(void) {
  PyObject *joystick;
  joystick = PyModule_Create(&joystick_def);
  if (joystick == NULL)
      return NULL;
  return joystick;
}