// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.

#define  BUILDING_SCRIPT_DLL
#include <Graphite/ScriptInterface.h>
#include <Graphite/Point.h>

#include <stdio.h>
#include <math.h>

#define SAMPLES 1000

class Script : ScriptInterface{
  Graphite::Math::Point points[SAMPLES];
  float f(float x) { return (1/2.0f) * sin(x * M_PI * 2); };


  void Init(){
    for(int i = 0; i < SAMPLES; i++){
      float x = (i/(SAMPLES - 1.0f) * 2) - 1;
      float y = f(x);
      points[i].setPos(x, y);
    }
    
    printf("Initialzed\n");
  };

  void Update(){

  };

  void Draw(){
    for(int i = 0; i < SAMPLES; i++){
      points[i].drawPoint();
    };
  };

  void Destroy(){
    printf("Destroyed\n");
  };
};



extern "C" ScriptInterface* SCRIPT_API GetScript() {
  Script* script = new Script();
  return (ScriptInterface*)script;
};