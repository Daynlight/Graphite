// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.

#pragma once

#include "Globals.h"
#include "Renderer.h"
#include "Core/ScriptController/ScriptController.h"

#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <string>


bool verbose_mode = 0;
CW::Renderer::Renderer* renderer = nullptr;

std::string path = "./";


namespace Graphite{
class Graphite{
private:
  std::unordered_map<const char*, bool> flags;
  
private:
  void initFile(const char* filename, const char* data);
  void init();
  void help();
  void verbose();

  void longFlags(const char* argv);
  void shortFlags(const char* argv);
  void detectPath(const char* argv);
  void detectFlags(int args, const char* argv[]);

  void executeFlags();

public:
  void run(int args, const char* argv[]);
  void runProgram();


};
};






















////////////////////////////////////////////////////////////
////////////////////// Flag Execution //////////////////////
////////////////////////////////////////////////////////////
void Graphite::Graphite::executeFlags(){
  if(!std::filesystem::exists(path + "Graphite.cpp"))
    flags["init"] = 1;

  if(flags["init"]) init();
  if(flags["help"]) help();
  if(flags["verbose"]) verbose();
};








void Graphite::Graphite::initFile(const char* filename, const char* data){
  std::ofstream out(filename, std::ios::out | std::ios::binary);
  if (!out) {
    printf("Failed to wite!\n");
    return;
  };
  out << data;
  out.close();
};








void Graphite::Graphite::init() {
  if(!std::filesystem::exists(path))
    std::filesystem::create_directories(path);
  
  #include "../Resources/Templates/Main.h"
  
  if(!std::filesystem::exists(path + "Graphite.cpp"))
    initFile((path + "Graphite.cpp").c_str(), GraphiteTemplate);
};








void Graphite::Graphite::help() {
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








void Graphite::Graphite::verbose() {
  verbose_mode = 1;
};















////////////////////////////////////////////////////////////
////////////////////// Flag Detection //////////////////////
////////////////////////////////////////////////////////////
void Graphite::Graphite::longFlags(const char* argv){
  if(strcmp(argv, "--init") == 0)
    flags["init"] = 1;
  if(strcmp(argv, "--help") == 0)
    flags["help"] = 1;
  if(strcmp(argv, "--verbose") == 0 ||
    strcmp(argv, "--debug") == 0)
    flags["verbose"] = 1;
};








void Graphite::Graphite::shortFlags(const char* argv){
  unsigned int len = strlen(argv);
  for(int j = 1; j < len; j++){
    if(argv[j] == 'i') flags["init"] = 1;
    if(argv[j] == 'h') flags["help"] = 1;
    if(argv[j] == 'v') flags["verbose"] = 1;
    if(argv[j] == 'd') flags["verbose"] = 1;
  };
};








void Graphite::Graphite::detectPath(const char* argv){
  path = std::string(argv); 
  if(path[path.size() - 1] != '/')
    path += "/";
};








void Graphite::Graphite::detectFlags(int args, const char *argv[]){
  for(int i = 1; i < args; i++){
    if(strcmp(argv[i], "--") == 0) longFlags(argv[i]);
    else if(argv[i][0] == '-') shortFlags(argv[i]);
    else detectPath(argv[i]);
  };
};















////////////////////////////////////////////////////////////
//////////////////////// Main Entry ////////////////////////
////////////////////////////////////////////////////////////
void Graphite::Graphite::run(int args, const char *argv[]){
  detectFlags(args, argv);

  executeFlags();

  if(!flags["help"])
    runProgram();
};








void Graphite::Graphite::runProgram(){
  renderer = new CW::Renderer::Renderer();
  renderer->setWindowTitle("Graphite");

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


  ScriptLoader script(path);


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