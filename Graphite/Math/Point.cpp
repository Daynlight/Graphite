#include "Point.h"

void Graphite::Math::Point::init(){
  CW::Renderer::Uniform* u = (CW::Renderer::Uniform*)uniform_ref;
  CW::Renderer::DrawShader* s = (CW::Renderer::DrawShader*)shader_ref;

  u->clear();
  s->getUniforms().clear();

  (*u)["color"]->set<glm::vec3>({r, g, b});
  (*u)["pos"]->set<glm::vec2>({x, y});

  s->getUniforms().emplace_back(u);
};







Graphite::Math::Point::Point(float x, float y, float r, float g, float b)
    : x(x), y(y), r(r), g(g), b(b){

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

  CW::Renderer::Mesh* m = (CW::Renderer::Mesh*)mesh_ref;
  m->compile();

  init();
};







Graphite::Math::Point::~Point() {
  CW::Renderer::Uniform* u = (CW::Renderer::Uniform*)uniform_ref;
  CW::Renderer::DrawShader* s = (CW::Renderer::DrawShader*)shader_ref;

  if(u) 
    delete u;

  if(s) 
    delete s;
};







std::array<float, 2> Graphite::Math::Point::getPos(){
  std::array<float, 2> pos = {x, y};
  return pos;
};







void Graphite::Math::Point::setPos(float x, float y) {
  this->x = x;
  this->y = y;

  init();
};







std::array<float, 3> Graphite::Math::Point::getColors(){
  std::array<float, 3> colors = {r, g, b};
  return colors;
};







void Graphite::Math::Point::setColors(float r, float g, float b) {
  this->r = r;
  this->g = g;
  this->b = b;
  
  init();
};







void Graphite::Math::Point::drawPoint(){
  CW::Renderer::DrawShader* s = (CW::Renderer::DrawShader*)shader_ref;
  CW::Renderer::Mesh* m = (CW::Renderer::Mesh*)mesh_ref; 

  s->bind();
  m->render();
  s->unbind();
};