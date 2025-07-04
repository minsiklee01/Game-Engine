#include "audio.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

sf::Music music;
bool musicLoaded = false;

PyObject* loadMusic(PyObject *self, PyObject *args) {
  const char* filename;
  if (!PyArg_ParseTuple(args, "s", &filename)) {
      PyErr_SetString(PyExc_TypeError, "Expected one string argument (filename)");
      return NULL;
  }

  if (!music.openFromFile(filename)) {
      PyErr_SetString(PyExc_IOError, "Failed to load music file");
      return NULL;
  }

  musicLoaded = true;
  Py_RETURN_NONE;
}

PyObject* playMusic(PyObject *self, PyObject *args) {
  if (!musicLoaded) {
      PyErr_SetString(PyExc_RuntimeError, "Music not loaded");
      return NULL;
  }

  music.setLoop(true);
  music.play();
  Py_RETURN_NONE;
}

PyObject* pauseMusic(PyObject *self, PyObject *args) {
  if (!musicLoaded) {
      PyErr_SetString(PyExc_RuntimeError, "Music not loaded");
      return NULL;
  }

  music.pause();
  Py_RETURN_NONE;
}

PyObject* stopMusic(PyObject *self, PyObject *args) {
  if (!musicLoaded) {
      PyErr_SetString(PyExc_RuntimeError, "Music not loaded");
      return NULL;
  }

  music.stop();
  Py_RETURN_NONE;
}

// audio methods
static PyMethodDef audio_methods[] = {
  {"loadMusic", loadMusic, METH_VARARGS, engine_audio_loadMusic_doc},
  {"playMusic", playMusic, METH_VARARGS, engine_audio_playMusic_doc},
  {"pauseMusic", pauseMusic, METH_VARARGS, engine_audio_pauseMusic_doc},
  {"stopMusic", stopMusic, METH_VARARGS, engine_audio_stopMusic_doc},
  {NULL, NULL, 0, NULL}
};

// audio definition
static struct PyModuleDef audio_def = {
  PyModuleDef_HEAD_INIT,
  "audio",
  NULL,
  -1,
  audio_methods
};

// audio initialization function
PyMODINIT_FUNC PyInit_audio(void) {
  PyObject *audio;
  audio = PyModule_Create(&audio_def);
  if (audio == NULL)
      return NULL;
  return audio;
}