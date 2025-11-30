#include "ScriptController.h"

Graphite::ScriptLoader::ScriptLoader(const std::string &filename)
  : filename(filename){};






  

Graphite::ScriptLoader::~ScriptLoader(){
  removeModule();
};






  

void Graphite::ScriptLoader::checkLastWrite() {
  bool file_exist = std::filesystem::exists(filename + ".cpp");

  if(cant_find_file_print && !file_exist){
    printf("No file named: %s\n", (filename + ".cpp").c_str());
    cant_find_file_print = 0;
  };
  
  if(!file_exist)
    return;
  
  cant_find_file_print = 1;
  
  std::filesystem::file_time_type currentWriteTime = 
      std::filesystem::last_write_time(filename + ".cpp");


  if(currentWriteTime != lastWriteTime){
    removeModule();
    if(!compile())
      if(!loadModule())
        init();

      
    lastWriteTime = currentWriteTime;
  };
};






  

int Graphite::ScriptLoader::compile() {
  std::string outDir = "dll/";

  if(!std::filesystem::exists(outDir))
    std::filesystem::create_directory(outDir);




  const char* command = "g++";
  const char* argv[] = {
    "g++",
    "-shared", 
    "-fPIC", 
    "-o", (outDir + filename + ".so").c_str(), 
    (filename + ".cpp").c_str(), 
    nullptr
  };



  pid_t pid = fork();
  if(pid == 0){
    execvp(command, const_cast<char* const*>(argv)); 
    printf("Failed to exec g++\n");
    return -1;
  }
  else if(pid > 0){
    int status = 0; 
    waitpid(pid, &status, 0);

    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) { 
      if(verbose_mode)
        printf("Compilation successful: %s\n", (outDir + filename + ".so").c_str()); 
      return 0; 
    } 
    else { 
      printf("Compilation failed!\n"); 
      return false; 
    };
  }



  printf("Failed to fork()\n");
  return -1;
};






  

int Graphite::ScriptLoader::loadModule() {
  script_handler = dlopen(("dll/" + filename + ".so").c_str(), RTLD_LAZY);
  if (!script_handler) {
      printf("Failed to load script: %s\n", dlerror());
      return -1;
  };



  dlerror();


  typedef ScriptInterface* (*GetScriptFunc)();
  GetScriptFunc getScript = (GetScriptFunc)dlsym(script_handler, "GetScript");
  const char* dlsym_error = dlerror();
  if (dlsym_error) {
      printf("Cannot load symbol 'GetScript': %s\n", dlsym_error);
      dlclose(script_handler);
      return -1;
  };


  script = getScript();


  return 0;
};






  

void Graphite::ScriptLoader::removeModule(){
  if(script){
    destroy();
    delete script;
    script = nullptr;
  };

  if(script_handler){
    dlclose(script_handler);
    script_handler = nullptr;
  };
};






  

void Graphite::ScriptLoader::init() {
  if(script)
    script->Init();
};






  

void Graphite::ScriptLoader::update() {
  if(script)
    script->Update();
};






  

void Graphite::ScriptLoader::destroy() {
  if(script)
    script->Destroy();
};