#include "draw.h"
#include <SFML/Graphics.hpp>

extern sf::RenderWindow *window;
extern sf::CircleShape *circle;
extern sf::RectangleShape *rect;
extern sf::Vertex line[2];
extern sf::Text text;
//depthshape *drawlater[100];
int drawlater_count;

class depthshape {
    public:
        sf::Drawable *shape;
        int depth;
        depthshape () {
            shape = nullptr;
            depth = 0;
        }
};

depthshape *drawlater[100];

sf::Font engineFont;
bool fontLoaded = false;

/* Return the number of arguments of the application command line */
PyObject* engine_draw_circle(PyObject *self, PyObject *args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if(nargs != 8) {
        // error!
        printf("engine.draw_circle expects 8 longs as arguments\n");
        PyErr_BadArgument();
    }
    //printf("drawing circle %ld\n", nargs);
    PyObject *pX = PyTuple_GetItem(args, 0);
    if(!PyLong_Check(pX)) {
        Py_XDECREF(pX);
        // error!
        printf("engine.draw_circle expects 8 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pY = PyTuple_GetItem(args, 1);
    if(!PyLong_Check(pY)) {
        Py_XDECREF(pY);
        // error!
        printf("engine.draw_circle expects 8 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pZ = PyTuple_GetItem(args, 2);
    if(!PyLong_Check(pZ)) {
        Py_XDECREF(pZ);
        // error!
        printf("engine.draw_circle expects 8 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pR = PyTuple_GetItem(args, 3);
    if(!PyLong_Check(pR)) {
        Py_XDECREF(pR);
        // error!
        printf("engine.draw_circle expects 8 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pRed = PyTuple_GetItem(args, 4);
    if(!PyLong_Check(pRed)) {
        Py_XDECREF(pRed);
        // error!
        printf("engine.draw_circle expects 8 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pG = PyTuple_GetItem(args, 5);
    if(!PyLong_Check(pG)) {
        Py_XDECREF(pG);
        // error!
        printf("engine.draw_circle expects 8 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pB = PyTuple_GetItem(args, 6);
    if(!PyLong_Check(pB)) {
        Py_XDECREF(pB);
        // error!
        printf("engine.draw_circle expects 8 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pA = PyTuple_GetItem(args, 7);
    if(!PyLong_Check(pA)) {
        Py_XDECREF(pA);
        // error!
        printf("engine.draw_circle expects 8 longs as arguments\n");
        PyErr_BadArgument();
    }

    long x = PyLong_AsLong(pX);
    long y = PyLong_AsLong(pY);
    long z = PyLong_AsLong(pZ);
    long r = PyLong_AsLong(pR);

    long R = PyLong_AsLong(pRed);
    long G = PyLong_AsLong(pG);
    long B = PyLong_AsLong(pB);
    long A = PyLong_AsLong(pA);

    //printf("drawing circle %ld %ld\n", x, y);

    float scale = pow((4800.0f - z) / 4800.0f, 2.0f);
    //scale = 1;

    float diffx = 400 + (x - 400) * scale;
    float diffy = 300 + (y - 300) * scale;

    //printf("new x: %g\n", diffx);

    float radius = static_cast<float>(r) * scale;

    sf::CircleShape *tempCircle = new sf::CircleShape();
    tempCircle->setRadius(radius);
    tempCircle->setPosition(sf::Vector2f(diffx, diffy));
    tempCircle->setOutlineColor(sf::Color(R, G, B, 255));
    tempCircle->setOutlineThickness(1);
    tempCircle->setFillColor(sf::Color(R, G, B, A));

    //window->draw(*circle);
    drawlater[drawlater_count] = new depthshape();
    drawlater[drawlater_count]->shape = tempCircle;
    drawlater[drawlater_count]->depth = z;
    drawlater_count++;
    //printf("drawlater count: %d\n", drawlater_count);

    Py_RETURN_NONE;
    /*if(!PyArg_ParseTuple(args, ":numargs"))
        return NULL;
    return PyLong_FromLong(numargs);*/
}



PyObject*engine_draw_rect(PyObject *self, PyObject *args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if(nargs != 9) {
        // error!
        printf("engine.draw_rect expects 9 longs as arguments\n");
        PyErr_BadArgument();
    }
    //printf("drawing rect %ld\n", nargs);
    PyObject *pX = PyTuple_GetItem(args, 0);
    if(!PyLong_Check(pX)) {
        Py_XDECREF(pX);
        // error!
        printf("engine.draw_rect expects 9 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pY = PyTuple_GetItem(args, 1);
    if(!PyLong_Check(pY)) {
        Py_XDECREF(pY);
        // error!
        printf("engine.draw_rect expects 9 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pZ = PyTuple_GetItem(args, 2);
    if(!PyLong_Check(pZ)) {
        Py_XDECREF(pZ);
        // error!
        printf("engine.draw_rect expects 9 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pW = PyTuple_GetItem(args, 3);
    if(!PyLong_Check(pW)) {
        Py_XDECREF(pW);
        // error!
        printf("engine.draw_rect expects 9 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pH = PyTuple_GetItem(args, 4);
    if(!PyLong_Check(pH)) {
        Py_XDECREF(pH);
        // error!
        printf("engine.draw_rect expects 9 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pR = PyTuple_GetItem(args, 5);
    if(!PyLong_Check(pR)) {
        Py_XDECREF(pR);
        // error!
        printf("engine.draw_rect expects 9 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pG = PyTuple_GetItem(args, 6);
    if(!PyLong_Check(pG)) {
        Py_XDECREF(pG);
        // error!
        printf("engine.draw_rect expects 9 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pB = PyTuple_GetItem(args, 7);
    if(!PyLong_Check(pB)) {
        Py_XDECREF(pB);
        // error!
        printf("engine.draw_rect expects 9 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pA = PyTuple_GetItem(args, 8);
    if(!PyLong_Check(pA)) {
        Py_XDECREF(pA);
        // error!
        printf("engine.draw_rect expects 9 longs as arguments\n");
        PyErr_BadArgument();
    }


    long R = PyLong_AsLong(pR);
    long G = PyLong_AsLong(pG);
    long B = PyLong_AsLong(pB);
    long A = PyLong_AsLong(pA);
    long x = PyLong_AsLong(pX);
    long y = PyLong_AsLong(pY);
    long z = PyLong_AsLong(pZ);
    long w = PyLong_AsLong(pW);
    long h = PyLong_AsLong(pH);

    float scale = pow((4800.0f - z) / 4800.0f, 2.0f);
    //printf("scale: %f\n", scale);
    //float scale = (4800.0 - static_cast<float>(z))/4800.0;

    float diffx = 400 + (x - 400) * scale;
    float diffy = 300 + (y - 300) * scale;

    float width = w * scale;
    float height = h * scale;

    sf::RectangleShape *temprect = new sf::RectangleShape();
    temprect->setSize(sf::Vector2f(width, height));
    temprect->setPosition(sf::Vector2f(diffx, diffy));
    temprect->setOutlineColor(sf::Color(R, G, B, 255));
    temprect->setOutlineThickness(1);
    temprect->setFillColor(sf::Color(R, G, B, A));

    drawlater[drawlater_count] = new depthshape();
    drawlater[drawlater_count]->shape = temprect;
    drawlater[drawlater_count]->depth = z;
    drawlater_count++;

    Py_RETURN_NONE;

}



PyObject*engine_draw_line(PyObject *self, PyObject *args) {
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    if(nargs != 9) {
        // error!
        printf("engine.draw_line expects 9 longs as arguments\n");
        PyErr_BadArgument();
    }
    //printf("drawing line %ld\n", nargs);
    PyObject *pX1 = PyTuple_GetItem(args, 0);
    if(!PyLong_Check(pX1)) {
        Py_XDECREF(pX1);
        // error!
        printf("engine.draw_line expects 9 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pY1 = PyTuple_GetItem(args, 1);
    if(!PyLong_Check(pY1)) {
        Py_XDECREF(pY1);
        // error!
        printf("engine.draw_line expects 9 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pX2 = PyTuple_GetItem(args, 3);
    if(!PyLong_Check(pX2)) {
        Py_XDECREF(pX2);
        // error!
        printf("engine.draw_line expects 9 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pY2 = PyTuple_GetItem(args, 4);
    if(!PyLong_Check(pY2)) {
        Py_XDECREF(pY2);
        // error!
        printf("engine.draw_line expects 9 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pZ1 = PyTuple_GetItem(args, 2);
    if(!PyLong_Check(pZ1)) {
        Py_XDECREF(pZ1);
        // error!
        printf("engine.draw_line expects 9 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pZ2 = PyTuple_GetItem(args, 5);
    if(!PyLong_Check(pZ2)) {
        Py_XDECREF(pZ2);
        // error!
        printf("engine.draw_line expects 9 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pR = PyTuple_GetItem(args, 6);
    if(!PyLong_Check(pR)) {
        Py_XDECREF(pR);
        // error!
        printf("engine.draw_line expects 9 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pG = PyTuple_GetItem(args, 7);
    if(!PyLong_Check(pG)) {
        Py_XDECREF(pG);
        // error!
        printf("engine.draw_line expects 9 longs as arguments\n");
        PyErr_BadArgument();
    }
    PyObject *pB = PyTuple_GetItem(args, 8);
    if(!PyLong_Check(pB)) {
        Py_XDECREF(pB);
        // error!
        printf("engine.draw_line expects 9 longs as arguments\n");
        PyErr_BadArgument();
    }

    long x1 = PyLong_AsLong(pX1);
    long y1 = PyLong_AsLong(pY1);
    long x2 = PyLong_AsLong(pX2);
    long y2 = PyLong_AsLong(pY2);
    long z1 = PyLong_AsLong(pZ1);
    long z2 = PyLong_AsLong(pZ2);

    long R = PyLong_AsLong(pR);
    long G = PyLong_AsLong(pG);
    long B = PyLong_AsLong(pB);

    float scale1 = pow((4800.0f - z1) / 4800.0f, 2.0f);
    float scale2 = pow((4800.0f - z2) / 4800.0f, 2.0f);

    float diffx1 = 400 + (x1 - 400) * scale1;
    float diffy1 = 300 + (y1 - 300) * scale1;
    float diffx2 = 400 + (x2 - 400) * scale2;
    float diffy2 = 300 + (y2 - 300) * scale2;

    line[0].position = sf::Vector2f(diffx1, diffy1);
    line[0].color = sf::Color(R, G, B, 255);
    line[1].position = sf::Vector2f(diffx2, diffy2);
    line[1].color = sf::Color(R, G, B, 255);
    
    window->draw(line, 2, sf::PrimitiveType::Lines, sf::RenderStates::Default);

    Py_RETURN_NONE;
    
}
PyObject* engine_textColor(PyObject *self, PyObject *args) {
    int r, g, b;
    if (!PyArg_ParseTuple(args, "iii", &r, &g, &b)) {
        PyErr_SetString(PyExc_TypeError, "Expected (r, g, b)");
        return NULL;
    }
    text.setFillColor(sf::Color(r,g,b));
    Py_RETURN_NONE;
}

PyObject* engine_print(PyObject *self, PyObject *args) {
    const char *font, *string;
    int x, y, size;
    if (!PyArg_ParseTuple(args, "ssiii", &font, &string, &x, &y, &size)) {
        PyErr_SetString(PyExc_TypeError, "Expected (font, string, x, y, size)");
        return NULL;
    }

    if (!fontLoaded) {
        if (!engineFont.loadFromFile(font)) {
            PyErr_SetString(PyExc_TypeError, "Fail loading font.");
            return NULL;
        }
        fontLoaded = true;
    }

    text.setFont(engineFont);
    text.setPosition(x, y);
    text.setString(string);
    text.setCharacterSize(size);
    window->draw(text);
    Py_RETURN_NONE;
}


void wipe_drawlater() {
    for(int i = 0; i < drawlater_count; i++) {
        delete drawlater[i];
    }
    drawlater_count = 0;
}

void sort_drawlater() {
    for(int i = 0; i < drawlater_count; i++) {
        for(int j = i + 1; j < drawlater_count; j++) {
            if(drawlater[i]->depth > drawlater[j]->depth) {
                depthshape *temp = drawlater[i];
                drawlater[i] = drawlater[j];
                drawlater[j] = temp;
            }
        }
    }
}
void draw_drawlater() {
    sort_drawlater();
    for(int i = drawlater_count - 1; i >= 0; i--) {
        //printf("drawing %d\n", i);
        //printf("drawing %d %d\n", drawlater[i]->depth, drawlater[i]->shape);
        window->draw(*(drawlater[i]->shape));
    }
    wipe_drawlater();
}