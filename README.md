# Radiant

Trying out things in WebGPU. This may not lead anywhere, it's mostly a playground to try things out
with WebGPU native.

## Requirements
 * `depot_tools`
 * `cmake`
 * `ninja`
 * `clang` or `gcc`

## Building
```
gclient sync --jobs=16`
mkdir -p out/Debug
cd out/Debug
cmake -GNinja ../..
ninja
```

