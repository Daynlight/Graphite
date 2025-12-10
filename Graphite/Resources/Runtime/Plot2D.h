// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#include "Math.h"

#include <string>
#include <unordered_map>


namespace Graphite::Math{
class Plot2D{

public:
  std::unordered_map<std::string, const iMath2D*> cell; 

public:
  Plot2D();

  void draw();

};
};