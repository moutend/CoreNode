#pragma once

#include <UIAutomationClient.h>
#include <cstdint>
#include <windows.h>

#include "types.h"

template <class T> void SafeRelease(T **ppT) {
  if (ppT == nullptr) {
    return;
  }
  if (*ppT == nullptr) {
    return;
  }

  (*ppT)->Release();
  *ppT = nullptr;
}

void SafeCloseHandle(HANDLE *pHandle);
void SafeDelete(RawEvent **pRawEvent);
