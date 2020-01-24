CoreNode
========

A node which collects Windows events and UI elements.

The CoreNode is a part of [ScreenReaderX](https://github.com/moutend/ScreenReaderX)

## Develop

### Tools

- VisualStudio 2017
- git
- cmake
- clang-format

### Build

```console
git clone https://github.com/moutend/CoreNode
cd CoreNode
git submodule update --init --recursive
mkdir build
cd build
..\tools\build.bat
msbuild all.vcxproj
```

## LICENSE

MIT
