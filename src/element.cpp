#include <cpplogger/cpplogger.h>
#include <cstring>
#include <iostream>
#include <windows.h>

#include <UIAutomationClient.h>
#include <strsafe.h>

#include "element.h"

extern Logger::Logger *Log;

Element::Element() {}

Element::~Element() {
  delete[] mName;
  mName = nullptr;
}

HRESULT
Element::CopyFromElement(Element *pElement) {
  if (pElement == nullptr) {
    return E_FAIL;
  }

  mLeft = pElement->mLeft;
  mTop = pElement->mTop;
  mWidth = pElement->mWidth;
  mHeight = pElement->mHeight;

  if (pElement->mName != nullptr) {
    size_t nameLength = std::wcslen(pElement->mName);
    mName = new wchar_t[nameLength + 1]{};
    std::wmemcpy(mName, pElement->mName, nameLength);
  }

  return S_OK;
}

HRESULT Element::CopyFromIUIAutomationElement(IUIAutomationElement *pElement) {
  if (pElement == nullptr) {
    return E_FAIL;
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
  }

  RECT boundingRectangle{0, 0, 0, 0};

  if (FAILED(pElement->get_CurrentBoundingRectangle(&boundingRectangle))) {
    return E_FAIL;
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

  return S_OK;
}

ElementSingleton::ElementSingleton() { mElement = new Element(); }

ElementSingleton::~ElementSingleton() {
  delete[] mElement;
  mElement = nullptr;
}

HRESULT ElementSingleton::Get(Element *pElement) {
  std::lock_guard<std::mutex> lock(mMutex);

  if (pElement == nullptr) {
    return E_FAIL;
  }

  return pElement->CopyFromElement(mElement);
}

void ElementSingleton::Sent() {
  std::lock_guard<std::mutex> lock(mMutex);

  mSent = true;

  return;
}

bool ElementSingleton::IsSent() {
  std::lock_guard<std::mutex> lock(mMutex);

  return mSent;
}

HRESULT ElementSingleton::Set(Element *pElement) {
  std::lock_guard<std::mutex> lock(mMutex);

  if (pElement == nullptr) {
    return E_FAIL;
  }

  wchar_t *name{};
  size_t length = std::wcslen(pElement->mName);

  if (length > 63) {
    length = 63;
  }

  name = new wchar_t[length + 1]{};
  std::wmemcpy(name, pElement->mName, length);

  wchar_t *buffer = new wchar_t[256]{};
  bool isSame{false};

  if (mLastElementName != nullptr) {
    isSame = std::wcscmp(mLastElementName, name) == 0;
  }

  HRESULT hr = StringCbPrintfW(buffer, 255, L"@@@ %s == %s = %s",
                               mLastElementName == nullptr ? L"nullptr"
                                                           : mLastElementName,
                               name, isSame ? L"true" : L"false");

  if (!FAILED(hr)) {
    Log->Info(buffer, GetCurrentThreadId(), __LONGFILE__);
  }

  delete[] buffer;

  if (isSame) {
    return S_OK;
  }

  delete[] mLastElementName;
  mLastElementName = new wchar_t[length + 1]{};
  std::wmemcpy(mLastElementName, name, length);

  mSent = false;

  return mElement->CopyFromElement(pElement);
}
