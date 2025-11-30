#include "Point.h"

Graphite::Math::Point::Point(float x, float y, float r, float g, float b)
  :x(x), y(y), r(r), g(g), b(b), shader(CW::Renderer::DrawShader(vertexPointShader, fragmentPointShader)){

  uniform["color"]->set<glm::vec3>({r, g, b});
  uniform["pos"]->set<glm::vec2>({x, y});

  shader.getUniforms().emplace_back(&uniform);

  shader.compile();
};








void Graphite::Math::Point::drawPoint(){
  shader.bind();
  canvas->render();
  shader.unbind();
};