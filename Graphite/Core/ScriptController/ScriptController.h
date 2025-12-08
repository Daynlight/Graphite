// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#pragma once

#include "Globals.h"
#include "Resources/Runtime/ScriptInterface.h"

#include <string>
#include <filesystem>

#include <unistd.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <sys/wait.h>


namespace Graphite{
class ScriptLoader{
private:
  std::string path = "";
  bool cant_find_file_print = 1;
  std::filesystem::file_time_type lastWriteTime{};
  
  void* script_handler = nullptr; 
  ScriptInterface* script = nullptr;

public:
  ScriptLoader(const std::string& path);
  ~ScriptLoader();
  
  bool checkLastWrite();
  void updateScript();

  int compile();
  int loadModule();
  void removeModule();

  void init();
  void update();
  void draw();
  void destroy();

};
};