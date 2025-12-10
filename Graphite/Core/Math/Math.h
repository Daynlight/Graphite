// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#include <array>


namespace Graphite{
class iMath2D{
public:
  virtual std::array<float, 2> get(float t = 0.0f) const = 0;

};
};