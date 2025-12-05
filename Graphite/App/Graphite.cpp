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
  -s/--sandbox: turn on sandbox mode.
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
  if(strcmp(argv, "--sandbox") == 0)
    flags["sandbox"] = 1;
  if(strcmp(argv, "--verbose") == 0 ||
    strcmp(argv, "--debug") == 0)
    flags["verbose"] = 1;
};








void Graphite::Graphite::shortFlags(const char* argv){
  unsigned int len = strlen(argv);
  for(int j = 1; j < len; j++){
    if(argv[j] == 'i') flags["init"] = 1;
    if(argv[j] == 'h') flags["help"] = 1;
    if(argv[j] == 's') flags["sandbox"] = 1;
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

  if(!flags["help"]){
    if(flags["sandbox"])
      runSandbox();
    else
      runProgram();
  };

};








void Graphite::Graphite::runProgram(){
  AppRenderer renderer;
  ScriptLoader script(path);


  while(renderer.isRunning()){
    script.checkLastWrite();

    script.update();

    renderer.renderFrame([&script](){
      script.draw();
    });
  };
};








void Graphite::Graphite::runSandbox(){
  printf("Sandbox Mode\n");

  ScriptLoader script(path);
  script.checkLastWriteSandbox();


  while(1){
    pid_t pid = fork();

    if (pid == 0) {
      execl("Graphite", "Graphite", path.c_str(), "-v", nullptr); 
      printf("Failed to exec Graphite sandbox\n");
      exit(1);
    }
    else if (pid > 0) {
      int status;
      waitpid(pid, &status, 0);

      if (WIFSIGNALED(status)) {
        printf("Sandbox crashed (signal %d)\n", WTERMSIG(status));
      } else if (WIFEXITED(status)) {
        printf("Sandbox exited with status %d\n", WEXITSTATUS(status));
        exit(0);
      }
    }
    else
      perror("fork failed");

    while(!script.checkLastWriteSandbox())
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
  };

};