#pragma once

#include <windows.h>

#include "element.h"

struct LogLoopContext {
  HANDLE QuitEvent = nullptr;
};

struct UIALoopContext {
  HANDLE QuitEvent = nullptr;
  HANDLE WindowEvent = nullptr;
  HANDLE TargetEvent = nullptr;
  ElementSingleton *TargetElement = nullptr;
  ElementSingleton *WindowElement = nullptr;
};

struct RequestLoopContext {
  HANDLE QuitEvent = nullptr;
  HANDLE TargetEvent = nullptr;
  HANDLE WindowEvent = nullptr;
  ElementSingleton *TargetElement = nullptr;
  ElementSingleton *WindowElement = nullptr;
};
