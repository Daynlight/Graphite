#pragma once
#include <string>

std::string vertexPointShader = R"(
#version 430 core

layout(location = 0) in vec2 aPos;
out vec4 vPos;

void main() {
  gl_Position = vec4(aPos, 0.0, 1.0);
  vPos = gl_Position;
}

)";



std::string fragmentPointShader = R"(
#version 430 core

out vec4 FragColor;
in vec4 vPos;

uniform vec2 pos;
uniform vec3 color;

void main() {
  if((vPos.x - pos.x)*(vPos.x - pos.x) + (vPos.y - pos.y)*(vPos.y - pos.y) < 0.0001f)
    FragColor = vec4(color, 1.0);
  else
    FragColor = vec4(0.0);
}
)";