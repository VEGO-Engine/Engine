##### Compiling:

```sh
git submodule update --init # only needed once
cmake -S . -B build
cmake --build build
```
For Windows systems using MinGW the flag `-G "MinGW Makefiles"` has to be specified

The executable can be found as `build/SDL_Minigame` after building