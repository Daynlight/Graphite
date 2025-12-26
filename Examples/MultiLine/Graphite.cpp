// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#define  BUILDING_SCRIPT_DLL
#include <Graphite/ScriptInterface.h>

#include <math.h>


class Script : ScriptInterface{
  Graphite::Math::Point control_points[3] = {{{-4, 4}, 0.2f, {0.0, 0.0, 1.0}}, 
                                             {{0, -5}, 0.2f, {0.0, 0.0, 1.0}}, 
                                             {{4, 3}, 0.2f, {0.0, 0.0, 1.0}}};

  Graphite::Math::Plot2D plot;




  void Init(){
    plot.point_cell["cp_1"] = control_points[0];
    plot.point_cell["cp_2"] = control_points[1];
    plot.point_cell["cp_3"] = control_points[2];

    std::vector<std::array<float, 2>> points(3);
    for(Graphite::Math::Point el : control_points)
      points.emplace_back(el.getPos());
    
    plot.multi_line_cell["ml1"] = Graphite::Math::MultiLine(points);
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