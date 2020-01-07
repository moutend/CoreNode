#pragma once

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
void logElement(Element *pElement);
HRESULT logIUIAutomationElement(int eventId, IUIAutomationElement *pElement,
                                const wchar_t *longfile);
HRESULT printElements(IUIAutomationElementArray *pElements);
