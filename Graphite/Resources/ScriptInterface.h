// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#pragma once
#ifdef BUILDING_SCRIPT_DLL
  #include "Graphite/Math.h"
#endif







#if defined(_WIN32) || defined(_WIN64)
  #ifdef BUILDING_SCRIPT_DLL
    #define SCRIPT_API __declspec(dllexport)
  #else
    #define SCRIPT_API __declspec(dllimport)
  #endif
#else
  #define SCRIPT_API 
#endif








class ScriptInterface{
public:
  virtual ~ScriptInterface() = default;
  virtual void Init() = 0;
  virtual void Update() = 0;
  virtual void Draw() = 0;
  virtual void Destroy() = 0;
};