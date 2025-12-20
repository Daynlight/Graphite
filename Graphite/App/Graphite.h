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


namespace Graphite{
class Graphite{
private:
  std::unordered_map<std::string, bool> flags;
  std::filesystem::path path = std::filesystem::path("./");

private:
  void initFile(const std::string& filename, const char* data);
  void init();
  void help();
  void verbose();
  void sandbox();

  void longFlags(int* i, int args, const char* argv[]);
  void shortFlags(int* i, int args, const char* argv[]);
  void detectPath(int* i, int args, const char* argv[]);
  void detectFlags(int args, const char* argv[]);
  void executeFlags();

  void calculateDeltas(AppRenderer* renderer);

public:
  void run(int args, const char* argv[]);
  void runProgram();

};
};

#include "Flags.h"