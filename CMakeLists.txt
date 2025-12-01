# Graphite
# Copyright 2025 Daynlight
# Licensed under the Apache License, Version 2.0.
# See LICENSE file for details.

cmake_minimum_required(VERSION 3.15)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(vendor/CWindow/CWindow)


add_subdirectory(Graphite)


set(interfaces_headers
  Graphite/InterfaceInclude/ScriptInterface.h
  Graphite/InterfaceInclude/Point.h
)


install(TARGETS Graphite RUNTIME DESTINATION bin CONFIGURATIONS Release)
install(FILES ${interfaces_headers} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/Graphite/)