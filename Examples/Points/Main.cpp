#define  BUILDING_SCRIPT_DLL
#include "ScriptInterface.h"
#include "Point.h"

#include <stdio.h>



class Script : ScriptInterface{
  Graphite::Math::Point* points;
  Graphite::Math::Point* points2;

  void Init(){
    points = new Graphite::Math::Point(0.0f, 0.5f);
    points2 = new Graphite::Math::Point(0.5f, 0.0f);

    printf("Initialzed\n");
  };

  void Update(){
    points->drawPoint();
    points2->drawPoint();
  };

  void Destroy(){
    delete points;
    delete points2;

    printf("Destroyed\n");
  };
};



extern "C" ScriptInterface* SCRIPT_API GetScript() {
  Script* script = new Script();
  return (ScriptInterface*)script;
};