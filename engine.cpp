
#include <Python.h>
#include <SFML/Graphics.hpp>

#include "./function/draw/draw.h"
#include "./function/draw/2Dmap.h"
#include "./function/draw/rectangle.h"
#include "./function/input/keyboard/keyboard.h"
#include "./function/input/joystick/joystick.h"
#include "./function/audio/audio.h"

sf::RenderWindow *window;
sf::CircleShape *circle;
sf::RectangleShape *rect;
sf::Vertex line[2];
sf::Text text;

sf::Texture tileTexture;
sf::Sprite tileSprite;

PyObject* engine_close(PyObject* self, PyObject* args) {
    if (window && window->isOpen()) {
        window->close();
    }
    Py_RETURN_NONE;
}

PyMODINIT_FUNC PyInit_keyboard(void);
PyMODINIT_FUNC PyInit_joystick(void);
PyMODINIT_FUNC PyInit_rectangle(void);
PyMODINIT_FUNC PyInit_audio(void);


static PyMethodDef EngineMethods[] = {
    {"draw_circle", engine_draw_circle, METH_VARARGS, engine_draw_circle_doc},
    {"draw_rect", engine_draw_rect, METH_VARARGS, engine_draw_rect_doc},
    {"draw_line", engine_draw_line, METH_VARARGS, engine_draw_line_doc},
    {"textColor", engine_textColor, METH_VARARGS, engine_textColor_doc},
    {"print", engine_print, METH_VARARGS, engine_print_doc},
    {"load_tilemap", engine_load_tilemap, METH_VARARGS, engine_load_tilemap_doc},
    {"draw_map", engine_draw_map, METH_VARARGS, engine_draw_map_doc},
    {"is_colliding", engine_is_colliding, METH_VARARGS, engine_is_colliding_doc},
    {"add_area2d", engine_add_area2d, METH_VARARGS, engine_add_area2d_doc},
    {"is_in_area", engine_is_in_area, METH_VARARGS, engine_is_in_area_doc},
    {"draw_tile", engine_draw_tile, METH_VARARGS, engine_draw_tile_doc},
    {"draw_sprite_frame", engine_draw_sprite_frame, METH_VARARGS, engine_draw_sprite_frame_doc},
    {"close", engine_close, METH_NOARGS, "Close the window"},
    {NULL, NULL, 0, NULL}
};

static PyModuleDef EngineModule = {
    PyModuleDef_HEAD_INIT,
    "engine",                   /* m_name */
    NULL,                       /* m_doc */
    -1,                         /* m_size */
    EngineMethods,              /* m_methods */
    NULL,                       /* m_reload */
    NULL,                       /* m_traverse */
    NULL,                       /* m_clear */
    NULL                        /* m_free */
};

PyMODINIT_FUNC PyInit_engine(void) {
    PyObject *engine, *keyboard_module, *joystick_module, *rectangle_module, *audio_module;

    // create main module
    engine = PyModule_Create(&EngineModule);
    if (engine == NULL) return NULL;

    // create keyboard module
    keyboard_module = PyInit_keyboard();
    if (keyboard_module == NULL) return NULL;
    Py_INCREF(keyboard_module);
    PyModule_AddObject(engine, "keyboard", keyboard_module);
    PyModule_AddStringConstant(keyboard_module, "__package__", "engine");

    // create joystick module
    joystick_module = PyInit_joystick();
    if (joystick_module == NULL) return NULL;
    Py_INCREF(joystick_module);
    PyModule_AddObject(engine, "joystick", joystick_module);
    PyModule_AddStringConstant(joystick_module, "__package__", "engine");
    
    // create rectangle module
    rectangle_module = PyInit_rectangle();
    if (rectangle_module == NULL) return NULL;
    Py_INCREF(rectangle_module);
    PyModule_AddObject(engine, "rectangle", rectangle_module);
    PyModule_AddStringConstant(rectangle_module, "__package__", "engine");

    // create audio module
    audio_module = PyInit_audio();
    if (audio_module == NULL) return NULL;
    Py_INCREF(audio_module);
    PyModule_AddObject(engine, "audio", audio_module);
    PyModule_AddStringConstant(audio_module, "__package__", "engine");

    // Make main module a package
    PyModule_AddObject(engine, "__path__", PyList_New(0));
    PyModule_AddStringConstant(engine, "__package__", "engine");

    // Update sys.modules
    PyDict_SetItemString(PyImport_GetModuleDict(), "engine.keyboard", keyboard_module);
    PyDict_SetItemString(PyImport_GetModuleDict(), "engine.joystick", joystick_module);
    PyDict_SetItemString(PyImport_GetModuleDict(), "engine.rectangle", rectangle_module);
    PyDict_SetItemString(PyImport_GetModuleDict(), "engine.audio", audio_module);

    return engine;
}


int main(int argc, char *argv[]) {
    PyObject *pName, *pModule, *pFuncInit, *pFuncUpdate, *pFuncDraw;
    PyObject *pArgs, *pValue;
    PyObject *pErr;
    int i;

    if (argc != 2) {
        fprintf(stderr, "Usage: engine pythongame.py\n");
        return 1;
    }

    PyImport_AppendInittab("engine", PyInit_engine);

    Py_Initialize();
    char *pythonfilename = argv[1];
    char *extension = strstr(pythonfilename, ".py\0");
    if(extension) strncpy(extension, "\0", 1);
    pName = PyUnicode_DecodeFSDefault(pythonfilename);
    /* Error checking of pName left out */

    // Setting up Python path
    PyRun_SimpleString("import sys\n"
                       "sys.path.insert(0, \".\")");


    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule == NULL) {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
        return 1;
    }

    pFuncInit = PyObject_GetAttrString(pModule, "init");
    if (!pFuncInit || !PyCallable_Check(pFuncInit)) {
        if (PyErr_Occurred())
            PyErr_Print();
        fprintf(stderr, "Cannot find function \"init\"\n");
        return 1;
    }
    pFuncUpdate = PyObject_GetAttrString(pModule, "update");
    if (!pFuncUpdate || !PyCallable_Check(pFuncUpdate)) {
        if (PyErr_Occurred())
            PyErr_Print();
        fprintf(stderr, "Cannot find function \"update\"\n");
        return 1;
    }
    pFuncDraw = PyObject_GetAttrString(pModule, "draw");
    if (!pFuncDraw || !PyCallable_Check(pFuncDraw)) {
        if (PyErr_Occurred())
            PyErr_Print();
        fprintf(stderr, "Cannot find function \"draw\"\n");
        return 1;
    }

    
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "Engine!");
    circle = new sf::CircleShape(10.f);
    rect = new sf::RectangleShape(sf::Vector2f(10.f, 10.f));
    circle->setFillColor(sf::Color::Green);
    rect = new sf::RectangleShape();

    pValue = PyObject_CallNoArgs(pFuncInit);
    Py_DECREF(pValue);


    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window->close();
                break;
            }
        }
        if(!window->isOpen()) break;

        pValue = PyObject_CallNoArgs(pFuncUpdate);
        pErr = PyErr_Occurred();
        if(pErr) {
            printf("An error occurred!\n");
            window->close();
            break;
        }
        Py_XDECREF(pValue);


        window->clear();
        //wipe_drawlater();
        pValue = PyObject_CallNoArgs(pFuncDraw);
        pErr = PyErr_Occurred();
        if(pErr) {
            printf("An error occurred!\n");
            window->close();
            break;
        }
        Py_XDECREF(pValue);
        // window->draw(shape);
        draw_drawlater();
        window->display();
    }


    Py_XDECREF(pFuncDraw);
    Py_XDECREF(pFuncUpdate);
    Py_XDECREF(pFuncInit);
    Py_DECREF(pModule);

    if (Py_FinalizeEx() < 0) {
        return 120;
    }
    return 0;
}