// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#define  BUILDING_SCRIPT_DLL
#include <Graphite/ScriptInterface.h>

#include <math.h>


class Script : ScriptInterface{
  Graphite::Math::Point control_points[3] = {{{-400, 400}, {0.0, 0.0, 1.0}}, 
                                             {{200, 0}, {0.0, 0.0, 1.0}}, 
                                             {{400, -300}, {0.0, 0.0, 1.0}}};

  Graphite::Math::Plot2D plot;




  void Init(){
    plot.line_cell["l_1"] = Graphite::Math::Line(control_points[0].getPos(), control_points[1].getPos());
    plot.line_cell["l_2"] = Graphite::Math::Line(control_points[1].getPos(), control_points[2].getPos());
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