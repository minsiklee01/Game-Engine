#pragma once
#include <Python.h>

PyObject* engine_load_tilemap(PyObject *self, PyObject *args);
PyObject* engine_draw_map(PyObject* self, PyObject* args);
PyObject* engine_is_colliding(PyObject* self, PyObject* args);
PyObject* engine_add_area2d(PyObject* self, PyObject* args);
PyObject* engine_is_in_area(PyObject* self, PyObject* args);
PyObject* engine_draw_tile(PyObject* self, PyObject* args);
PyObject* engine_draw_sprite_frame(PyObject* self, PyObject* args);

PyDoc_STRVAR(engine_load_tilemap_doc,
  ".. function:: load_tilemap(filename)\n"
  "\n"
  "   Loads a tilemap from a JSON file.\n"
);
PyDoc_STRVAR(engine_draw_map_doc,
  ".. function:: draw_map()\n"
  "\n"
  "   Draws all tiles from the loaded map using the engine renderer.\n"
);
PyDoc_STRVAR(engine_is_colliding_doc,
  ".. function:: is_colliding(x, y, w, h)\n"
  "\n"
  "   Checks for collision against the loaded map.\n"
  "   :return: True if colliding, False otherwise.\n"
);
PyDoc_STRVAR(engine_add_area2d_doc,
  ".. function:: add_area2d(name, x, y, w, h)\n"
  "\n"
  "   Create an 2D area with a name. \n"
  "\n"
  "   :return: None.\n"
);
PyDoc_STRVAR(engine_is_in_area_doc,
  ".. function:: engine_is_in_area_(name, x, y, w, h)\n"
  "\n"
  "   Create an 2D area with a name. \n"
  "\n"
  "   :return: Bool.\n"
);
PyDoc_STRVAR(engine_draw_tile_doc,
  ".. function:: draw_tile(filename, tileId, x, y, tileSize)\n"
  "\n"
  "   Get tileId texture from filename and draw tile at (x, y) with tileSize.\n"
);
PyDoc_STRVAR(engine_draw_sprite_frame_doc,
  ".. function:: engine_draw_sprite_frame(filename, frame_index, x, y, frame_w, frame_h)\n"
  "\n"
  "   Read filename and draw frame_w width, frame_h height frame_index frame at (x,y).\n"
);
