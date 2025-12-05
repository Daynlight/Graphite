// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.

#define  BUILDING_SCRIPT_DLL
#include <Graphite/ScriptInterface.h>
#include <Graphite/Point.h>

#include <stdio.h>
#include <math.h>

#define SAMPLES 200

class Script : ScriptInterface{
  Graphite::Math::Point control_points[3] = {{-0.7, 0.7, 0.0, 0.0}, 
                                             {0.7, -0.5, 0.0, 0.0}, 
                                             {0.9, 0.4, 0.0, 0.0}};
  Graphite::Math::Point points[SAMPLES];


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

    for(int i = 0; i < SAMPLES; i++){
      auto P = bezier((i * 1.0f) / SAMPLES);
      points[i].setPos(P[0], P[1]);
    };
    
    printf("Initialzed\n");
  };

  void Update(){

  };

  void Draw(){
    for(int i = 0; i < 3; i++)
      control_points[i].drawPoint();

    for(int i = 0; i < SAMPLES; i++)
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