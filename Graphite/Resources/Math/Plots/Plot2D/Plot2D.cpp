// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#include "Plot2D.h"


void Graphite::Math::Plot2D::drawPoint(Graphite::Math::Point point){

  CW::Renderer::Mesh viewport = CW::Renderer::Mesh(
  {
    -1.0f,  1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
    1.0f,  1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
  }, 
  {
    0, 1, 2,
    1, 3, 2
  });
  
  CW::Renderer::DrawShader shader = CW::Renderer::DrawShader(vertexPointShader, fragmentPointShader);

  std::array<float, 2> pos = point.getPos();
  std::array<float, 3> color = point.getColor();
  
  CW::Renderer::Uniform uniform;
  shader.getUniforms().emplace_back(&uniform);
  uniform["pos"]->set<glm::vec2>({pos[0], pos[1]});
  uniform["color"]->set<glm::vec3>({color[0], color[1], color[2]});

  uniform["camera_pos"]->set<glm::vec2>({this->pos[0], this->pos[1]});
  uniform["camera_zoom"]->set<float>(zoom);
  uniform["window_size"]->set<glm::vec2>({window_size[0], window_size[1]});

  shader.bind();
  viewport.render();
  shader.unbind();
  
  shader.getUniforms().clear();
};






Graphite::Math::Plot2D::Plot2D(){
};






Graphite::Math::Plot2D::~Plot2D() {
  point_cell.clear();
};






void Graphite::Math::Plot2D::draw(){
  for(std::pair<std::string, Graphite::Math::Point> el : point_cell)
    drawPoint(el.second);
};






void Graphite::Math::Plot2D::plotEvents() {
  pos[0] += d_pos[0];
  pos[1] += d_pos[1];
  zoom += d_zoom;
};