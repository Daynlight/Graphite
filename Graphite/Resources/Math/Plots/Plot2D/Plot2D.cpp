// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#include "Plot2D.h"


void Graphite::Math::Plot2D::drawPoint(const std::string& cell_name, Graphite::Math::Point point){
  
  if(!point.getUpdatedState()){
    std::pair<std::vector<float>, std::vector<unsigned int>> mesh_data = point.generateMesh();
    CW::Renderer::Mesh mesh(mesh_data.first, mesh_data.second);
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