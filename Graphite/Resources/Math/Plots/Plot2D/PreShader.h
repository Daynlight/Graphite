// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#pragma once
#include <string>


inline std::string vertexPreShader = R"(
#version 430 core

layout(location = 0) in vec3 aPos;



void main() {
    gl_Position = vec4(aPos, 1.0f);
}

)";



inline std::string fragmentPreShader = R"(
#version 430 core

out vec4 FragColor;


uniform vec2 camera_pos;
uniform float camera_zoom;
uniform vec2 window_size;

float main_thickness = 4.0f;
float side_thickness = 2.0f;

float modulo = 10.0f;

void main() {
  vec2 ndc = (gl_FragCoord.xy / window_size) * 2.0f - 1.0f;
  vec2 worldPos = ndc * window_size / camera_zoom + camera_pos;

  modulo = pow(10, floor(log2(window_size.x / camera_zoom) / log2(10)));
  
  if(abs(worldPos.x) < main_thickness / camera_zoom || abs(worldPos.y) < main_thickness / camera_zoom)
    FragColor = vec4(1.0, 1.0, 1.0, 0.7);

  else if(abs(mod(worldPos.x, floor(modulo))) < side_thickness / camera_zoom || 
          abs(mod(worldPos.y, floor(modulo))) < side_thickness / camera_zoom)
    FragColor = vec4(1.0, 1.0, 1.0, 0.5);
  
  else
    FragColor = vec4(0.0, 0.0, 0.0, 0.0);
}

)";