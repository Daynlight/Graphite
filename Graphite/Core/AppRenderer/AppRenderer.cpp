// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#include "AppRenderer.h"


Graphite::AppRenderer::AppRenderer(){
  renderer.setWindowTitle("Graphite");

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
};








bool Graphite::AppRenderer::isRunning(){
  return !renderer.getWindowData()->should_close;
};








void Graphite::AppRenderer::renderFrame(std::function<void()> fun){
  renderer.beginFrame();

  fun();

  renderer.swapBuffer();
  renderer.windowEvents();
};