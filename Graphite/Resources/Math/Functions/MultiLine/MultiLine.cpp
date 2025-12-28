// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#include "MultiLine.h"


Graphite::Math::MultiLine::MultiLine(std::vector<std::array<float, 2>> points, float size, std::array<float, 3> color)
  : points(points), size(size), color(color), updated(false) {};







Graphite::Math::MultiLine::~MultiLine() {};







std::vector<std::array<float, 2>> Graphite::Math::MultiLine::getPoints(){
  return points;
};







void Graphite::Math::MultiLine::setPoints(std::vector<std::array<float, 2>> points) {
  this->points = points;
  updated = false;
};







float Graphite::Math::MultiLine::getSize(){
  return size;
};







void Graphite::Math::MultiLine::setSize(float size){
  this->size = size;
  updated = false;
};







std::array<float, 3> Graphite::Math::MultiLine::getColor(){
  return color;
};







void Graphite::Math::MultiLine::setColor(std::array<float, 3> color) {
  this->color = color;
  updated = false;
};







bool Graphite::Math::MultiLine::getUpdatedState(){
  if(!updated){
    updated = true;
    return false;
  };

  return true;
};







std::vector<std::pair<std::array<std::vector<float>, 2>, std::vector<unsigned int>>> Graphite::Math::MultiLine::getMesh(){
  std::vector<std::pair<std::array<std::vector<float>, 2>, std::vector<unsigned int>>> meshes;
  meshes.reserve(points.size());
  Graphite::Math::Line line;

  for (int i = 1; i < points.size(); i++){
    line = Graphite::Math::Line(points[i - 1], points[i], size, color);
    meshes.emplace_back(line.getMesh());
  };
  
  return meshes;
};