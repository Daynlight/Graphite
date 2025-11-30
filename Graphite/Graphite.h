#pragma once

#include "Globals.h"
#include "Renderer.h"
#include "ScriptController/ScriptController.h"

#include <unordered_map>
#include <filesystem>
#include <fstream>


bool verbose_mode = 0;


namespace Graphite{
class App{
private:
  std::unordered_map<const char*, bool> flags;
  
private:
  void initFile(const char* filename, const char* data);
  void init();
  void help();
  void verbose();

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








void Graphite::App::help() {
  printf(R"(Graphite
Author:
  Daynlight.

Contact:
  Email: Danielstodulski000@gmail.com
  Github: https://github.com/daynlight

Commands:
  -h/--help: show program help command.
  -i/--init: initialize default files.
  -v/-d/--verbose/--debug: turn on verbose mode.
)");
};








void Graphite::App::verbose() {
  verbose_mode = 1;
};








void Graphite::App::run(int args, const char *argv[]){
  for(int i = 1; i < args; i++){
    if(strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--init") == 0)
      flags["init"] = 1;
    if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
      flags["help"] = 1;
    if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0 ||
       strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0)
      flags["verbose"] = 1;
  };
  
  if(flags["init"]) init();
  if(flags["help"]) help();
  if(flags["verbose"]) verbose();
  
  if(!flags["help"])
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