<div align=center>
  <h1>Graphite</h1>
  <h2>Experimental/Prototype</h2>
</div>




## About
Graphite is simple 2D/3D math visual app like geogebra, desoms, amtplotlib in python. It works on c++ scripting language. It is based how scripts works via using interfaces and dll loading. Allows how swap dll on runtime for easy and nice experience. It uses my own rendering library [CWindow](https://github.com/daynlight/CWindow)

Why it exists:
  * I hate python
  * Geogebra is slow
  * I love my own software
  * Learning

For who it is:
  * For people that want faster graphical math app
  * People who hate python <3




## TOC
- [About](#about)
- [TOC](#toc)
- [Installation](#installation)
- [Usage](#usage)
  - [Run](#run)
  - [Flags](#flags)
- [Prerequisites](#prerequisites)
- [Versions and features](#versions-and-features)
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
### Flags
  * ```-h/--help```: show program help command.
  * ```-i/--init```: initialize default files.
  * ```-v/-d/--verbose/--debug```: turn on verbose mode.




## Prerequisites
   * ```CMake``` - for building.
   * ```C++17``` - for compilation.
   * ```Git``` - cloning **repo** and **submodules**




## Versions and features

<details open>
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




## Cat
<img src="https://i.pinimg.com/736x/52/7b/e0/527be0e257856244a3db109c0713c61c.jpg">