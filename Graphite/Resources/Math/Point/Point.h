// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#pragma once
#include <array>
#include <vector>


namespace Graphite::Math{
class Point{
private:
  std::array<float, 2> pos = {0.0f, 0.0f};
  std::array<float, 3> color = {1.0f, 1.0f, 1.0f};

  bool updated = false;

public:
  Point(std::array<float, 2> pos = {0.0f, 0.0f}, std::array<float, 3> color = {1.0f, 1.0f, 1.0f});
  ~Point();

  std::array<float, 2> getPos();
  void setPos(std::array<float, 2> pos);

  std::array<float, 3> getColor();
  void setColor(std::array<float, 3> color);

  bool getUpdatedState();
};
};