// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#define  BUILDING_SCRIPT_DLL
#include <Graphite/ScriptInterface.h>

#include <math.h>

#define SAMPLES 300


class Script : ScriptInterface{
  Graphite::Math::Plot2D plot;
  float f(float x) { return 5 * sin((x * M_PI * 2)); };






  void Init(){
    std::array<float,2> last_pos = {0, 0};
    bool init = true;

    for(int i = 0; i < SAMPLES; i++){
      float x = ((i/(SAMPLES - 1.0f) * 2) - 1) * 7;
      float y = f(x);

      if(!init){
        plot.line_cell[std::to_string(i)] = Graphite::Math::Line(last_pos, {x, y}, 0.1f);
      };

      last_pos = {x, y};
      init = false;
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