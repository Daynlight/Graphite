// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#pragma once
#include <array>


namespace Graphite::Math{
class Line{
private:
  std::array<float, 2> pos1 = {0.0f, 0.0f};
  std::array<float, 2> pos2 = {0.0f, 0.0f};
  std::array<float, 3> color = {1.0f, 1.0f, 1.0f};

  bool updated = false;

public:
  Line(std::array<float, 2> pos1 = {0.0f, 0.0f}, std::array<float, 2> pos2 = {0.0f, 0.0f}, std::array<float, 3> color = {1.0f, 1.0f, 1.0f});
  ~Line();

  std::pair<std::array<float, 2>, std::array<float, 2>> getPos();
  void setPos(std::array<float, 2> pos1, std::array<float, 2> pos2);

  std::array<float, 3> getColor();
  void setColor(std::array<float, 3> color);

  bool getUpdatedState();
};
};