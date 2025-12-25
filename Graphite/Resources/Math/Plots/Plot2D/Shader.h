// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#pragma once
#include <string>


inline std::string vertexFillShader = R"(
#version 430 core

layout(location = 0) in vec3 aPos;

out vec3 vColor;

uniform vec2 camera_pos;
uniform float camera_zoom;
uniform vec2 window_size;

void main() {
    float window_ratio = window_size.y / window_size.x;
    
    vec2 world_pos = aPos.xy;
    vec2 view_pos = (world_pos - camera_pos) * camera_zoom;
    
    view_pos.x /= window_size.x;
    view_pos.y /= window_size.y;

    gl_Position = vec4(view_pos, aPos.z, 1.0);
    vColor = vec3(1.0f, 1.0f, 1.0f);
}

)";



inline std::string fragmentFillShader = R"(
#version 430 core

in vec3 vColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(vColor, 1.0);
}

)";