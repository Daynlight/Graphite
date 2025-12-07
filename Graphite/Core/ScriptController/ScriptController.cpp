// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#include "ScriptController.h"


Graphite::ScriptLoader::ScriptLoader(const std::string &path)
  : path(path) {};






  

Graphite::ScriptLoader::~ScriptLoader(){
  removeModule();
};






  

bool Graphite::ScriptLoader::checkLastWrite() {
  bool file_exist = std::filesystem::exists(path + ScriptName);

  bool changed = 0;

  if(cant_find_file_print && !file_exist){
    printf("No file named: %s\n", (path + ScriptName).c_str());
    cant_find_file_print = 0;
  };
  
  if(!file_exist)
    return 0;
  
  cant_find_file_print = 1;
  std::filesystem::file_time_type currentWriteTime{};

  try{
    currentWriteTime = std::filesystem::last_write_time(path + ScriptName);
  } catch(const std::filesystem::filesystem_error& e){
    printf("Filesystem error: %s\n", e.what());
    return false;
  };

  if(currentWriteTime != lastWriteTime){
    changed = 1;
    lastWriteTime = currentWriteTime;
  };

  return changed;
};






  

void Graphite::ScriptLoader::updateScript() {
  removeModule();
  if(!compile())
    if(!loadModule())
      init();
};






  

int Graphite::ScriptLoader::compile() {
  std::string so_file = path + ScriptOutName;
  std::string cpp_file = path + ScriptName;

  const char* command = "g++";
  const char* argv[] = {
    "g++",
    "-rdynamic",
    "-shared", 
    "-fPIC",
    "-o", so_file.c_str(), 
    cpp_file.c_str(), 
    nullptr
  };


  pid_t pid = fork();
  if(pid == 0){
    if(!verbose_mode) {
      int devnull = open("/dev/null", O_WRONLY);
      if(devnull != -1) {
        dup2(devnull, STDOUT_FILENO);
        dup2(devnull, STDERR_FILENO);
        close(devnull);
      };
    };

    execvp(command, const_cast<char* const*>(argv)); 
    printf("Failed to exec g++\n");
    return -1;
  }
  else if(pid > 0){
    int status = 0; 
    waitpid(pid, &status, 0);

    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) { 
      if(verbose_mode)
        printf("Compilation successful: %s\n", (path + "Graphite.so").c_str()); 

      return 0; 
    } 
    else { 
      printf("Compilation failed!\n"); 
      return -1; 
    };
  };

  printf("Failed to fork()\n");
  return -1;
};






  

int Graphite::ScriptLoader::loadModule() {
  removeModule();

  bool file_exist = std::filesystem::exists(path + ScriptOutName);
  if(!file_exist) return -1;

  script_handler = dlopen((path + "Graphite.so").c_str(), RTLD_NOW);

  if (!script_handler) {
    printf("Failed to load script: %s\n", dlerror());
    return -1;
  };

  dlerror();

  typedef ScriptInterface* (*GetScriptFunc)();
  GetScriptFunc getScript = (GetScriptFunc)dlsym(script_handler, "GetScript");
  const char* dlsym_error = dlerror();
  
  if (dlsym_error || !getScript) {
    printf("Cannot load symbol 'GetScript': %s\n", dlsym_error);
    removeModule();
    return -1;
  };

  script = getScript();

  if(!script){
    removeModule();
    return -1;
  }

  return 0;
};






  

void Graphite::ScriptLoader::removeModule(){
  if (!script_handler) {
    script = nullptr;
    return;
  };

  if(script){
    destroy();

    dlerror();
    using DeleteScriptFunc = void (*)(ScriptInterface*);
    DeleteScriptFunc deleteScript = (DeleteScriptFunc)dlsym(script_handler, "DeleteScript");
    const char* dlsym_error = dlerror();

    if (dlsym_error || !deleteScript) {
      printf("Warning: DeleteScript not found or invalid: %s\n", dlsym_error ? dlsym_error : "null");
      script = nullptr;
    }
    else{
      deleteScript(script);
      script = nullptr;
    };
  };

  
  if(script_handler) dlclose(script_handler);
  script_handler = nullptr;
  script = nullptr;
};






  

void Graphite::ScriptLoader::init() {
  if(script){
    
    if(sandbox_mode){
      pid_t pid = fork();
      if(pid == 0){
        script->Init();
        _exit(0);
      }
      else if(pid > 0){
        int status = 0; 
        waitpid(pid, &status, 0);

        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) { 
          if(verbose_mode){
            printf("%d\n", status);
            printf("Init failed!\n");
          }
          return; 
        };
      };
    };

    script->Init();
  };
};






  

void Graphite::ScriptLoader::update() {
  if(script){

    if(sandbox_mode){
      pid_t pid = fork();
      if(pid == 0){
        script->Update();
        _exit(0);
      }
      else if(pid > 0){
        int status = 0; 
        waitpid(pid, &status, 0);

        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) { 
          if(verbose_mode){
            printf("%d\n", status);
            printf("Update failed!\n");
          }
          return; 
        };
      };
    };

    script->Update();
  };
};






  

void Graphite::ScriptLoader::draw(){
  if(script){
    
    if(sandbox_mode){
      pid_t pid = fork();
      if(pid == 0){
        script->Draw();
        _exit(0);
      }
      else if(pid > 0){
        int status = 0; 
        waitpid(pid, &status, 0);

        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) { 
          if(verbose_mode){
            printf("%d\n", status);
            printf("Draw failed!\n");
          }
          return; 
        };
      };
    };

    script->Draw();
  };
};






  

void Graphite::ScriptLoader::destroy() {
  if(script){

    if(sandbox_mode){
      pid_t pid = fork();
      if(pid == 0){
        script->Destroy();
        _exit(0);
      }
      else if(pid > 0){
        int status = 0; 
        waitpid(pid, &status, 0);

        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) { 
          if(verbose_mode){
            printf("%d\n", status);
            printf("Destroy failed!\n");
          }
          return; 
        };
      };
    };

    script->Destroy();
  };
};

