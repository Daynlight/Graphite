<div align=center>
  <h1>Graphite</h1>
</div>




## About
Graphite is simple 2D/3D math visual app like geogebra, desoms, amtplotlib in python. It works on c++ scripting language. It is based how scripts works via using interfaces and dll loading. Allows how swap dll on runtime for easy and nice experience. It uses my own rendering library [CWindow](https://github.com/daynlight/CWindow)

Why it exists:
  * I hate python
  * Geogebra is slow
  * I love my own software
  * Learning

For whom:
  * For people that want faster graphical math app
  * People who hate python <3




## TOC
- [About](#about)
- [TOC](#toc)
- [Installation](#installation)
- [Usage](#usage)
  - [Run](#run)
  - [Flags](#flags)
- [**Important Note**](#important-note)
- [Prerequisites](#prerequisites)
- [Versions and features](#versions-and-features)
- [Other Docs](#other-docs)
- [Cat](#cat)

## Installation
```bash
  git clone --recursive https://github.com/daynlight/Graphite.git
  cd Graphite

  mkdir -p build
  cd build
  cmake ..
  cmake --build . --config Release
  cd ..

  sudo cmake --install build/ --config Release
  cd ..
```




## Usage
### Run
1. Run it
```bash
Graphite <flags> <path>
```

2. Edit ```Graphite.cpp```
```cpp
// Graphite
// Copyright 2025 Daynlight
// Licensed under the Apache License, Version 2.0.
// See LICENSE file for details.


#define  BUILDING_SCRIPT_DLL
#include <Graphite/ScriptInterface.h>
#include <Graphite/Math.h>

#include <math.h>

#define SAMPLES 1000


class Script : ScriptInterface{
  Graphite::Math::Point points[SAMPLES];
  float f(float x) { return (1/2.0f) * sin(x * M_PI * 2); };






  void Init(){
    for(int i = 0; i < SAMPLES; i++){
      float x = (i/(SAMPLES - 1.0f) * 2) - 1;
      float y = f(x);
      points[i].setPos({x, y});
    };
  };

  void Update(){

  };

  void Draw(){
    for(int i = 0; i < SAMPLES; i++)
      points[i].drawPoint();
  };

  void Destroy(){

  };
};



extern "C" ScriptInterface* SCRIPT_API GetScript() {
  Script* script = new Script();
  return (ScriptInterface*)script;
};

extern "C" void SCRIPT_API DeleteScript(ScriptInterface* script) {
  Script* temp_script = (Script*)script;
  delete temp_script;
};
```

### Flags
  * ```-h/--help```: show program help command.
  * ```-i/--init```: initialize default files.
  * ```-s/--sandbox```: turn on sandbox mode.
  * ```-v/-d/--verbose/--debug```: turn on verbose mode.




## **Important Note**
- For edition use **sandbox mode** it prevents **segment fault** and **program crashes** at **runtime edition**.
- **Sandbox mode** runs the ```Graphite -v <path>``` on fork. If program breaks it **doesn't stop whole program** just check if **script is changed**.
- **Always** end **all threads** in script in ```Destroy()``` function.
- When script is stable use **normal mode** for **performance**. 




## Prerequisites
   * ```CMake``` - for building.
   * ```C++17``` - for compilation.
   * ```Git``` - cloning **repo** and **submodules**




## Versions and features

<details open>
<summary>v1.0.0</summary>

- [x] Sandbox mode.
- [x] Script sandbox last write.
- [x] Separate ```CWindow``` renderer via ```AppRenderer```.
- [x] Safer script destroy.
- [ ] ScriptController edge-cases and error handling.
</details>

<details>
<summary>Prototype</summary>

- [x] hot script loading
- [x] help flag
- [x] init flag
- [x] verbose flag
- [x] points
- [x] print multiple points
- [x] installation
- [x] interfaces installing
- [x] simple example
- [x] installation guide
- [x] docs
- [x] single flags
- [x] path specify
- [x] Auto Create
</details>




## Other Docs
- [Apache License](LICENSE)
- [Security](SECURITY.md)
- [Contributing](CONTRIBUTING.md)
- [Code of Conduct](CODE_OF_CONDUCT.md)





## Cat
<img src="https://i.pinimg.com/736x/52/7b/e0/527be0e257856244a3db109c0713c61c.jpg">