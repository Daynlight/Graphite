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
  #include "Globals.h"

  CW::Renderer::DrawShader* shader;
  CW::Renderer::Uniform* uniform;
  std::unordered_map<std::string, CW::Renderer::Mesh> meshes;
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
  void drawPoint(const std::string& cell_name, Graphite::Math::Point point);
  std::array<float, 2> pos = {0.0f, 0.0f};
  float zoom = 1.0f;

public:
  Plot2D();
  ~Plot2D();

  void draw();
  
  void plotEvents();
};
};