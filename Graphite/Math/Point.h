#pragma once
#include "Renderer.h"
#include "Globals.h"

#include "PointShader.h"

#include <array>

namespace Graphite::Math{
class Point{
private:
  float x = 0.0f;
  float y = 0.0f;
  
  float r = 0.0f;
  float g = 0.0f;
  float b = 0.0f;

  void* uniform_ref = nullptr;
  void* shader_ref = nullptr;

  void init();
public:
  Point(float x = 0.0f, float y = 0.0f, float r = 1.0f, float g = 1.0f, float b = 1.0f);
  ~Point();

  std::array<float, 2> getPos();
  void setPos(float x, float y);

  std::array<float, 3> getColors();
  void setColors(float r, float g, float b);

  void drawPoint();
};
};