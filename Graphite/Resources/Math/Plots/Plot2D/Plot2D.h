// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#pragma once
#ifndef BUILDING_SCRIPT_DLL
  #include "Mesh/Mesh.h"
  #include "Shader/DrawShader.h"
  #include "Uniform/Uniform.h"
  #include "Resources/Math/Functions/Point/Point.h"
  #include "Resources/Math/Functions/Line/Line.h"
  #include "Resources/Math/Shader.h"
  #include "Globals.h"

  CW::Renderer::DrawShader* shader;
  CW::Renderer::Uniform* uniform;
  std::unordered_map<std::string, CW::Renderer::Mesh> meshes;
#else
  #include "Graphite/Point.h"
  #include "Graphite/Line.h"
#endif


#include <string>
#include <unordered_map>


namespace Graphite::Math{
class Plot2D{
public:
  std::unordered_map<std::string, Graphite::Math::Point> point_cell;
  std::unordered_map<std::string, Graphite::Math::Line> line_cell;

private:
  void drawPoint(const std::string& cell_name, Graphite::Math::Point point);
  void drawLine(const std::string& cell_name, Graphite::Math::Line line);

  std::array<float, 2> pos = {0.0f, 0.0f};
  float zoom = 1.0f;

public:
  Plot2D();
  ~Plot2D();

  void draw();
  
  void plotEvents();
};
};