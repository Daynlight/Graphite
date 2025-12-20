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

uniform vec2 pos;
uniform vec3 color;
uniform vec2 camera_pos;
uniform float camera_zoom;

void main() {
    float scale = 0.01f;
    vec4 point_pos = vec4(aPos * scale + pos, 0.0, 1.0);
    vec4 world_pos = vec4(camera_pos[0], camera_pos[1], 0, 0);

    
    gl_Position = point_pos + world_pos;
    vColor = color;
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