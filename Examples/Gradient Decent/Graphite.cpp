// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#define  BUILDING_SCRIPT_DLL
#include <Graphite/ScriptInterface.h>
#include <array>
#include <vector>
#include <math.h>

class Script : ScriptInterface{
  Graphite::Math::Plot2D plot;

  std::array<float, 2> f(float x){
      float y = std::sin(3*x) + 0.2f * x*x;
      return {x, y};
  }

  std::array<float, 2> df(float x){
      float dy = 3*std::cos(3*x) + 0.4f*x;
      return {x, dy};
  }
  



  void Init(){
    std::vector<std::array<float, 2>> ml;
    std::array<float, 2> last;
    
    std::array<float, 2> start = f(4.5f);
    const float learning_rate = 0.03f;
    std::array<float, 2> start2 = f(-4.5f);
    const float learning_rate2 = 0.5f;

    for(float x = -10; x < 10; x += 0.1f)
      ml.emplace_back(f(x));
      plot.multi_line_cell["function"] = Graphite::Math::MultiLine(ml, 0.1f, {0.5f, 1.0f});

    last = start;
    for(int i = 0; i < 20; i += 1){
      float dy = df(last[0])[1];
      last = f(last[0] - dy * learning_rate);

      plot.point_cell["points" + i] = Graphite::Math::Point(last, 0.2, {0.2f, 0.4f, 0.2f});
    }

    last = start2;
    for(int i = 0; i < 20; i += 1){
      float dy = df(last[0])[1];
      last = f(last[0] - dy * learning_rate2);

      plot.point_cell["points2" + i] = Graphite::Math::Point(last, 0.2, {0.4f, 0.2f, 0.2f});
    }

    plot.point_cell["start"] = Graphite::Math::Point(start, 0.2, {0.0f, 1.0f});
    plot.point_cell["start2"] = Graphite::Math::Point(start2, 0.2, {1.0f, 0.0f});
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
