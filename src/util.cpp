#include <cpplogger/cpplogger.h>
#include <windows.h>

#include <tlhelp32.h>
#include <strsafe.h>

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
  if (pRawEvent == nullptr) {
    return;
  }
  if (*pRawEvent == nullptr) {
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
  if ((*pRawEvent)->Element->AriaRoleNameLength > 0) {
    delete[](*pRawEvent)->Element->AriaRoleNameData;
    (*pRawEvent)->Element->AriaRoleNameData = nullptr;
  }
  if ((*pRawEvent)->Element->ProcessNameLength > 0) {
    delete[](*pRawEvent)->Element->ProcessNameData;
    (*pRawEvent)->Element->ProcessNameData = nullptr;
  }

  delete (*pRawEvent)->Element;
  (*pRawEvent)->Element = nullptr;

  delete (*pRawEvent);
  (*pRawEvent) = nullptr;
}

HRESULT GetProcessName(DWORD processId, wchar_t **processName,
                       size_t *processNameLength) {
  HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

  if (hSnapshot == nullptr) {
    return E_FAIL;
  }

  PROCESSENTRY32W processEntry{};

  processEntry.dwSize = sizeof(PROCESSENTRY32W);

  bool hasProcessEntry = Process32FirstW(hSnapshot, &processEntry);

  while (hasProcessEntry) {
    if (processEntry.th32ProcessID == processId) {
      wchar_t *buffer = new wchar_t[256]{};
      StringCbPrintfW(buffer, 511, L"ProcessName is %s", processEntry.szExeFile);
      Log->Info(buffer, GetCurrentThreadId(), __LONGFILE__);
      delete[] buffer;
      buffer = nullptr;
      break;
      (*processNameLength) = MAX_PATH;
      (*processName) = new wchar_t[MAX_PATH + 1]{};
      std::wmemcpy((*processName), processEntry.szExeFile, MAX_PATH);

      break;
    }

    hasProcessEntry = Process32NextW(hSnapshot, &processEntry);
  }

  SafeCloseHandle(&hSnapshot);

  return S_OK;
}
