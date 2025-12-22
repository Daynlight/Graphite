// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#pragma once
#include <string>


inline std::string vertexPointShader = R"(
#version 430 core

layout(location = 0) in vec2 aPos;

out vec3 vColor;

uniform vec2 camera_pos;
uniform float camera_zoom;
uniform vec2 window_size;

void main() {
    float window_ratio = window_size.y / window_size.x;
    float scale = 1.0f;
    
    vec2 world_pos = aPos;
    vec2 view_pos = (world_pos - camera_pos) * camera_zoom;
    
    view_pos /= window_size;

    gl_Position = vec4(view_pos, 0.0, 1.0);
    vColor = vec3(1.0f,1.0f,1.0f);
}

)";



inline std::string fragmentPointShader = R"(
#version 430 core

in vec3 vColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(vColor, 1.0);
}

)";