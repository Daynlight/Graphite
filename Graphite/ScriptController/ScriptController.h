#pragma once

#include "Globals.h"
#include "ScriptInterface.h"

#include <string>
#include <filesystem>

#include <unistd.h>
#include <sys/wait.h>
#include <dlfcn.h>


namespace Graphite{
class ScriptLoader{
private:
  std::string filename = "";
  bool cant_find_file_print = 1;
  std::filesystem::file_time_type lastWriteTime{};
  
  void* script_handler = nullptr; 
  ScriptInterface* script = nullptr;

public:
  ScriptLoader(const std::string& filename);
  ~ScriptLoader();
  
  void checkLastWrite();
  int compile();
  int loadModule();
  void removeModule();
  void init();
  void update();
  void destroy();
};
};