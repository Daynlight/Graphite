// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#include "Plot2D.h"


void Graphite::Math::Plot2D::drawPoint(const std::string& cell_name, Graphite::Math::Point point){
  
  if(!point.getUpdatedState()){
    float point_size = 5;

    std::array<float, 2> pos = point.getPos();

    std::vector<float> vertices =
    {
      pos[0] - point_size,  pos[1] + point_size, 0.0f,
      pos[0] - point_size, pos[1] - point_size, 0.0f,
      pos[0] + point_size,  pos[1] + point_size, 0.0f,
      pos[0] + point_size, pos[1] - point_size, 0.0f,
    };
    
    std::vector<unsigned int> indicies = 
    {
      0, 1, 2,
      1, 3, 2
    };
    
    CW::Renderer::Mesh mesh(vertices, indicies);
    meshes[cell_name] = mesh;
  };

  shader->bind();
  meshes[cell_name].render();
  shader->unbind();

};






Graphite::Math::Plot2D::Plot2D(){
  uniform = new CW::Renderer::Uniform;
  shader = new CW::Renderer::DrawShader(vertexPointShader, fragmentPointShader);
  shader->getUniforms().emplace_back(uniform);
};






Graphite::Math::Plot2D::~Plot2D() {
  point_cell.clear();
  meshes.clear();
  delete uniform;
  delete shader;
};






void Graphite::Math::Plot2D::draw(){
  (*uniform)["camera_pos"]->set<glm::vec2>({this->pos[0], this->pos[1]});
  (*uniform)["camera_zoom"]->set<float>(zoom);
  (*uniform)["window_size"]->set<glm::vec2>({window_size[0], window_size[1]});

  for(std::pair<std::string, Graphite::Math::Point> el : point_cell){
    drawPoint(el.first, el.second);
  };
};






void Graphite::Math::Plot2D::plotEvents() {
  pos[0] += d_pos[0];
  pos[1] += d_pos[1];
  zoom += d_zoom;
};