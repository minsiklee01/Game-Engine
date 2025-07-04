#pragma once
#include <Python.h>

PyMODINIT_FUNC PyInit_audio(void);

PyDoc_STRVAR(engine_audio_loadMusic_doc,
    ".. function:: loadMusic(path)\n"
    "\n"
    "   Load music feom path.\n"
    "\n"
    "   :return: Nothing.\n"
  );
PyDoc_STRVAR(engine_audio_playMusic_doc,
    ".. function:: playMusic(path)\n"
    "\n"
    "   Play loaded music.\n"
    "\n"
    "   :return: Nothing.\n"
  );
PyDoc_STRVAR(engine_audio_pauseMusic_doc,
    ".. function:: pauseMusic(path)\n"
    "\n"
    "   Pause playing music.\n"
    "\n"
    "   :return: Nothing.\n"
  );
PyDoc_STRVAR(engine_audio_stopMusic_doc,
    ".. function:: stopMusic(path)\n"
    "\n"
    "   Stop playing music.\n"
    "\n"
    "   :return: Nothing.\n"
  );
PyObject* loadMusic(PyObject *self, PyObject *args);
PyObject* playMusic(PyObject *self, PyObject *args);
PyObject* pauseMusic(PyObject *self, PyObject *args);
PyObject* stopMusic(PyObject *self, PyObject *args);