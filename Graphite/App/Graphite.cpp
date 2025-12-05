// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#include "Graphite.h"


int main(int args, const char* argv[]){
  Graphite::Graphite graphite;

  graphite.run(args, argv);

  return 0;
};















////////////////////////////////////////////////////////////
//////////////////////// Main Entry ////////////////////////
////////////////////////////////////////////////////////////
void Graphite::Graphite::run(int args, const char *argv[]){
  detectFlags(args, argv);

  if(!std::filesystem::exists(path + ScriptName))
    flags["init"] = 1;

  executeFlags();

  if(!flags["help"]){
    if(flags["sandbox"]) runSandbox();
    else runProgram();
  };
};








void Graphite::Graphite::runProgram(){
  AppRenderer renderer;
  ScriptLoader script(path);


  while(renderer.isRunning()){
    if(script.checkLastWrite()) 
      script.updateScript();

    script.update();

    renderer.renderFrame([&script](){
      script.draw();
    });
  };
};








void Graphite::Graphite::runSandbox(){
  printf("Sandbox Mode\n");

  ScriptLoader script(path);
  script.checkLastWrite();

  const char* command = "Graphite";
  const char* argv[] = {
    "Graphite",
    path.c_str(), 
    nullptr
  };


  while(1){
    pid_t pid = fork();

    if (pid == 0) {
      execvp(command, const_cast<char* const*>(argv)); 
      printf("Failed to exec Graphite sandbox\n");
      exit(1);
    }
    else if (pid > 0) {
      int status;
      waitpid(pid, &status, 0);

      if (WIFSIGNALED(status))
        printf("Sandbox crashed (signal %d)\n", WTERMSIG(status));
      else if (WIFEXITED(status))
        exit(0);
    }
    else
      perror("fork failed");

    while(!script.checkLastWrite())
      usleep(500);
  };
};