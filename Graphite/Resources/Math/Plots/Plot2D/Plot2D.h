// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#pragma once
#ifndef BUILDING_SCRIPT_DLL
  #include "Mesh/Mesh.h"
  #include "Shader/DrawShader.h"
  #include "Uniform/Uniform.h"
  #include "Resources/Math/Point/Point.h"
  #include "Resources/Math/Point/PointShader.h"

  CW::Renderer::Mesh* viewport = nullptr;
  CW::Renderer::DrawShader* shader;
#else
  #include "Graphite/Point.h"
#endif


#include <string>
#include <unordered_map>


namespace Graphite::Math{
class Plot2D{
public:
  std::unordered_map<std::string, Graphite::Math::Point> point_cell;

private:
  void drawPoint(Graphite::Math::Point point);

public:
  Plot2D();
  ~Plot2D();

  void draw();

};
};