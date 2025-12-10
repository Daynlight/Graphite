// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#include "Plot2D.h"


Graphite::Math::Plot2D::Plot2D(){

};






Graphite::Math::Plot2D::~Plot2D() {
  for(std::pair<std::string, const iMath2D*> el : cell)
    delete el.second;
};






void Graphite::Math::Plot2D::draw(){
  for(std::pair<std::string, const iMath2D*> el : cell)
    printf("[%f, %f]\n", el.second->get()[0], el.second->get()[1]);
};
