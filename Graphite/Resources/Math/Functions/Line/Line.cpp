// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#include "Line.h"


Graphite::Math::Line::Line(std::array<float, 2> pos1, std::array<float, 2> pos2, std::array<float, 3> color)
  : pos1(pos1), pos2(pos2), color(color), updated(false) {};







Graphite::Math::Line::~Line() {};







std::pair<std::array<float, 2>, std::array<float, 2>> Graphite::Math::Line::getPos(){
  return {pos1, pos2};
};







void Graphite::Math::Line::setPos(std::array<float, 2> pos1, std::array<float, 2> pos2) {
  this->pos1 = pos1;
  this->pos2 = pos2;
  updated = false;
};







std::array<float, 3> Graphite::Math::Line::getColor(){
  return color;
};







void Graphite::Math::Line::setColor(std::array<float, 3> color) {
  this->color = color;
};







bool Graphite::Math::Line::getUpdatedState(){
  if(!updated){
    updated = true;
    return false;
  };

  return true;
};