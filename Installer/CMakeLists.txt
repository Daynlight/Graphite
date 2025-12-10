# Graphite
# Copyright 2025 Daynlight
# Licensed under the Apache License, Version 2.0.
# See LICENSE file for details.


cmake_minimum_required(VERSION 3.15)


set(CMAKE_CXX_STANDARD 17)



project(GraphiteInstaller LANGUAGES CXX)

set(src
  main.cpp
)


add_executable(GraphiteInstaller ${src})


add_custom_command(TARGET GraphiteInstaller PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/Graphite/Resources/Runtime/ScriptInterface.h
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ScriptInterface.h
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/Graphite/Resources/Runtime/Plot2D.h
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Plot2D.h
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/Graphite/Resources/Runtime/Math.h
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Math.h
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/Graphite/Resources/Runtime/Point.h
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Point.h
)