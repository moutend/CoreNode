#include <cstring>
#include <cwchar>
#include <windows.h>

#include <Commctrl.h>

#include "types.h"

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
    (*pRawElement)->NameData = nullptr;
    (*pRawElement)->NameLength = 0;
  } else {
    size_t nameLength = std::wcslen(name);

    (*pRawElement)->NameData = new wchar_t[nameLength + 1]{};
    std::wmemcpy((*pRawElement)->NameData, name, nameLength);
    (*pRawElement)->NameLength = static_cast<int32_t>(nameLength);

    SysFreeString(name);
    name = nullptr;
  }

  wchar_t *className{nullptr};

  if (FAILED(pElement->get_CachedClassName(&className))) {
    (*pRawElement)->ClassNameData = nullptr;
    (*pRawElement)->ClassNameLength = 0;
  } else {
    size_t classNameLength = std::wcslen(className);

    (*pRawElement)->ClassNameData = new wchar_t[classNameLength + 1]{};
    std::wmemcpy((*pRawElement)->ClassNameData, className, classNameLength);
    (*pRawElement)->ClassNameLength = static_cast<int32_t>(classNameLength);

    SysFreeString(className);
    className = nullptr;
  }

  wchar_t *frameworkName{};

  if (FAILED(pElement->get_CachedFrameworkId(&frameworkName))) {
    (*pRawElement)->FrameworkNameData = nullptr;
    (*pRawElement)->FrameworkNameLength = 0;
  } else {
    size_t frameworkNameLength = std::wcslen(frameworkName);

    (*pRawElement)->FrameworkNameData = new wchar_t[frameworkNameLength + 1]{};
    std::wmemcpy((*pRawElement)->FrameworkNameData, frameworkName,
                 frameworkNameLength);
    (*pRawElement)->FrameworkNameLength =
        static_cast<int32_t>(frameworkNameLength);

    SysFreeString(frameworkName);
    frameworkName = nullptr;
  }

  wchar_t *ariaRoleName{};

  if (FAILED(pElement->get_CachedAriaRole(&ariaRoleName))) {
    (*pRawElement)->AriaRoleNameData = nullptr;
    (*pRawElement)->AriaRoleNameLength = 0;
  } else {
    size_t ariaRoleNameLength = std::wcslen(ariaRoleName);

    (*pRawElement)->AriaRoleNameData = new wchar_t[ariaRoleNameLength + 1]{};
    std::wmemcpy((*pRawElement)->AriaRoleNameData, ariaRoleName,
                 ariaRoleNameLength);
    (*pRawElement)->AriaRoleNameLength =
        static_cast<int32_t>(ariaRoleNameLength);

    SysFreeString(ariaRoleName);
    ariaRoleName = nullptr;
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

  if (FAILED(RawElementFromIUIAutomationElement(pElement, &pRawElement))) {
    return E_FAIL;
  }

  *pRawEvent = new RawEvent;

  (*pRawEvent)->Element = pRawElement;
  (*pRawEvent)->EventId = eventId;

  return S_OK;
}

HRESULT RawElementFromIAccessible(IAccessible *pAcc, RawElement **pRawElement) {
  if (pAcc == nullptr || pRawElement == nullptr) {
    return E_FAIL;
  }

  *pRawElement = new RawElement;

  VARIANT varChild;
  varChild.vt = VT_I4;
  varChild.lVal = CHILDID_SELF;

  wchar_t *name{};

  if (FAILED(pAcc->get_accName(varChild, &name))) {
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

  DWORD roleId{};
  VARIANT varResult;

  if (FAILED(pAcc->get_accRole(varChild, &varResult))) {
    roleId = 0;
  } else {
    roleId = varResult.lVal;
  }

  (*pRawElement)->ControlTypeId = static_cast<int32_t>(roleId);

  long left{};
  long top{};
  long width{};
  long height{};

  if (FAILED(pAcc->accLocation(&left, &top, &width, &height, varChild))) {
    left = 0;
    top = 0;
    width = 0;
    height = 0;
  }

  (*pRawElement)->Left = left;
  (*pRawElement)->Top = top;
  (*pRawElement)->Width = width;
  (*pRawElement)->Height = height;

  return S_OK;
}

HRESULT RawEventFromIAccessible(int32_t eventId, IAccessible *pAcc,
                                RawEvent **pRawEvent) {
  if (pAcc == nullptr || pRawEvent == nullptr) {
    return E_FAIL;
  }

  RawElement *pRawElement;

  if (FAILED(RawElementFromIAccessible(pAcc, &pRawElement))) {
    return E_FAIL;
  }

  *pRawEvent = new RawEvent;

  (*pRawEvent)->Element = pRawElement;
  (*pRawEvent)->EventId = eventId;

  return S_OK;
}
