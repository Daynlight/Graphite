#pragma once

#include "Globals.h"
#include "Renderer.h"
#include "ScriptController/ScriptController.h"

#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <string>


bool verbose_mode = 0;
CW::Renderer::Renderer* renderer = nullptr;

std::string path = "./";


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
  if(!std::filesystem::exists(path))
    std::filesystem::create_directory(path);
  
  #include "Template/GraphiteTemplate.h"
  
  if(!std::filesystem::exists(path + "Graphite.cpp"))
    initFile((path + "Graphite.cpp").c_str(), GraphiteTemplate);
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
    if(strcmp(argv[i], "--") == 0){
      if(strcmp(argv[i], "--init") == 0)
        flags["init"] = 1;
      if(strcmp(argv[i], "--help") == 0)
        flags["help"] = 1;
      if(strcmp(argv[i], "--verbose") == 0 ||
        strcmp(argv[i], "--debug") == 0)
        flags["verbose"] = 1;
    }
    else if(argv[i][0] == '-'){
      unsigned int len = strlen(argv[i]);
      for(int j = 1; j < len; j++){
        if(argv[i][j] == 'i') flags["init"] = 1;
        if(argv[i][j] == 'h') flags["help"] = 1;
        if(argv[i][j] == 'v') flags["verbose"] = 1;
        if(argv[i][j] == 'd') flags["verbose"] = 1;
      };
    }
    else 
      path = std::string(argv[i]); 
      if(path[path.size() - 1] != '/')
        path += "/";
  };

  if(flags["init"]) init();
  if(flags["help"]) help();
  if(flags["verbose"]) verbose();
  
  if(!flags["help"])
    runProgram();
};








void Graphite::App::runProgram(){
  renderer = new CW::Renderer::Renderer();
  renderer->setWindowTitle("Graphite");

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


  Graphite::ScriptLoader script(path);


  while(!renderer->getWindowData()->should_close){
    renderer->beginFrame();

    script.checkLastWrite();

    script.update();

    renderer->swapBuffer();
    renderer->windowEvents();
  };

  script.~ScriptLoader();

  delete renderer;
};