// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#include "Point.h"


Graphite::Math::Point::Point(std::array<float, 2> pos, std::array<float, 3> color)
  : pos(pos), color(color), updated(false) {};







Graphite::Math::Point::~Point() {};







std::array<float, 2> Graphite::Math::Point::getPos(){
  return pos;
};







void Graphite::Math::Point::setPos(std::array<float, 2> pos) {
  this->pos = pos;
  updated = false;
};







std::array<float, 3> Graphite::Math::Point::getColor(){
  return color;
};







void Graphite::Math::Point::setColor(std::array<float, 3> color) {
  this->color = color;
};







std::pair<std::vector<float>, std::vector<unsigned int>> Graphite::Math::Point::generateMesh(){
  float point_size = 5;

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

  updated = true;
  return {vertices, indicies};
};







bool Graphite::Math::Point::getUpdatedState(){
  return updated;
};