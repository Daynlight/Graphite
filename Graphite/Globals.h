// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#pragma once
#include <array>

#define ScriptName "Graphite.cpp"
#define ScriptOutName "Graphite.so"

#define MoveSpeed 10.0f;
#define ZoomSpeed 0.01f;

extern bool verbose_mode;
extern bool sandbox_mode;

extern std::array<float, 2> d_pos;
extern float d_zoom;
extern std::array<float, 2> window_size;