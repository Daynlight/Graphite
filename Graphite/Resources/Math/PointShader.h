// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.

#pragma once
#include <string>

inline std::string vertexPointShader = R"(
#version 430 core

layout(location = 0) in vec2 aPos;

uniform vec2 pos;
uniform vec3 color;
out vec3 vColor;

void main() {
    float scale = 0.01f;
    gl_Position = vec4(aPos * scale + pos, 0.0, 1.0);
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