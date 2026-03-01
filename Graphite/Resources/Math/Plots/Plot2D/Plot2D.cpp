// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#include "Plot2D.h"


void Graphite::Math::Plot2D::drawPoint(const std::string& cell_name, Graphite::Math::Point point){
  
  if(!point.getUpdatedState()){
    std::pair<std::array<std::vector<float>, 2>, std::vector<unsigned int>> mesh_data = point.getMesh(); 
    
    CW::Renderer::Mesh mesh(mesh_data.first[0], mesh_data.second);
    mesh.addColors(mesh_data.first[1]);

    meshes["p: " + cell_name] = mesh;
  };

  shader->bind();
  meshes["p: " + cell_name].render();
  shader->unbind();

};






void Graphite::Math::Plot2D::drawLine(const std::string& cell_name, Graphite::Math::Line line){
  
  if(!line.getUpdatedState()){
    std::pair<std::array<std::vector<float>, 2>, std::vector<unsigned int>> mesh_data = line.getMesh(); 

    CW::Renderer::Mesh mesh(mesh_data.first[0], mesh_data.second);
    mesh.addColors(mesh_data.first[1]);
    meshes["l: " + cell_name] = mesh;
  }

  shader->bind();
  meshes["l: " + cell_name].render();
  shader->unbind();
};






void Graphite::Math::Plot2D::drawMultiLine(const std::string &cell_name, Graphite::Math::MultiLine line){
  if(!line.getUpdatedState()){
    std::pair<std::array<std::vector<float>, 2>, std::vector<unsigned int>> mesh_data = line.getMesh();

    CW::Renderer::Mesh mesh(mesh_data.first[0], mesh_data.second);
    mesh.addColors(mesh_data.first[1]);

    meshes["ml: " + cell_name] = mesh;
  };
  
  shader->bind();
  meshes["ml: " + cell_name].render();
  shader->unbind();
};





Graphite::Math::Plot2D::Plot2D(){
  uniform = new CW::Renderer::Uniform;
  shader = new CW::Renderer::DrawShader(vertexFillShader, fragmentFillShader);
  shader->getUniforms().emplace_back(uniform);

  pre_mesh = new CW::Renderer::Mesh({
    -1.0f, -1.0f, 0.1f,
    1.0f, -1.0f, 0.1f,
    -1.0f, 1.0f, 0.1f,
    1.0f, 1.0f, 0.1f
  },{
    0, 1, 2,
    1, 2, 3
  });

  pre_shader = new CW::Renderer::DrawShader(vertexPreShader, fragmentPreShader);
  pre_shader->getUniforms().emplace_back(uniform);

  zoom = 10.0f / (1.0f / window_size[0]);
};






Graphite::Math::Plot2D::~Plot2D() {
  point_cell.clear();
  line_cell.clear();
  meshes.clear();
  delete uniform;
  delete shader;

  delete pre_shader;
  delete pre_mesh;
};






void Graphite::Math::Plot2D::draw(){
  (*uniform)["camera_pos"]->set<glm::vec2>({this->pos[0], this->pos[1]});
  (*uniform)["camera_zoom"]->set<float>(zoom);
  (*uniform)["window_size"]->set<glm::vec2>({window_size[0], window_size[1]});

  pre_shader->bind();
  pre_mesh->render();
  pre_shader->unbind();

  for(std::pair<std::string, Graphite::Math::MultiLine> el : multi_line_cell){
    drawMultiLine(el.first, el.second);
  };

  for(std::pair<std::string, Graphite::Math::Line> el : line_cell){
    drawLine(el.first, el.second);
  };

  for(std::pair<std::string, Graphite::Math::Point> el : point_cell){
    drawPoint(el.first, el.second);
  };
};






void Graphite::Math::Plot2D::plotEvents() {
  pos[0] += d_pos[0] / zoom;
  pos[1] += d_pos[1] / zoom;
  
  zoom += d_zoom * zoom;

  if(zoom > MAXZOOM)
    zoom = MAXZOOM;

  if(zoom < MINZOOM)
    zoom = MINZOOM;
};