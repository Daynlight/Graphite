// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#define  BUILDING_SCRIPT_DLL
#include <Graphite/ScriptInterface.h>

#include <math.h>

#define SAMPLES 50


class Script : ScriptInterface{
  Graphite::Math::Plot2D plot;

  std::array<float, 2> f(float t){
    return {6 * cos(t), 6 * sin(t)};
  };



  void Init(){
    std::vector<std::array<float, 2>> points;
    points.reserve(SAMPLES);

    for(float t = 0; t < 2 * M_PI + M_PI / SAMPLES; t += 2 * M_PI / SAMPLES){
      points.emplace_back(f(t));
    };
    
    plot.multi_line_cell["ml1"] = Graphite::Math::MultiLine(points, 0.2f, {0.0f, 0.7f, 0.7f});
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