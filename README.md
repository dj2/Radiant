# Radiant

Trying out things in WebGPU. This may not lead anywhere, it's mostly a playground to try things out
with WebGPU native.

## Requirements
 * `git`
 * `cmake`
 * `ninja`
 * `clang` or `gcc`

## Building
```
git submodule init
git submodule update
mkdir -p out/Debug
cd out/Debug
cmake -GNinja ../..
ninja
```

