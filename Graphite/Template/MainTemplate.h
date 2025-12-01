const char* MainTemplate = 
R"(#define  BUILDING_SCRIPT_DLL
#include <Graphite/ScriptInterface.h>
#include <Graphite/Point.h>


#include <stdio.h>


class Script : ScriptInterface{

  void Init(){
    printf("Initialzed\n");
  };

  void Update(){
    
  };

  void Destroy(){
    printf("Destroyed\n");
  };
};



extern "C" ScriptInterface* SCRIPT_API GetScript() {
  Script* script = new Script();
  return (ScriptInterface*)script;
};  

)";