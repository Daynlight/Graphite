// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#pragma once

#include "Globals.h"
#include "Core/AppRenderer/AppRenderer.h"
#include "Core/ScriptController/ScriptController.h"

#include "../Resources/Templates/Main.h"

#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <string>


bool verbose_mode = 0;
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
  void runSandbox();

};
};

#include "Flags.h"