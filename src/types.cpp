#include <cpplogger/cpplogger.h>
#include <cstring>
#include <cwchar>
#include <windows.h>

#include <Commctrl.h>
#include <strsafe.h>

#include "types.h"
#include "util.h"

extern Logger::Logger *Log;

HRESULT RawElementFromIUIAutomationElement(IUIAutomationElement *pElement,
                                           RawElement **pRawElement) {
  if (pElement == nullptr || pRawElement == nullptr) {
    return E_FAIL;
  }

  *pRawElement = new RawElement;

  int processId{};

  if (false && FAILED(pElement->get_CachedProcessId(&processId))) {
    return E_FAIL;
  }

  wchar_t *processName{};
  size_t processNameLength{};

  if (false && SUCCEEDED(GetProcessName(processId, &processName, &processNameLength))) {
    (*pRawElement)->ProcessNameLength = static_cast<int32_t>(processNameLength);
    (*pRawElement)->ProcessNameData = new wchar_t[processNameLength + 1]{};
    std::wmemcpy((*pRawElement)->ProcessNameData, processName,
                 processNameLength);

    delete[] processName;
    processName = nullptr;
  } else {
    (*pRawElement)->ProcessNameLength = 0;
    (*pRawElement)->ProcessNameData = nullptr;
  }

  CONTROLTYPEID controlTypeId{};

  if (SUCCEEDED(pElement->get_CachedControlType(&controlTypeId))) {
    (*pRawElement)->ControlTypeId = static_cast<int32_t>(controlTypeId);
  } else {
    (*pRawElement)->ControlTypeId = 0;
  }

  (*pRawElement)->Role = 0;

  wchar_t *name{};

  if (SUCCEEDED(pElement->get_CachedName(&name))) {
    size_t nameLength = std::wcslen(name);

    (*pRawElement)->NameData = new wchar_t[nameLength + 1]{};
    std::wmemcpy((*pRawElement)->NameData, name, nameLength);
    (*pRawElement)->NameLength = static_cast<int32_t>(nameLength);

    SysFreeString(name);
    name = nullptr;
  } else {
    (*pRawElement)->NameData = nullptr;
    (*pRawElement)->NameLength = 0;
  }

  wchar_t *className{nullptr};

  if (SUCCEEDED(pElement->get_CachedClassName(&className))) {
    size_t classNameLength = std::wcslen(className);

    (*pRawElement)->ClassNameData = new wchar_t[classNameLength + 1]{};
    std::wmemcpy((*pRawElement)->ClassNameData, className, classNameLength);
    (*pRawElement)->ClassNameLength = static_cast<int32_t>(classNameLength);

    SysFreeString(className);
    className = nullptr;
  } else {
    (*pRawElement)->ClassNameData = nullptr;
    (*pRawElement)->ClassNameLength = 0;
  }

  wchar_t *ariaRoleName{};

  if (SUCCEEDED(pElement->get_CachedAriaRole(&ariaRoleName))) {
    size_t ariaRoleNameLength = std::wcslen(ariaRoleName);

    (*pRawElement)->AriaRoleNameData = new wchar_t[ariaRoleNameLength + 1]{};
    std::wmemcpy((*pRawElement)->AriaRoleNameData, ariaRoleName,
                 ariaRoleNameLength);
    (*pRawElement)->AriaRoleNameLength =
        static_cast<int32_t>(ariaRoleNameLength);

    SysFreeString(ariaRoleName);
    ariaRoleName = nullptr;
  } else {
    (*pRawElement)->AriaRoleNameData = nullptr;
    (*pRawElement)->AriaRoleNameLength = 0;
  }

  RECT boundingRectangle{0, 0, 0, 0};

  if (SUCCEEDED(pElement->get_CachedBoundingRectangle(&boundingRectangle))) {
    (*pRawElement)->Left = boundingRectangle.left;
    (*pRawElement)->Top = boundingRectangle.left;
    (*pRawElement)->Width = boundingRectangle.right - boundingRectangle.left;
    (*pRawElement)->Height = boundingRectangle.bottom - boundingRectangle.top;
  } else {
    (*pRawElement)->Left = 0;
    (*pRawElement)->Top = 0;
    (*pRawElement)->Width = 0;
    (*pRawElement)->Height = 0;
  }

  return S_OK;
}

HRESULT RawEventFromIUIAutomationElement(int32_t eventId,
                                         IUIAutomationElement *pElement,
                                         RawEvent **pRawEvent) {
  if (pElement == nullptr || pRawEvent == nullptr) {
    return E_FAIL;
  }

  RawElement *pRawElement;

  if (FAILED(RawElementFromIUIAutomationElement(pElement, &pRawElement))) {
    return E_FAIL;
  }

  *pRawEvent = new RawEvent;

  (*pRawEvent)->Element = pRawElement;
  (*pRawEvent)->EventId = eventId;

  return S_OK;
}

HRESULT RawElementFromIAccessible(HWND hWindow, IAccessible *pAcc,
                                  RawElement **pRawElement) {
  if (pAcc == nullptr || pRawElement == nullptr) {
    return E_FAIL;
  }

  *pRawElement = new RawElement;

  DWORD processId{};

  GetWindowThreadProcessId(hWindow, &processId);

  wchar_t *processName{};
  size_t processNameLength{};

  if (false && SUCCEEDED(GetProcessName(processId, &processName, &processNameLength))) {
    (*pRawElement)->ProcessNameLength = static_cast<int32_t>(processNameLength);
    (*pRawElement)->ProcessNameData = new wchar_t[processNameLength + 1]{};
    std::wmemcpy((*pRawElement)->ProcessNameData, processName,
                 processNameLength);

    delete[] processName;
    processName = nullptr;
  } else {
    (*pRawElement)->ProcessNameLength = 0;
    (*pRawElement)->ProcessNameData = nullptr;
  }

  VARIANT varChild;
  varChild.vt = VT_I4;
  varChild.lVal = CHILDID_SELF;

  wchar_t *name{};

  if (false && SUCCEEDED(pAcc->get_accName(varChild, &name))) {
    size_t nameLength = std::wcslen(name);

    (*pRawElement)->NameData = new wchar_t[nameLength + 1]{};
    std::wmemcpy((*pRawElement)->NameData, name, nameLength);
    (*pRawElement)->NameLength = static_cast<int32_t>(nameLength);

    SysFreeString(name);
    name = nullptr;
  } else {
    (*pRawElement)->NameLength = 0;
    (*pRawElement)->NameData = nullptr;
  }

  DWORD roleId{};
  VARIANT varResult;

  if (FAILED(pAcc->get_accRole(varChild, &varResult))) {
    roleId = 0;
  } else {
    roleId = varResult.lVal;
  }

  (*pRawElement)->Role = static_cast<int32_t>(roleId);
  (*pRawElement)->ControlTypeId = 0;

  (*pRawElement)->ClassNameData = nullptr;
  (*pRawElement)->AriaRoleNameData = nullptr;

  (*pRawElement)->ClassNameLength = 0;
  (*pRawElement)->AriaRoleNameLength = 0;

  long left{};
  long top{};
  long width{};
  long height{};

  if (SUCCEEDED(pAcc->accLocation(&left, &top, &width, &height, varChild))) {
    (*pRawElement)->Left = left;
    (*pRawElement)->Top = top;
    (*pRawElement)->Width = width;
    (*pRawElement)->Height = height;
  } else {
    (*pRawElement)->Left = 0;
    (*pRawElement)->Top = 0;
    (*pRawElement)->Width = 0;
    (*pRawElement)->Height = 0;
  }

  return S_OK;
}

HRESULT RawEventFromIAccessible(HWND hWindow, int32_t eventId,
                                IAccessible *pAcc, RawEvent **pRawEvent) {
  if (pAcc == nullptr || pRawEvent == nullptr) {
    return E_FAIL;
  }

  RawElement *pRawElement;

  if (FAILED(RawElementFromIAccessible(hWindow, pAcc, &pRawElement))) {
    return E_FAIL;
  }

  *pRawEvent = new RawEvent;

  (*pRawEvent)->Element = pRawElement;
  (*pRawEvent)->EventId = eventId;

  return S_OK;
}
