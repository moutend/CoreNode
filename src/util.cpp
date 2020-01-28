#include <cpplogger/cpplogger.h>
#include <windows.h>

#include <tlhelp32.h>

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
  if ((*pRawEvent)->Element->FrameworkNameLength > 0) {
    delete[](*pRawEvent)->Element->FrameworkNameData;
    (*pRawEvent)->Element->FrameworkNameData = nullptr;
  }
  if ((*pRawEvent)->Element->AriaRoleNameLength > 0) {
    delete[](*pRawEvent)->Element->AriaRoleNameData;
    (*pRawEvent)->Element->AriaRoleNameData = nullptr;
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
  processEntiry.cbSize = sizeof(PROCESSENTRY32);

  bool hasProcessEntry = Process32First(hSnapshot, &processEntry);

  while (hasProcessEntry) {
    if (processEntry.th32ProcessID == processId) {
      processNameLength = std::wcslen(processEntry.szExeFile);
      *processName = new wchar_t[processNameLength + 1]{};
      std::wmemcpy(processName, processEntry.szExeFile, processNameLength);

      break;
    }

    hasProcessEntry = Process32Next(hSnapshot, &processEntry);
  }

  SafeCloseHandle(&hSnapshot);

  return S_OK;
}
