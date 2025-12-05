# Graphite
# Copyright 2025 Daynlight
# Licensed under the Apache License, Version 2.0.
# See LICENSE file for details.

cmake_minimum_required(VERSION 3.15)


project(Graphite LANGUAGES CXX)

set(src
  App/Graphite.cpp
  Core/AppRenderer/AppRenderer.cpp
  Core/ScriptController/ScriptController.cpp
  Core/Math/Point.cpp
)

set(headers
  .
)

add_executable(Graphite ${src})
target_include_directories(Graphite PUBLIC ${headers})
target_link_libraries(Graphite PUBLIC CWindow)

if (UNIX)
  target_link_options(Graphite PUBLIC "-rdynamic")
endif()