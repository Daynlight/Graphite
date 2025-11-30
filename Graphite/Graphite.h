#pragma once

#include "Renderer.h"
#include "ScriptController/ScriptController.h"

#include <unordered_map>
#include <filesystem>
#include <fstream>


namespace Graphite{
class App{
private:
  std::unordered_map<const char*, bool> flags;
  
private:
  void init();
  void initFile(const char* filename, const char* data);

public:
  void run(int args, const char* argv[]);
  void runProgram();


};
};















void Graphite::App::initFile(const char* filename, const char* data){
  std::ofstream out(filename, std::ios::out | std::ios::binary);
  if (!out) {
    printf("Failed to wite!\n");
    return;
  };
  out << data;
  out.close();
};








void Graphite::App::init() {
  #include "Template/MainTemplate.h"
  #include "Template/ScriptInterface.h"

  initFile("Main.cpp", MainTemplate);
  initFile("ScriptInterface.h", ScriptInterfaceTemplate);
};








void Graphite::App::run(int args, const char *argv[]){
  for(int i = 1; i < args; i++){
    if(strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--init") == 0)
      flags["init"] = 1;
  };
  
  if(flags["init"]) init();
  
  
  runProgram();
};








void Graphite::App::runProgram(){
  CW::Renderer::Renderer renderer;
  renderer.setWindowTitle("Graphite");

  Graphite::ScriptLoader script("Main");


  while(!renderer.getWindowData()->should_close){
    renderer.beginFrame();

    script.checkLastWrite();

    script.update();

    renderer.swapBuffer();
    renderer.windowEvents();
  };

};