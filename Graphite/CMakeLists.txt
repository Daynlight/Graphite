cmake_minimum_required(VERSION 3.15)


project(Graphite LANGUAGES CXX)

set(src
  Main.cpp
  ScriptController/ScriptController.cpp
  Math/Point.cpp
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