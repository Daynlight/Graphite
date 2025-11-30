#pragma once

namespace Graphite::Math{
class Point{
public:
  Point(float x = 0.0f, float y = 0.0f, float r = 1.0f, float g = 1.0f, float b = 1.0f);
  void drawPoint();
};
};