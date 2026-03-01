// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#include <string>
#include <vector>
#include <filesystem>


void moveFile(const std::filesystem::path src, const std::filesystem::path dest){
  if(!std::filesystem::exists(src) || !std::filesystem::exists(dest.parent_path())) {
    printf("Can't move resource %s -> %s\n", src.string().c_str(), dest.string().c_str());
    return;
  };

  try {
    if (!std::filesystem::exists(dest.parent_path())) {
      std::filesystem::create_directories(dest.parent_path());
      printf("Directory %s created\n", dest.c_str());
    }
  } catch (const std::filesystem::filesystem_error& e) {
    printf("Failed to create directory %s: %s\n", dest.c_str(), e.what());
    return;
  }

  try {
    std::filesystem::copy_file(src, dest, std::filesystem::copy_options::overwrite_existing);
    printf("File copied successfully. %s -> %s\n", src.string().c_str(), dest.string().c_str());
  }
  catch (const std::filesystem::filesystem_error& e) {
    printf("Error copying file: %s\n", e.what());
    return;
  };
};






const std::string path = "/usr/local/include/Graphite/";
const std::vector<std::string> resources = {
  "ScriptInterface.h",
  "Plot2D.h",
  "Math.h",
  "Point.h",
  "Line.h",
  "MultiLine.h",
};

int main(){

  for(const std::string& el : resources)
    moveFile(el, path + el);

  moveFile("Graphite", "/usr/local/bin/Graphite");

  return 0;
};