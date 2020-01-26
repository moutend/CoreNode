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

  wchar_t *nameData = (*pRawEvent)->Element->NameData;

  if (nameData != nullptr) {
    delete[] nameData;
    nameData = nullptr;
  }

  wchar_t *classNameData = (*pRawEvent)->Element->ClassNameData;

  if (classNameData != nullptr) {
    delete[] classNameData;
    classNameData = nullptr;
  }

  wchar_t *frameworkNameData = (*pRawEvent)->Element->FrameworkNameData;

  if (frameworkNameData != nullptr) {
    delete[] frameworkNameData;
    frameworkNameData = nullptr;
  }

  wchar_t *ariaRoleNameData = (*pRawEvent)->Element->AriaRoleNameData;

  if (ariaRoleNameData != nullptr) {
    delete[] ariaRoleNameData;
    ariaRoleNameData = nullptr;
  }

  delete (*pRawEvent)->Element;
  (*pRawEvent)->Element = nullptr;

  delete (*pRawEvent);
  (*pRawEvent) = nullptr;
}
