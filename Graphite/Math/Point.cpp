#include "Point.h"

Graphite::Math::Point::Point(float x, float y, float r, float g, float b)
  :x(x), y(y), r(r), g(g), b(b){
};








void Graphite::Math::Point::drawPoint(){
  shader.getUniforms().clear();
  uniform["color"]->set<glm::vec3>({r, g, b});
  uniform["pos"]->set<glm::vec2>({x, y});
  shader.getUniforms().emplace_back(&uniform);
  shader.compile();

  shader.bind();
  canvas->render();
  shader.unbind();
};