#include "Point.h"

Graphite::Math::Point::Point(float x, float y, float r, float g, float b)
  :x(x), y(y), r(r), g(g), b(b){

  uniform_ref = (void*)new CW::Renderer::Uniform();
  shader_ref = (void*)new CW::Renderer::DrawShader(vertexPointShader, fragmentPointShader);

  CW::Renderer::Uniform* u = (CW::Renderer::Uniform*)uniform_ref;
  CW::Renderer::DrawShader* s = (CW::Renderer::DrawShader*)shader_ref;

  (*u)["color"]->set<glm::vec3>({r, g, b});
  (*u)["pos"]->set<glm::vec2>({x, y});

  s->getUniforms().emplace_back(u);
};








void Graphite::Math::Point::drawPoint(){
  CW::Renderer::DrawShader* s = (CW::Renderer::DrawShader*)shader_ref;
  s->bind();
  canvas->render();
  s->unbind();
};