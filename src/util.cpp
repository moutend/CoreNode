#include <cpplogger/cpplogger.h>
#include <windows.h>

#include "util.h"

xtern Logger::Logger;

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

  wchar_t *buffer = new wchar_t[128]{};

HRESULT hr = StringCbPrintfW((buffer, 128, L"Name is %d", 
  (*pRawEvent)->Element->NameData == nullptr);

if (FAILED(hr)) {
    return;
}

Log->Info(buffer, GetCurrentThreadId(), __LONGFILE__);

delete[] buffer;
buffer = nullptr;

return;

wchar_t *nameData{};

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
