// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#include "Point.h"


void Graphite::Math::Point::init(){
  CW::Renderer::Uniform* u = (CW::Renderer::Uniform*)uniform_ref;
  CW::Renderer::DrawShader* s = (CW::Renderer::DrawShader*)shader_ref;

  u->clear();
  s->getUniforms().clear();

  (*u)["pos"]->set<glm::vec2>({pos[0], pos[1]});
  (*u)["color"]->set<glm::vec3>({color[0], color[1], color[2]});

  s->getUniforms().emplace_back(u);
};







Graphite::Math::Point::Point(std::array<float, 2> pos, std::array<float, 3> color)
  : pos(pos), color(color){

  uniform_ref = (void*)new CW::Renderer::Uniform();
  shader_ref = (void*)new CW::Renderer::DrawShader(vertexPointShader, fragmentPointShader);
  mesh_ref = (void*)new CW::Renderer::Mesh({
    -1.0f,  1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
    1.0f,  1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
  }, 
  {
    0, 1, 2,
    1, 3, 2
  });

  init();
};







Graphite::Math::Point::~Point() {
  CW::Renderer::Uniform* u = (CW::Renderer::Uniform*)uniform_ref;
  CW::Renderer::DrawShader* s = (CW::Renderer::DrawShader*)shader_ref;
  CW::Renderer::Mesh* m = (CW::Renderer::Mesh*)mesh_ref;

  delete m;
  delete s;
  delete u;
};







std::array<float, 2> Graphite::Math::Point::getPos(){
  return pos;
};







void Graphite::Math::Point::setPos(std::array<float, 2> pos) {
  this->pos = pos;

  init();
};







std::array<float, 3> Graphite::Math::Point::getColor(){
  return color;
};







void Graphite::Math::Point::setColor(std::array<float, 3> color) {
  this->color = color;
  
  init();
};







void Graphite::Math::Point::drawPoint(){
  CW::Renderer::DrawShader* s = (CW::Renderer::DrawShader*)shader_ref;
  CW::Renderer::Mesh* m = (CW::Renderer::Mesh*)mesh_ref; 

  s->bind();
  m->render();
  s->unbind();
};







std::array<float, 2> Graphite::Math::Point::get(float t) const{
  return pos;
};







Graphite::Math::Point::operator iMath2D*() {
  return this;
};
