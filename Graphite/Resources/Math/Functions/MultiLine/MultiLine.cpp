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







std::pair<std::array<std::vector<float>, 2>, std::vector<unsigned int>> Graphite::Math::MultiLine::getMesh(){
  std::pair<std::array<std::vector<float>, 2>, std::vector<unsigned int>> mesh;

  mesh.first[0].reserve(points.size() * 3 * 4);
  mesh.first[1].reserve(points.size() * 3 * 4);
  mesh.second.reserve(points.size() * 6);

  
  Graphite::Math::Line line;
  std::pair<std::array<std::vector<float>, 2>, std::vector<unsigned int>> mesh_temp;


  for (int i = 1; i < points.size(); i++){
    line = Graphite::Math::Line(points[i - 1], points[i], size, color);
    mesh_temp = line.getMesh();

    for(int j = 0; j < 4 * 3; j++)
      mesh.first[0].emplace_back(mesh_temp.first[0][j]);
      
    for(int j = 0; j < 4 * 3; j++)
      mesh.first[1].emplace_back(mesh_temp.first[1][j]);
    
    for(int j = 0; j < 3 * 2; j++)
      mesh.second.emplace_back((i - 1) * 4 + mesh_temp.second[j]);
  };
  
  return mesh;
};