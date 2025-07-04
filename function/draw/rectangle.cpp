#include "rectangle.h"
#include <SFML/Graphics.hpp>

extern sf::RenderWindow *window;
extern sf::CircleShape *circle;
extern sf::RectangleShape *rect;

// FUNC: draw
PyDoc_STRVAR(engine_rectangle_draw_doc,
  ".. function:: draw(x,y,w,h)\n"
  "\n"
  "   Draws a rectangle relative to top-left (x,y) with width w and height h in the window.\n"
  "\n"
  "   :return: None.\n"
);

static PyObject* draw(PyObject *self, PyObject *args) {
  int x, y, w, h;

  if (!PyArg_ParseTuple(args, "iiii", &x, &y, &w, &h)) {
      PyErr_SetString(PyExc_TypeError, "Expected 4 integers (x, y, w, h)");
      return NULL;
  }

  rect->setSize(sf::Vector2f(w, h));
  rect->setPosition(sf::Vector2f(x, y));
  window->draw(*rect);
  Py_RETURN_NONE;
}

// FUNC: setOutlineColor
PyDoc_STRVAR(engine_rectangle_setOutlineColor_doc,
  ".. function:: setOutlineColor()\n"
  "\n"
  "   Set rectangle outline color.\n"
  "\n"
  "   :return: None.\n"
);

static PyObject* setOutlineColor(PyObject *self, PyObject *args) {
  int r, g, b;
  int a = 255;

  if (!PyArg_ParseTuple(args, "iii|i", &r, &g, &b, &a)) {
      PyErr_SetString(PyExc_TypeError, "Expected 3 or 4 integers (r, g, b[, a])");
      return NULL;
  }

  rect->setOutlineColor(sf::Color(r, g, b, a));
  Py_RETURN_NONE;
}

// FUNC: setOutlineThickness
PyDoc_STRVAR(engine_rectangle_setOutlineThickness_doc,
  ".. function:: setOutlineThickness()\n"
  "\n"
  "   Set rectangle outline thickness.\n"
  "\n"
  "   :return: None.\n"
);

static PyObject* setOutlineThickness(PyObject *self, PyObject *args) {
  int w;
  if (!PyArg_ParseTuple(args, "i", &w)){
    PyErr_SetString(PyExc_TypeError, "Expected one integer argument");
    return NULL;
  }
  rect->setOutlineThickness(w);
  Py_RETURN_NONE;
}

// FUNC: setFillColor
PyDoc_STRVAR(engine_rectangle_setFillColor_doc,
  ".. function:: setFillColor()\n"
  "\n"
  "   Set rectangle fill color.\n"
  "\n"
  "   :return: None.\n"
);

static PyObject* setFillColor(PyObject *self, PyObject *args) {
  int r, g, b;
  int a = 255;

  if (!PyArg_ParseTuple(args, "iii|i", &r, &g, &b, &a)) {
      PyErr_SetString(PyExc_TypeError, "Expected 3 or 4 integers (r, g, b[, a])");
      return NULL;
  }

  rect->setFillColor(sf::Color(r, g, b, a));
  Py_RETURN_NONE;
}

// rectangle methods
static PyMethodDef rectangle_methods[] = {
  {"draw", draw, METH_VARARGS, engine_rectangle_draw_doc},
  {"setOutlineColor", setOutlineColor, METH_VARARGS, engine_rectangle_setOutlineColor_doc},
  {"setOutlineThickness", setOutlineThickness, METH_VARARGS, engine_rectangle_setOutlineThickness_doc},
  {"setFillColor", setFillColor, METH_VARARGS, engine_rectangle_setFillColor_doc},
  {NULL, NULL, 0, NULL}
};

// rectangle definition
static struct PyModuleDef rectangle_def = {
  PyModuleDef_HEAD_INIT,
  "rectangle",
  NULL,
  -1,
  rectangle_methods
};

// rectangle initialization function
PyMODINIT_FUNC PyInit_rectangle(void) {
  PyObject *rectangle;
  rectangle = PyModule_Create(&rectangle_def);
  if (rectangle == NULL)
      return NULL;
  return rectangle;
}