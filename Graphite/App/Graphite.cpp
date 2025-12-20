// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#include "Graphite.h"

bool verbose_mode = 0;
bool sandbox_mode = 0;

std::array<float, 2> d_pos = {0.0f, 0.0f};
float d_zoom = 1.0f;


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








void Graphite::Graphite::runProgram(){
  AppRenderer renderer;
  ScriptLoader script(path);


  while(renderer.isRunning()){
    calculateDeltas(&renderer);

    if(script.checkLastWrite()) 
      script.updateScript();

    script.update();

    renderer.renderFrame([&script](){
      script.draw();
    });
  };
};