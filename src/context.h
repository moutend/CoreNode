#pragma once

#include <windows.h>

#include "event.h"

struct LogLoopContext {
  HANDLE QuitEvent = nullptr;
};

struct UIALoopContext {
  HANDLE QuitEvent = nullptr;
  HANDLE NotifyEvent = nullptr;
  EventQueue *EventQueue = nullptr;
};

struct RequestLoopContext {
  HANDLE QuitEvent = nullptr;
  HANDLE NotifyEvent = nullptr;
  EventQueue *EventQueue = nullptr;
};
