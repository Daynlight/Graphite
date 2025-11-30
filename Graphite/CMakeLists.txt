cmake_minimum_required(VERSION 3.15)


project(Graphite LANGUAGES CXX)

set(src
  Main.cpp
)

set(headers
  .
)

add_executable(Graphite ${src})
target_include_directories(Graphite PUBLIC ${headers})
target_link_libraries(Graphite PUBLIC CWindow)