#pragma once

#include <unordered_map>
#include <string>
#include "Renderer/OpenGL/Renderer.h"


class Mesh2D{
private:
  std::unordered_map<std::string, CW::Renderer::Mesh> meshes;

public:
  Mesh2D();
  



};
