RBP
=======
# Pipeline
our remote bridge pipeline consist of following
components.

## TRAP
TRAP (Tiny REST API disPatcher) is a simple
single thread http server that receive and dispatch
HTTP requests into RBP pipeline.

## T-REX
T-REX (Tiny REST eXchanger) is a simple proxy
for REST protocol over http. for now it support
only http.

# Dependency
1. [CMake 2.6](http://cmake.org)
2. [libsoup 2.48](https://developer.gnome.org/libsoup/stable/)

# Installation
```
cmake .
make
```
