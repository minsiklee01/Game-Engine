#include <Python.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
extern sf::RenderWindow* window;
extern sf::Texture tileTexture;
extern sf::Sprite tileSprite;

struct Tile {
  int id;
  int x, y;
  bool solid;
};

std::vector<Tile> loadedMap;
int tileSize = 0;

struct Area2D {
  std::string name;
  int x, y, w, h;
};

std::vector<Area2D> area2DList;
std::unordered_map<std::string, sf::Texture> spriteSheetCache;
bool tiles_loaded = false;

void draw_tile(int tile_id, int x, int y, int tileSize);

PyObject* engine_load_tilemap(PyObject *self, PyObject *args) {
  const char *fileName, *spriteName;
  int offsetX = 0;
  int offsetY = 0;
  
  if (!PyArg_ParseTuple(args, "ssii", &fileName, &spriteName, &offsetX, &offsetY)){
    PyErr_SetString(PyExc_TypeError, "Expected (str) fileName, spriteName and 4 integers (x, y, w, h)");
    return NULL;
  }

  std::ifstream file(fileName);
  if (!file.is_open()) {
      PyErr_SetString(PyExc_IOError, "Cannot open map file");
      return NULL;
  }
  if (!tileTexture.loadFromFile(spriteName)) {
      std::cerr << "Failed to load " << spriteName << std::endl;
      PyErr_SetString(PyExc_IOError, "Cannot load sprite sheet");
      return NULL;
  } else {
      std::cout << "[DEBUG] Loaded sprite sheet: " << spriteName << std::endl;
      std::cout << "[DEBUG] Texture size: " << tileTexture.getSize().x << "x" << tileTexture.getSize().y << std::endl;
  }

  nlohmann::json j;
  file >> j;

  tileSize = j["tileSize"];
  loadedMap.clear();

  for (const auto& layer : j["layers"]) {
      bool solid = layer["collider"].get<bool>();
      for (const auto& tile : layer["tiles"]) {
          int id = std::stoi(tile["id"].get<std::string>());
          int tx = tile["x"].get<int>();
          int ty = tile["y"].get<int>();
          int x = tx * tileSize + offsetX;
          int y = ty * tileSize + offsetY;
          loadedMap.push_back({ id, x, y, solid });
      }
  }

  Py_RETURN_NONE;
}

PyObject* engine_draw_map(PyObject* self, PyObject* args) {
    for (const auto& tile : loadedMap) {
        draw_tile(tile.id, tile.x, tile.y, tileSize);

      //   if (tile.solid) {
      //     sf::RectangleShape debugRect;
      //     debugRect.setSize(sf::Vector2f(tileSize, tileSize));
      //     debugRect.setPosition(tile.x, tile.y);
      //     debugRect.setFillColor(sf::Color::Transparent);
      //     debugRect.setOutlineColor(sf::Color::Red);
      //     debugRect.setOutlineThickness(1);
      //     window->draw(debugRect);
      // }
    }
    Py_RETURN_NONE;
}

PyObject* engine_is_colliding(PyObject* self, PyObject* args) {
  int px, py, pw, ph;
  if (!PyArg_ParseTuple(args, "iiii", &px, &py, &pw, &ph)) {
      return NULL;
  }

  for (const auto& tile : loadedMap) {
      if (!tile.solid) continue;
      if (px < tile.x + tileSize && px + pw > tile.x &&
          py < tile.y + tileSize && py + ph > tile.y) {
          Py_RETURN_TRUE;
      }
  }

  Py_RETURN_FALSE;
}

PyObject* engine_add_area2d(PyObject* self, PyObject* args) {
  const char* name;
  int x, y, w, h;
  if (!PyArg_ParseTuple(args, "siiii", &name, &x, &y, &w, &h)) {
    PyErr_SetString(PyExc_TypeError, "Expected name (str) and 4 integers (x, y, w, h)");
      return NULL;
  }
  area2DList.push_back({std::string(name), x, y, w, h});
  Py_RETURN_NONE;
}

PyObject* engine_is_in_area(PyObject* self, PyObject* args) {
  const char* name;
  int x, y, w, h;
  if (!PyArg_ParseTuple(args, "siiii", &name, &x, &y, &w, &h)) {
    PyErr_SetString(PyExc_TypeError, "Expected name (str) and 4 integers (x, y, w, h)");
    return NULL;
  }
  for (const auto& area : area2DList) {
    if (area.name == name) {
      bool overlap = x < area.x + area.w && x + w > area.x &&
                     y < area.y + area.h && y + h > area.y;
      if (overlap) Py_RETURN_TRUE;
      else Py_RETURN_FALSE;
    }
  }
  PyErr_SetString(PyExc_ValueError, "Area2D with given name not found");
  return NULL;
}

void draw_tile(int tile_id, int x, int y, int tileSize) {

  tileSprite.setTexture(tileTexture);
  int tiles_per_row = tileTexture.getSize().x / tileSize;
  int tx = (tile_id % tiles_per_row) * tileSize;
  int ty = (tile_id / tiles_per_row) * tileSize;

  tileSprite.setTextureRect(sf::IntRect(tx, ty, tileSize, tileSize));
  tileSprite.setPosition(x, y);
  window->draw(tileSprite);
}

PyObject* engine_draw_tile(PyObject* self, PyObject* args) {
  int tile_id, x, y, tileSize;
  if (!PyArg_ParseTuple(args, "iiii", &tile_id, &x, &y, &tileSize)) {
      PyErr_SetString(PyExc_TypeError, "Expected 4 integers (tile_id, x, y, tileSize).");
      return NULL;
  }
  
  draw_tile(tile_id, x, y, tileSize);
  Py_RETURN_NONE;
}

void draw_sprite_frame(std::string filename, int frame_index, int x, int y, int frame_width, int frame_height, int scale, bool faceRight) {
  static sf::Sprite sprite;

  if(spriteSheetCache.find(filename) == spriteSheetCache.end()) {
    sf::Texture tex;
    if(!tex.loadFromFile(filename)) {
      std::cerr << "Failed to load sprite sheet: " << filename << std::endl;
      return;
    }
    spriteSheetCache[filename] = std::move(tex);
  }

  sprite.setTexture(spriteSheetCache[filename]);
  
  int sheet_width = sprite.getTexture()->getSize().x;
  int frames_per_row = sheet_width / frame_width;
  int fx = (frame_index % frames_per_row) * frame_width;
  int fy = (frame_index / frames_per_row) * frame_height;
  sprite.setTextureRect(sf::IntRect(fx, fy, frame_width, frame_height));

  float ratio = tileSize / static_cast<float>(frame_width) * scale;
  float new_x = x + tileSize/2.0 * (1 - scale);
  float new_y = y + tileSize * (1 - scale);

  sprite.setOrigin(faceRight ? 0.f : frame_width, 0.f);
  sprite.setScale((faceRight ? 1.f : -1.f) * ratio, ratio);

  sprite.setPosition(new_x, new_y);
  window->draw(sprite);
}

PyObject* engine_draw_sprite_frame(PyObject* self, PyObject* args) {
  const char* filename;
  int frame_index, x, y, frame_w, frame_h, scale;
  bool faceRight;
  if (!PyArg_ParseTuple(args, "siiiiiib", &filename, &frame_index, &x, &y, &frame_w, &frame_h, &scale, &faceRight)) {
      PyErr_SetString(PyExc_TypeError, "Expected (filename, frame_index, x, y, frame_w, frame_h, scale, faceRight)");
      return NULL;
  }
  draw_sprite_frame(filename, frame_index, x, y, frame_w, frame_h, scale, faceRight);
  Py_RETURN_NONE;
}

