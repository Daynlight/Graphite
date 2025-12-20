// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#define  BUILDING_SCRIPT_DLL
#include <Graphite/ScriptInterface.h>

#include <math.h>

#define SAMPLES 50


class Script : ScriptInterface{
  Graphite::Math::Point control_points[3] = {{{-0.7, 0.7}, {0.0, 0.0, 1.0}}, 
                                             {{0.7, -0.5}, {0.0, 0.0, 1.0}}, 
                                             {{0.9, 0.4}, {0.0, 0.0, 1.0}}};

  Graphite::Math::Plot2D plot;





  // https://mst.mimuw.edu.pl/lecture.php?lecture=gk1&part=Ch6&mode=xhtml#S1
  std::array<float, 2> bezier(float t) {
    float u = 1.0f - t;

    std::array<float, 2> pos1 = control_points[0].getPos();
    std::array<float, 2> pos2 = control_points[1].getPos();
    std::array<float, 2> pos3 = control_points[2].getPos();

    float x = u*u*pos1[0] + 2*u*t*pos2[0] + t*t*pos3[0];
    float y = u*u*pos1[1] + 2*u*t*pos2[1] + t*t*pos3[1];

    return {x, y};
  };





  
  void Init(){
    plot.point_cell["cp_1"] = control_points[0];
    plot.point_cell["cp_2"] = control_points[1];
    plot.point_cell["cp_3"] = control_points[2]; 

    for(int i = 0; i < SAMPLES; i++){
      auto P = bezier((i * 1.0f) / SAMPLES);
      plot.point_cell[std::to_string(i)] = Graphite::Math::Point(P);
    };
    
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