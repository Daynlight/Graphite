#pragma once

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

public:
  Point(float x = 0.0f, float y = 0.0f, float r = 1.0f, float g = 1.0f, float b = 1.0f);
  void drawPoint();
};
};