// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#define  BUILDING_SCRIPT_DLL
#include <Graphite/ScriptInterface.h>
#include <array>
#include <vector>

class Script : ScriptInterface{
  Graphite::Math::Plot2D plot;
  std::vector<std::array<float, 2>> points ={
    {-3, -2},
    {-1, 1},
    {0, 3},
    {1, 2},
    {3, 6},
    {4, -3}
  };

  std::array<float, 2> interpolate(float x, std::vector<std::array<float, 2>> points){
    if (points.empty())
      return {x, 0};

    float y = 0.0f;
    size_t n = points.size();

    for (size_t i = 0; i < n; i++) {

      float xi = points[i][0];
      float yi = points[i][1];

      float Li = 1.0f;

      for (size_t j = 0; j < n; j++) {
        if (i == j) continue;

        float xj = points[j][0];
        Li *= (x - xj) / (xi - xj);
      }

      y += yi * Li;
    }

    return {x, y};
  };



  void Init(){
    for(int i = 0; i < points.size(); i++)
      plot.point_cell["point: " + i] = Graphite::Math::Point(points[i], 0.2, {0, 1, 0});

    std::vector<std::array<float, 2>> ml;
    for(float x = -10; x < 10; x += 0.1f)
      ml.emplace_back(interpolate(x, points));
    plot.multi_line_cell["function"] = Graphite::Math::MultiLine(ml, 0.1, {0, 0, 1});
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
