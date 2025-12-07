// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#pragma once

#include "Graphite.h"


////////////////////////////////////////////////////////////
////////////////////// Flag Detection //////////////////////
////////////////////////////////////////////////////////////
void Graphite::Graphite::longFlags(int* i, int args, const char* argv[]){
  if(*i >= args) return;

  if(strcmp(argv[*i], "--init") == 0)
    flags["init"] = 1;
  else if(strcmp(argv[*i], "--help") == 0)
    flags["help"] = 1;
  else if(strcmp(argv[*i], "--sandbox") == 0)
    flags["sandbox"] = 1;
  else if(strcmp(argv[*i], "--verbose") == 0 || strcmp(argv[*i], "--debug") == 0)
    flags["verbose"] = 1;
  else 
    printf("flag %s didn't exist\n", argv[*i]);
};








void Graphite::Graphite::shortFlags(int* i, int args, const char* argv[]){
  if(*i >= args) return;
  
  unsigned int len = strlen(argv[*i]);

  for(int j = 1; j < len; j++){
    if(argv[*i][j] == 'i') flags["init"] = 1;
    else if(argv[*i][j] == 'h') flags["help"] = 1;
    else if(argv[*i][j] == 's') flags["sandbox"] = 1;
    else if(argv[*i][j] == 'v' || argv[*i][j] == 'd') flags["verbose"] = 1;
    else printf("flag -%c didn't exist\n", argv[*i][j]);
  };
};








void Graphite::Graphite::detectPath(int* i, int args, const char* argv[]){
  if(*i >= args || *i < 1) return;
  
  std::string argv_path = argv[*i];
  
  if(!argv_path.empty() && argv_path.back() != '/')
    argv_path += "/";

  path = std::filesystem::path(argv_path);
};








void Graphite::Graphite::detectFlags(int args, const char *argv[]){
  flags["init"] = 0;
  flags["help"] = 0;
  flags["sandbox"] = 0;
  flags["verbose"] = 0;

  int i = 1;
  while(i < args) {
    if(i >= args) break;

    if(argv[i][0] == '-'){
       if(argv[i][1] == '-') longFlags(&i, args, argv);
       else shortFlags(&i, args, argv);
    }
    else detectPath(&i, args, argv);

    i++;
  };
};








////////////////////////////////////////////////////////////
////////////////////// Flag Execution //////////////////////
////////////////////////////////////////////////////////////
void Graphite::Graphite::executeFlags(){
  try {
    if (!std::filesystem::exists(path)) {
      std::filesystem::create_directories(path);
      printf("Directory %s created\n", path.string().c_str());
    };
  } catch (const std::filesystem::filesystem_error& e) {
    printf("Failed to create directory %s: %s\n", path.string().c_str(), e.what());
    return;
  };

  if(flags["init"]) init();
  if(flags["help"]) help();
  if(flags["verbose"]) verbose();
  if(flags["sandbox"]) sandbox();
};








void Graphite::Graphite::initFile(const std::string& filename, const char* data){
  if(!data){
    printf("Can't load template\n");
    return;
  };

  try {
    if (!std::filesystem::exists(path)) {
      std::filesystem::create_directories(path);
      printf("Directory %s created\n", path.string().c_str());
    }
  } catch (const std::filesystem::filesystem_error& e) {
    printf("Failed to create directory %s: %s\n", path.string().c_str(), e.what());
    return;
  }
  
  if(std::filesystem::exists(path / filename)){
    printf("File %s, already exists\n", (path / filename).string().c_str());
    return;
  };

  std::ofstream out(path / filename, std::ios::out | std::ios::binary);
  if (!out.is_open()) {
    printf("Can't open file %s!\n", (path / filename).string().c_str());
    out.close();
    return;
  };

  out << data;

  if (out.fail())
    printf("Failed to write data to %s\n", (path / filename).string().c_str());

  out.close();
};








void Graphite::Graphite::init() {
  initFile(ScriptName, GraphiteTemplate);
};








void Graphite::Graphite::help() {
  printf(R"(== Graphite ==
Author:
  Daynlight.

Contact:
  Email: Danielstodulski000@gmail.com
  Github: https://github.com/daynlight

Commands:
  -h/--help: show program help command.
  -i/--init: initialize default files.
  -s/--sandbox: turn on sandbox mode.
  -v/-d/--verbose/--debug: turn on verbose mode.

Path:
  Final path is set always as last argument. If filename specified it will create directory instead.
)");
};








void Graphite::Graphite::verbose() {
  verbose_mode = 1;
};








void Graphite::Graphite::sandbox() {
  sandbox_mode = 1;
};