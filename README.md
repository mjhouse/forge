# Forge

Forge is a 3D design solution for manufacturing and plant construction, currently under heavy development. It's written top-to-bottom in C++ using Qt5, primarily for (and on) Windows 10, although some thought has been given to keeping the codebase cross-platform for later porting. 

![](docs/mouse-extrude.gif)

## Goals

### Fast
A primary goal of Forge is to make failure *easy*. Iteration is part of any development process, and plant design is no different. Conventional manufacturing design applications have heavy processes that are awkward to configure and start, and that take a long time to complete. This inhibits creativity and risk-taking, because recovering from these processes is time-consuming, if it's even possible. By prioritizing speed, we make experimentation and failure recovery painless.

### Reliable
Forge will be rigorously tested and iteratively redesigned until __there are no bugs__. Nothing is worse, or breaks the design process more thoroughly, than an unexpected failure that destroys or corrupts project files. This goal supports the first, because speed isn't just the rate at which things get done- it's the number of times they have to be done. 

### Live
Forge will be *live*. This means that as actions are completed locally, they will be shared across the network so that other users can see them. Communication, either through VOIP or direct messages, is a part of this. By allowing multiple designers to have eyes on the same work at the same time and communicate with each other about the project as it unfolds, Forge will support higher quality work and cooperation between designers.


## Features

### Current
* 3D Views
* Model creation control
* Model transform control
* JSON import

### Planned
* Snap-to-surface / Snap-to-line
* Placement by two points
* Connections
* Slabs / walls
* Pipes

## Building

### Using Visual Studio

You should be able to simply open the root directory in Visual Studio, generate a CMake cache and then build. I've only tested with __Visual Studio Community 2019__, however.

### Using CMake

Source the `vcvars64.bat` file:

```
>> "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/Build/vcvars64.bat"
```

Clone the repository and build:
```
git clone https://github.com/mjhouse/forge.git
cd bin/
cmake ../..
```

If you happen to be using __Visual Studio Enterprise 2019__, you coule also run `.github/scripts/windows-build.ps1` (a CI/CD build script).

## Contributing

This project is currently not looking for outside support.