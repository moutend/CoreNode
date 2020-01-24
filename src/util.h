#pragma once

#include <UIAutomationClient.h>
#include <cstdint>
#include <windows.h>

#include "event.h"

template <class T> void SafeRelease(T **ppT) {
  if (*ppT) {
    (*ppT)->Release();
    *ppT = nullptr;
  }
}

void SafeCloseHandle(HANDLE *pHandle);
