// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.

#pragma once
#ifndef BUILDING_SCRIPT_DLL
  #include "Renderer.h"
  #include "Resources/Math/iMath.h"
  #else
  #include "Graphite/Math.h"
  #include "Graphite/iMath.h"
#endif


#include <string>
#include <unordered_map>


namespace Graphite::Math{
class Plot2D{
private:
  std::unordered_map<std::string, iMath2D*> cell; 

public:
  Plot2D();
  ~Plot2D();

  void draw();
  
  iMath2D*& operator[](const std::string& name);
};
};