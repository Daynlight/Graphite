// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#define  BUILDING_SCRIPT_DLL
#include <Graphite/ScriptInterface.h>
#include <math.h>
#include <functional>


class Script : ScriptInterface{

  Graphite::Math::Plot2D plot;

  float wave(float t, float HZ, float amplitude = 1, float phase = 0){

    return amplitude * sin((t + phase) * HZ * M_PI * 2);
  };

  std::array<float, 2> f(float t){
    float y = wave(t, 0.1, 0.6) + wave(t, 0.2, 1) + wave(t, 0.3, 2) + wave(t, 0.4, 0.2) 
    + wave(t, 0.5, 2) + wave(t, 0.6, -2.5) + wave(t, 0.7, -0.5) + wave(t, 0.8, 2)
    + wave(t, 0.9, 1) + wave(t, 1, 3);
    return {t, y};
  };


  std::vector<std::array<float, 2>> dft(std::function<std::array<float, 2>(float)> func, float min = 0.0f, float max = 1.0f, float step = 0.01f) {
    std::vector<float> samples;

    for (float t = min; t < max; t += step)
        samples.push_back(func(t)[1]);

    int N = samples.size();
    std::vector<std::array<float, 2>> spectrum;
    float samplingRate = 1.0f / step;

    for (int k = 0; k < N / 2; k++) {
        float real = 0.0f;
        float imag = 0.0f;

        for (int n = 0; n < N; n++)
        {
            float angle = 2.0f * M_PI * k * n / N;
            real += samples[n] * cos(angle);
            imag -= samples[n] * sin(angle);
        }

        real /= N;
        imag /= N;

        float magnitude = sqrt(real * real + imag * imag);
        float freq = k * samplingRate / N;

        spectrum.push_back({freq, magnitude});
    }

    return spectrum;
  };





  void Init(){
    std::vector<std::array<float, 2>> ml;
    for(float t = -10.0f; t <10.0f; t += 0.1f)
      ml.emplace_back(f(t));
    plot.multi_line_cell["ml"] = Graphite::Math::MultiLine(ml, 0.2f, {0.0f, 0.2f, 0.6f});

    std::vector<std::array<float, 2>> points = dft([this](float t){return this->f(t); }, 
                                                   -10.0f, 
                                                   10.0f, 
                                                   0.2f);
    for(int i = 0; i < points.size(); i++){
      points[i][0] *= 3;
      points[i][1] *= 3;
    };
    plot.multi_line_cell["dftml"] = Graphite::Math::MultiLine(points, 0.1f, {0.0f, 0.5});
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
