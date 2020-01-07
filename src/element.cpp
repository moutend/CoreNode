#include <cpplogger/cpplogger.h>
#include <cstring>
#include <iostream>
#include <windows.h>

#include <UIAutomationClient.h>
#include <strsafe.h>

#include "element.h"

extern Logger::Logger *Log;

Element::Element() {}

Element::Element(Element *pElement) {
  if (pElement == nullptr) {
    return;
  }

  mControlTypeId = pElement->GetControlTypeId();
  mRole = pElement->GetRole();
  mLeft = pElement->GetLeft();
  mTop = pElement->GetTop();
  mWidth = pElement->GetWidth();
  mHeight = pElement->GetHeight();

  if (pElement->GetName() != nullptr) {
    size_t nameLength = std::wcslen(pElement->GetName());
    mName = new wchar_t[nameLength + 1]{};
    std::wmemcpy(mName, pElement->GetName(), nameLength);
  }
  if (pElement->GetClassName() != nullptr) {
    size_t classNameLength = std::wcslen(pElement->GetClassName());
    mClassName = new wchar_t[classNameLength + 1]{};
    std::wmemcpy(mClassName, pElement->GetClassName(), classNameLength);
  }
  if (pElement->GetFrameworkName() != nullptr) {
    size_t classNameLength = std::wcslen(pElement->GetFrameworkName());
    mFrameworkName = new wchar_t[classNameLength + 1]{};
    std::wmemcpy(mFrameworkName, pElement->GetFrameworkName(), classNameLength);
  }
}

Element::Element(IUIAutomationElement *pElement) {
  if (pElement == nullptr) {
    return;
  }

  CONTROLTYPEID controlTypeId{};

  if (FAILED(pElement->get_CachedControlType(&controlTypeId))) {
    controlTypeId = 0;
  }

  mControlTypeId = static_cast<int32_t>(controlTypeId);

  wchar_t *name{nullptr};

  if (FAILED(pElement->get_CurrentName(&name))) {
    name = nullptr;
  }
  if (name != nullptr) {
    size_t nameLength = std::wcslen(name);
    mName = new wchar_t[nameLength + 1]{};
    std::wmemcpy(mName, name, nameLength);

    SysFreeString(name);
    name = nullptr;
  } else {
    mName = new wchar_t[10];
    std::wmemcpy(mName, L"<nullptr>", 9);
  }

  wchar_t *className{nullptr};

  if (FAILED(pElement->get_CachedClassName(&className))) {
    className = nullptr;
  }
  if (className != nullptr) {
    size_t classNameLength = std::wcslen(className);
    mClassName = new wchar_t[classNameLength + 1]{};
    std::wmemcpy(mClassName, className, classNameLength);

    SysFreeString(className);
    className = nullptr;
  } else {
    mClassName = wchar_t[10]{};
    std::wmemcpy(mClassName, L"<nullptr>", 9);
  }

  wchar_t *frameworkName{nullptr};

  if (FAILED(pElement->get_CachedFrameworkId(&frameworkName))) {
    frameworkName = nullptr;
  }
  if (frameworkName != nullptr) {
    size_t frameworkNameLength = std::wcslen(frameworkName);
    mFrameworkName = new wchar_t[frameworkNameLength + 1]{};
    std::wmemcpy(mFrameworkName, frameworkName, frameworkNameLength);

    SysFreeString(frameworkName);
    frameworkName = nullptr;
  } else {
    mFrameworkName = wchar_t[10]{};
    std::wmemcpy(mFrameworkName, L"<nullptr>", 9);
  }

  RECT boundingRectangle{0, 0, 0, 0};

  if (FAILED(pElement->get_CurrentBoundingRectangle(&boundingRectangle))) {
    return;
  }

  mLeft = boundingRectangle.left;
  mTop = (boundingRectangle.top);
  mWidth = boundingRectangle.right - boundingRectangle.left;
  mHeight = (boundingRectangle.bottom - boundingRectangle.top);

  if (mWidth < 0) {
    mWidth = 0;
  }
  if (mHeight < 0) {
    mHeight = 0;
  }

  return;
}

Element::~Element() {
  delete[] mName;
  mName = nullptr;
}

wchar_t *Element::GetName() { return mName; }
wchar_t *Element::GetClassName() { return mClassName; }
wchar_t *Element::GetFrameworkName() { return mFrameworkName; }
int32_t Element::GetControlTypeId() { return mControlTypeId; }
int32_t Element::GetRole() { return mRole; }
int32_t Element::GetLeft() { return mLeft; }
int32_t Element::GetTop() { return mTop; }
int32_t Element::GetWidth() { return mWidth; }
int32_t Element::GetHeight() { return mHeight; }
