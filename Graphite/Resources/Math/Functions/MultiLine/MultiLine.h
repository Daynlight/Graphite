// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#pragma once
#include <array>
#include <vector>

#include "Resources/Math/Functions/Line/Line.h"


namespace Graphite::Math{
class MultiLine{
private:
  std::vector<std::array<float, 2>> points;
  std::array<float, 3> color = {1.0f, 1.0f, 1.0f};

  float size = 1.0f;

  bool updated = false;

public:
  MultiLine(std::vector<std::array<float, 2>> points = {}, float size = 1.0f, std::array<float, 3> color = {1.0f, 1.0f, 1.0f});
  ~MultiLine();

  std::vector<std::array<float, 2>> getPoints();
  void setPoints(std::vector<std::array<float, 2>> points);

  float getSize();
  void setSize(float size);

  std::array<float, 3> getColor();
  void setColor(std::array<float, 3> color);

  bool getUpdatedState();

  std::vector<std::pair<std::array<std::vector<float>, 2>, std::vector<unsigned int>>> getMesh();

};
};