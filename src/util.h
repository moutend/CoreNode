#pragma once

#include <cstdint>
#include <UIAutomationClient.h>
#include <windows.h>

#include "element.h"

template <class T> void SafeRelease(T **ppT) {
  if (*ppT) {
    (*ppT)->Release();
    *ppT = nullptr;
  }
}

void SafeCloseHandle(HANDLE *pHandle);
bool isEmptyIUIAutomationElement(IUIAutomationElement *pElement);
void logEvent(int32_t eventCount, Event *pEvent);
HRESULT logIUIAutomationElement(int eventId, IUIAutomationElement *pElement,
                                const wchar_t *longfile);
HRESULT printElements(IUIAutomationElementArray *pElements);
