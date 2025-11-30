#pragma once
#include "Renderer.h"
#include "Globals.h"

#include "PointShader.h"


CW::Renderer::DrawShader shader(CW::Renderer::DrawShader(vertexPointShader, fragmentPointShader));
CW::Renderer::Uniform uniform;


namespace Graphite::Math{
class Point{
private:
  float x = 0.0f;
  float y = 0.0f;
  
  float r = 0.0f;
  float g = 0.0f;
  float b = 0.0f;

public:
  Point(float x = 0.0f, float y = 0.0f, float r = 1.0f, float g = 1.0f, float b = 1.0f);

  void drawPoint();

};
};