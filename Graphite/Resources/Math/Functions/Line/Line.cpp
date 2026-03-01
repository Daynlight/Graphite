// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#include "Line.h"


Graphite::Math::Line::Line(std::array<float, 2> pos1, std::array<float, 2> pos2, float size, std::array<float, 3> color)
  : pos1(pos1), pos2(pos2), size(size), color(color), updated(false) {};







Graphite::Math::Line::~Line() {};







std::pair<std::array<float, 2>, std::array<float, 2>> Graphite::Math::Line::getPos(){
  return {pos1, pos2};
};







void Graphite::Math::Line::setPos(std::array<float, 2> pos1, std::array<float, 2> pos2) {
  this->pos1 = pos1;
  this->pos2 = pos2;
  updated = false;
};







float Graphite::Math::Line::getSize(){
  return size;
};







void Graphite::Math::Line::setSize(float size){
  this->size = size;
  updated = false;
};







std::array<float, 3> Graphite::Math::Line::getColor(){
  return color;
};







void Graphite::Math::Line::setColor(std::array<float, 3> color) {
  this->color = color;
  updated = false;
};







bool Graphite::Math::Line::getUpdatedState(){
  if(!updated){
    updated = true;
    return false;
  };

  return true;
};







std::pair<std::array<std::vector<float>, 2>, std::vector<unsigned int>> Graphite::Math::Line::getMesh(){
  float thickness = size;

  std::pair<std::array<float, 2>, std::array<float, 2>> pos = getPos();

  auto& p0 = pos.first;
  auto& p1 = pos.second;

  float dx = p1[0] - p0[0];
  float dy = p1[1] - p0[1];
  float len = std::sqrt(dx*dx + dy*dy);
  float nx = -dy / len;
  float ny = dx / len;
  float tx = nx * (thickness * 0.5f);
  float ty = ny * (thickness * 0.5f);


  std::vector<float> vertices = {
    p0[0] + tx, p0[1] + ty, 0.01f,
    p0[0] - tx, p0[1] - ty, 0.01f,
    p1[0] + tx, p1[1] + ty, 0.01f,
    p1[0] - tx, p1[1] - ty, 0.01f 
  };

  std::vector<float> colors = {
    color[0], color[1], color[2],
    color[0], color[1], color[2],
    color[0], color[1], color[2],
    color[0], color[1], color[2],
  };

  std::vector<unsigned int> indicies = {
    0, 1, 2,
    1, 3, 2
  };
  
  return {{vertices, colors}, indicies};
};