## Config
See the file `CMakeLists.txt.config`.

## Build
### General
```bash
cmake -B build
cmake --build build
```
### Customized
```bash
cmake -B build -DBoost_ROOT=/path/to/boost
cmake --build build
```