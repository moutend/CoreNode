#pragma once

#include <cstdint>

typedef struct {
  wchar_t *Name;
  int32_t ControlTypeId;
  int32_t Role;
  int32_t Top;
  int32_t Left;
  int32_t Width;
  int32_t Height;
  int64_t UnixSec;
  int64_t UnixNano;
} RawElement;
