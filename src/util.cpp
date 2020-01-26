#include <windows.h>

#include "util.h"

void SafeCloseHandle(HANDLE *pHandle) {
  if (pHandle != nullptr) {
    CloseHandle(*pHandle);
    *pHandle = nullptr;
  }
}

void SafeDelete(RawEvent **pRawEvent) {
  if (pRawEvent == nullptr) {
    return;
  }

  delete[](*pRawEvent)->Element->NameData;
  (*pRawEvent)->Element->NameData = nullptr;

  delete[](*pRawEvent)->Element->ClassNameData;
  (*pRawEvent)->Element->ClassNameData = nullptr;

  delete[](*pRawEvent)->Element->FrameworkNameData;
  (*pRawEvent)->Element->FrameworkNameData = nullptr;

  delete[](*pRawEvent)->Element->AriaRoleNameData;
  (*pRawEvent)->Element->AriaRoleNameData = nullptr;

  delete (*pRawEvent)->Element;
  (*pRawEvent)->Element = nullptr;

  delete (*pRawEvent);
  (*pRawEvent) = nullptr;
}
