// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#include "AppRenderer.h"


Graphite::AppRenderer::AppRenderer()
  :renderer(new CW::Renderer::Renderer)
{
  if(!renderer){
    printf("Can't initialize renderer from CWindow\n");
    exit(-1);
  };

  renderer->setWindowTitle("Graphite");

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
};








Graphite::AppRenderer::~AppRenderer(){
  delete renderer;
};








bool Graphite::AppRenderer::isRunning(){
  return !renderer->getWindowData()->should_close;
};








template<typename F>
void Graphite::AppRenderer::renderFrame(F&& fun){
  renderer->beginFrame();

  fun();

  renderer->swapBuffer();
  renderer->windowEvents();
};