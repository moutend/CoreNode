#pragma once

#include <cstdint>

typedef struct {
  int32_t ControlTypeId;
  int32_t Role;
  int32_t Top;
  int32_t Left;
  int32_t Width;
  int32_t Height;
  int32_t NameLength;
  int32_t ClassNameLength;
  int32_t FrameworkNameLength;
  wchar_t *NameData;
  wchar_t *ClassNameData;
  wchar_t *FrameworkNameData;
} RawElement;

typedef struct {
  int32_t EventId;
  RawElement *Element;
} RawEvent;

typedef int64_t(__stdcall *EventHandler)(RawEvent *e);
