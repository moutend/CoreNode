#include <cstring>
#include <cwchar>
#include <windows.h>

#include "event.h"

HRESULT RawElementFromIUIAutomationElement(IUIAutomationElement *pElement,
                                           RawElement **pRawElement) {
  if (pElement == nullptr || pRawElement == nullptr) {
    return E_FAIL;
  }

  *pRawElement = new RawElement;

  CONTROLTYPEID controlTypeId{};

  if (FAILED(pElement->get_CachedControlType(&controlTypeId))) {
    controlTypeId = 0;
  }

  (*pRawElement)->ControlTypeId = static_cast<int32_t>(controlTypeId);

  wchar_t *name{};

  if (FAILED(pElement->get_CurrentName(&name))) {
    name = nullptr;
  }
  if (name != nullptr) {
    size_t nameLength = std::wcslen(name);

    (*pRawElement)->NameData = new wchar_t[nameLength + 1]{};
    std::wmemcpy((*pRawElement)->NameData, name, nameLength);
    (*pRawElement)->NameLength = static_cast<int32_t>(nameLength);

    SysFreeString(name);
    name = nullptr;
  }

  wchar_t *className{nullptr};

  if (FAILED(pElement->get_CachedClassName(&className))) {
    className = nullptr;
  }
  if (className != nullptr) {
    size_t classNameLength = std::wcslen(className);

    (*pRawElement)->ClassNameData = new wchar_t[classNameLength + 1]{};
    std::wmemcpy((*pRawElement)->ClassNameData, className, classNameLength);
    (*pRawElement)->ClassNameLength = static_cast<int32_t>(classNameLength);

    SysFreeString(className);
    className = nullptr;
  }

  wchar_t *frameworkName{};

  if (FAILED(pElement->get_CachedFrameworkId(&frameworkName))) {
    frameworkName = nullptr;
  }
  if (frameworkName != nullptr) {
    size_t frameworkNameLength = std::wcslen(frameworkName);

    (*pRawElement)->FrameworkNameData = new wchar_t[frameworkNameLength + 1]{};
    std::wmemcpy((*pRawElement)->FrameworkNameData, frameworkName,
                 frameworkNameLength);
    (*pRawElement)->FrameworkNameLength =
        static_cast<int32_t>(frameworkNameLength);

    SysFreeString(frameworkName);
    frameworkName = nullptr;
  }

  RECT boundingRectangle{0, 0, 0, 0};

  if (FAILED(pElement->get_CurrentBoundingRectangle(&boundingRectangle))) {
  }

  (*pRawElement)->Left = boundingRectangle.left;
  (*pRawElement)->Top = boundingRectangle.left;
  (*pRawElement)->Width = boundingRectangle.right - boundingRectangle.left;
  (*pRawElement)->Height = boundingRectangle.bottom - boundingRectangle.top;

  return S_OK;
}

HRESULT RawEventFromIUIAutomationElement(int32_t eventId,
                                         IUIAutomationElement *pElement,
                                         RawEvent **pRawEvent) {
  if (pElement == nullptr || pRawEvent == nullptr) {
    return E_FAIL;
  }

  RawElement *pRawElement;

if (FAILED(RawElementFromIUIAutomationElement(pElement, &pRawElement)) {
    return E_FAIL;
}

*pRawEvent = new RawEvent;

(*pRawEvent)->RawElement = pRawElement;
(*pRawEvent)->EventId = eventId;

return S_OK;
}
