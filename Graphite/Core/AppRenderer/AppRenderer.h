// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.

#pragma once

#include "Renderer.h"

#include <functional>


namespace Graphite{
class AppRenderer{
private:
  CW::Renderer::Renderer renderer;
public:
  AppRenderer();
  ~AppRenderer();

  void renderFrame(std::function<void()> fun);
  bool isRunning();
};
};