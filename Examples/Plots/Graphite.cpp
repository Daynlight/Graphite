// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#define  BUILDING_SCRIPT_DLL
#include <Graphite/ScriptInterface.h>

#include <math.h>


class Script : ScriptInterface{

  Graphite::Math::Plot2D plot;


  void Init(){
    plot.point_cell["1"] = Graphite::Math::Point({0.2f, 0.1f});
    plot.point_cell["2"] = Graphite::Math::Point({0.2f, -0.1f});
    plot.point_cell["3"] = Graphite::Math::Point({-0.2f, 0.1f});
  };

  void Update(){
    plot.plotEvents();
  };

  void Draw(){
    plot.draw();
  };

  void Destroy(){

  };
};



extern "C" ScriptInterface* SCRIPT_API GetScript() {
  Script* script = new Script();
  return (ScriptInterface*)script;
};

extern "C" void SCRIPT_API DeleteScript(ScriptInterface* script) {
  Script* temp_script = (Script*)script;
  delete temp_script;
};