#pragma once
#include <Python.h>


PyDoc_STRVAR(engine_draw_circle_doc,
    ".. function:: draw_circle(x, y, z, r, R, G, B, A)\n"
    "\n"
    "   Draws a circle centered at (x,y) at depth z with radius r in the window. It will be filled with an RGB value with alpha A.\n"
    "\n"
    "   :return: Nothing.\n"
);
PyObject* engine_draw_circle(PyObject *self, PyObject *args);

PyDoc_STRVAR(engine_draw_rect_doc,
    ".. function:: draw_rect(x, y, z, w, h, R, G, B, A)\n"
    "\n"
    "   Draws a rectangle centered at (x,y) at depth z with width w and height h in the window. It will be filled with an RGB value with alpha A.\n"
    "\n"
    "   :return: Nothing.\n"
);
PyObject*engine_draw_rect(PyObject *self, PyObject *args);

PyDoc_STRVAR(engine_draw_line_doc,
    ".. function:: draw_line(x1, y1, z1, x2, y2, z2, R, G, B)\n"
    "\n"
    "   Draws a line from (x1,y1,z1) to (x2,y2,z2) with color (R,G,B) in the window.\n"
    "\n"
    "   :return: Nothing.\n"
);
PyObject*engine_draw_line(PyObject *self, PyObject *args);

PyDoc_STRVAR(engine_textColor_doc,
    ".. function:: textColor(r, g, b)\n"
    "\n"
    "   Set text color to (r,g,b).\n"
    "\n"
    "   :return: Nothing.\n"
);
PyObject*engine_textColor(PyObject *self, PyObject *args);

PyDoc_STRVAR(engine_print_doc,
    ".. function:: print(font, string, x, y, size)\n"
    "\n"
    "   Print string with font at x, y with size big.\n"
    "\n"
    "   :return: Nothing.\n"
);
PyObject*engine_print(PyObject *self, PyObject *args);
void draw_drawlater();