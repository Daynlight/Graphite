#define  BUILDING_SCRIPT_DLL
#include "ScriptInterface.h"
#include "Point.h"

#include <stdio.h>



class Script : ScriptInterface{
  Graphite::Math::Point* points;

  void Init(){
    points = new Graphite::Math::Point(0.0f, 0.5f);

    printf("Initialzed\n");
  };

  void Update(){
    points->drawPoint();
  };

  void Destroy(){
    delete points;

    printf("Destroyed\n");
  };
};



extern "C" ScriptInterface* SCRIPT_API GetScript() {
  Script* script = new Script();
  return (ScriptInterface*)script;
};