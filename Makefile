INCLUDE_PYTHONB = -lpython3.10 -I/usr/include/python3.10
INCLUDE_PYTHOND = \
-I/Library/Frameworks/Python.framework/Versions/3.13/include/python3.13 \
-L/Library/Frameworks/Python.framework/Versions/3.13/lib \
-lpython3.13

INCLUDE_SFMLB = -lsfml-graphics -lsfml-window -lsfml-system -I/usr/include/SFML/
INCLUDE_SFMLD = -lsfml-graphics -lsfml-window -lsfml-system -I/opt/sfml262/include -L/opt/sfml262/lib

INCLUDE_SFML_EXTRAS = -lsfml-audio -lsfml-network

INCLUDE_GLB = -lGL -lGLU -lglut -I/usr/include/GL/
INCLUDE_GLD = -framework OpenGL -framework GLUT

PYTHON_SUFFIX := $(shell python3-config --extension-suffix)

ENGINE_SOURCES = engine.cpp $(shell find function -name '*.cpp') 

all: engine

.PHONY: all clean

engine: $(ENGINE_SOURCES)
	g++ -std=c++17 -o engine $(ENGINE_SOURCES) $(INCLUDE_SFML_EXTRAS) $(INCLUDE_PYTHOND) $(INCLUDE_SFMLD) -Wl,-rpath,/opt/sfml262/lib -I./include

clean:
	rm -rf engine *.o *.so __pycache__