// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#include "Graphite.h"
#include "Gui.h"

bool verbose_mode = 0;
bool sandbox_mode = 0;

std::array<float, 2> d_pos = {0.0f, 0.0f};
float d_zoom = 1.0f;
std::array<float, 2> window_size = {1.0f, 1.0f};


int main(int args, const char* argv[]){
  Graphite::Graphite graphite;

  graphite.run(args, argv);

  return 0;
};















////////////////////////////////////////////////////////////
//////////////////////// Main Entry ////////////////////////
////////////////////////////////////////////////////////////
void Graphite::Graphite::run(int args, const char *argv[]){
  detectFlags(args, argv);

  if(!std::filesystem::exists(path / ScriptName))
    printf("File %s didn't exists\n", (path / ScriptName).string().c_str());
    
  executeFlags();

  if(!flags["help"])
    runProgram();
};








void Graphite::Graphite::calculateDeltas(AppRenderer* renderer){
  d_pos = renderer->getDPos();
  d_zoom = renderer->getDZoom();
};








void Graphite::Graphite::calculateWindowSize(AppRenderer *renderer) {
  std::array<unsigned int, 2> temp_window_size = renderer->getWindowSize();
  window_size[0] = temp_window_size[0];
  window_size[1] = temp_window_size[1];
};


inline const std::function<void(CW::Renderer::iRenderer *renderer)> fpsGui(){
  return [](CW::Renderer::iRenderer* renderer){
    ImGui::Text("fps: %f", 1 / renderer->getWindowData()->delta_time);
  };
};




void Graphite::Graphite::runProgram(){
  AppRenderer renderer;
  CW::Gui::Gui gui(renderer.renderer);
  ScriptLoader script(path);

  gui.addWindow("FPS", fpsGui());


  while(renderer.isRunning()){
    
    calculateDeltas(&renderer);
    calculateWindowSize(&renderer);
    
    if(script.checkLastWrite()) 
    script.updateScript();
    
    script.update();
    
    renderer.renderFrame([&script, &gui](){
      script.draw();
      if(verbose_mode)
        gui.render();
    });


  };
};