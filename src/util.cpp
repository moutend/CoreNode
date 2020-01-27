#include <cpplogger/cpplogger.h>
#include <windows.h>

#include "util.h"
#include <strsafe.h>

extern Logger::Logger *Log;

void SafeCloseHandle(HANDLE *pHandle) {
  if (pHandle != nullptr) {
    CloseHandle(*pHandle);
    *pHandle = nullptr;
  }
}

void SafeDelete(RawEvent **pRawEvent) {
return;
  if (pRawEvent == nullptr) {
    return;
  }
  if ((*pRawEvent)->Element->NameLength > 0) {
    delete[](*pRawEvent)->Element->NameData;
    (*pRawEvent)->Element->NameData = nullptr;
  }
  if ((*pRawEvent)->Element->ClassNameLength > 0) {
    delete[](*pRawEvent)->Element->ClassNameData;
    (*pRawEvent)->Element->ClassNameData = nullptr;
  }
  if (false && (*pRawEvent)->Element->FrameworkNameLength > 0) {
    delete[](*pRawEvent)->Element->FrameworkNameData;
    (*pRawEvent)->Element->FrameworkNameData = nullptr;
  }
  if (false && (*pRawEvent)->Element->AriaRoleNameLength > 0) {
    delete[](*pRawEvent)->Element->AriaRoleNameData;
    (*pRawEvent)->Element->AriaRoleNameData = nullptr;
  }

  delete (*pRawEvent)->Element;
  (*pRawEvent)->Element = nullptr;

  delete (*pRawEvent);
  (*pRawEvent) = nullptr;
}
