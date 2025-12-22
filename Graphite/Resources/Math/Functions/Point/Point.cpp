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







bool Graphite::Math::Point::getUpdatedState(){
  if(!updated){
    updated = true;
    return false;
  };

  return true;
};