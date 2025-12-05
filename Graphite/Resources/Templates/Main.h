// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.

const char* GraphiteTemplate = 
R"(// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.

#define  BUILDING_SCRIPT_DLL
#include <Graphite/ScriptInterface.h>
#include <Graphite/Point.h>


#include <stdio.h>


class Script : ScriptInterface{

  void Init(){
    printf("Initialzed\n");
  };

  void Update(){
    
  };

  void Draw(){
  
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