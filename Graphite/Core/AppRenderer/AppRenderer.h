// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#pragma once

#include "Renderer.h"


namespace Graphite{
class AppRenderer{
private:
  CW::Renderer::iRenderer* renderer;

public:
  AppRenderer();
  ~AppRenderer();

  template<typename F>
  void renderFrame(F&& fun);
  bool isRunning();

};
};

#include "AppRenderer.hpp"