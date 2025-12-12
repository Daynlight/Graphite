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









set(copy_files
  ${CMAKE_SOURCE_DIR}/Graphite/Resources/ScriptInterface.h
  ${CMAKE_SOURCE_DIR}/Graphite/Resources/Math/iMath.h
  ${CMAKE_SOURCE_DIR}/Graphite/Resources/Math/Math.h
  ${CMAKE_SOURCE_DIR}/Graphite/Resources/Math/Plots/Plot2D/Plot2D.h
  ${CMAKE_SOURCE_DIR}/Graphite/Resources/Math/Point.h
)


set(copied_headers)
foreach(file IN LISTS copy_files)
    get_filename_component(fname "${file}" NAME)
    add_custom_command(
        OUTPUT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${fname}
        COMMAND ${CMAKE_COMMAND} -E copy 
            ${file} 
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${fname}
        DEPENDS "${file}"
        COMMENT "Copying ${fname}"
    )
    list(APPEND copied_headers ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${fname})
endforeach()



add_custom_target(copy_headers ALL DEPENDS ${copied_headers})
add_dependencies(GraphiteInstaller copy_headers)