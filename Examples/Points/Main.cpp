#define  BUILDING_SCRIPT_DLL
#include <Graphite/ScriptInterface.h>
#include <Graphite/Point.h>

#include <stdio.h>



class Script : ScriptInterface{
  Graphite::Math::Point points[20];

  void Init(){
    for(int i = 0; i < 20; i++)
      points[i].setPos(i/20, i/20);
    
    printf("Initialzed\n");
  };

  void Update(){
    for(int i = 0; i < 20; i++)
      points[i].drawPoint();
  };

  void Destroy(){
    printf("Destroyed\n");
  };
};



extern "C" ScriptInterface* SCRIPT_API GetScript() {
  Script* script = new Script();
  return (ScriptInterface*)script;
};