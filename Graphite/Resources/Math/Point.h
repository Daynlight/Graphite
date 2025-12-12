// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#pragma once
#ifndef BUILDING_SCRIPT_DLL
  #include "Renderer.h"
  #include "PointShader.h"
  #include "Resources/Math/iMath.h"
#else
  #include "Graphite/iMath.h"
#endif


#include <array>


namespace Graphite::Math{
class Point : iMath2D{
private:
  std::array<float, 2> pos = {0.0f, 0.0f};
  
  std::array<float, 3> color = {1.0f, 1.0f, 1.0f};

  void* uniform_ref = nullptr;
  void* shader_ref = nullptr;
  void* mesh_ref = nullptr;

  void init();

public:
  Point(std::array<float, 2> pos = {0.0f, 0.0f}, std::array<float, 3> color = {1.0f, 1.0f, 1.0f});
  ~Point();

  std::array<float, 2> getPos();
  void setPos(std::array<float, 2> pos);

  std::array<float, 3> getColor();
  void setColor(std::array<float, 3> color);

  void drawPoint();

  std::array<float, 2> get(float t = 0.0f) const;

  operator iMath2D*();
};
};