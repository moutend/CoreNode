#include <UIAutomationClient.h>
#include <UIAutomationCore.h>
#include <cpplogger/cpplogger.h>
#include <mutex>
#include <sstream>

#include "uiahandler.h"
#include "util.h"

extern Logger::Logger *Log;

FocusChangeEventHandler::FocusChangeEventHandler() {}

ULONG FocusChangeEventHandler::AddRef() {
  ULONG ret = InterlockedIncrement(&mRefCount);
  return ret;
}

ULONG FocusChangeEventHandler::Release() {
  ULONG ret = InterlockedDecrement(&mRefCount);
  if (ret == 0) {
    delete this;
    return 0;
  }
  return ret;
}

HRESULT FocusChangeEventHandler::QueryInterface(REFIID riid,
                                                void **ppInterface) {
  if (riid == __uuidof(IUnknown))
    *ppInterface = static_cast<IUIAutomationFocusChangedEventHandler *>(this);
  else if (riid == __uuidof(IUIAutomationFocusChangedEventHandler))
    *ppInterface = static_cast<IUIAutomationFocusChangedEventHandler *>(this);
  else {
    *ppInterface = nullptr;
    return E_NOINTERFACE;
  }
  this->AddRef();
  return S_OK;
}

bool FocusChangeEventHandler::isSameElement(Element *pElement) {
  bool isSame{false};

  isSame = mLeft == pElement->mLeft;
  isSame &= mTop == pElement->mTop;
  isSame &= mWidth == pElement->mWidth;
  isSame &= mHeight == pElement->mHeight;

  if (isSame) {
    return true;
  }

  mLeft = pElement->mLeft;
  mTop = pElement->mTop;
  mWidth = pElement->mWidth;
  mHeight = pElement->mHeight;

  return false;
}

HRESULT
FocusChangeEventHandler::HandleFocusChangedEvent(
    IUIAutomationElement *pSender) {
  Log->Info(L"Focus change event received", GetCurrentThreadId(), __LONGFILE__);

  if (isEmptyIUIAutomationElement(pSender)) {
    return S_OK;
  }

  HRESULT hr{};
  Element *pElement{nullptr};

  hr = logIUIAutomationElement(pSender, __LONGFILE__);

  if (FAILED(hr)) {
    return hr;
  }

  CONTROLTYPEID controlTypeId{};

  hr = pSender->get_CachedControlType(&controlTypeId);

  if (FAILED(hr)) {
    return hr;
  }

  pElement = new Element();

  hr = pElement->CopyFromIUIAutomationElement(pSender);

  if (FAILED(hr)) {
    goto CLEANUP;
  }
  switch (controlTypeId) {
  case UIA_WindowControlTypeId:
    hr = mWindowElement->Set(pElement);

    if (FAILED(hr)) {
      goto CLEANUP;
    }
    if (!SetEvent(mWindowEvent)) {
      Log->Fail(L"Failed to send event", GetCurrentThreadId(), __LONGFILE__);
    }
    break;
  default:
    hr = mTargetElement->Set(pElement);

    if (FAILED(hr)) {
      goto CLEANUP;
    }
    if (!SetEvent(mTargetEvent)) {
      Log->Fail(L"Failed to send event", GetCurrentThreadId(), __LONGFILE__);
    }
  }

CLEANUP:

  if (pElement != nullptr) {
    delete pElement;
    pElement = nullptr;
  }

  return hr;
}

PropertyChangeEventHandler::PropertyChangeEventHandler() {}

ULONG PropertyChangeEventHandler::AddRef() {
  ULONG ret = InterlockedIncrement(&mRefCount);
  return ret;
}

ULONG PropertyChangeEventHandler::Release() {
  ULONG ret = InterlockedDecrement(&mRefCount);
  if (ret == 0) {
    delete this;
    return 0;
  }
  return ret;
}

HRESULT PropertyChangeEventHandler::QueryInterface(REFIID riid,
                                                   void **ppInterface) {
  if (riid == __uuidof(IUnknown))
    *ppInterface =
        static_cast<IUIAutomationPropertyChangedEventHandler *>(this);
  else if (riid == __uuidof(IUIAutomationPropertyChangedEventHandler))
    *ppInterface =
        static_cast<IUIAutomationPropertyChangedEventHandler *>(this);
  else {
    *ppInterface = nullptr;
    return E_NOINTERFACE;
  }
  this->AddRef();
  return S_OK;
}

HRESULT
PropertyChangeEventHandler::HandlePropertyChangedEvent(
    IUIAutomationElement *pSender, PROPERTYID propertyId, VARIANT newValue) {
  Log->Info(L"Property change event received", GetCurrentThreadId(),
            __LONGFILE__);

  if (isEmptyIUIAutomationElement(pSender)) {
    return S_OK;
  }

  HRESULT hr{};
  Element *pElement{nullptr};

  hr = logIUIAutomationElement(pSender, __LONGFILE__);

  if (FAILED(hr)) {
    return hr;
  }

  pElement = new Element();

  hr = pElement->CopyFromIUIAutomationElement(pSender);

  if (FAILED(hr)) {
    goto CLEANUP;
  }

  hr = mTargetElement->Set(pElement);

  if (FAILED(hr)) {
    goto CLEANUP;
  }
  if (!SetEvent(mTargetEvent)) {
    Log->Fail(L"Failed to send event", GetCurrentThreadId(), __LONGFILE__);
  }

CLEANUP:

  if (pElement != nullptr) {
    delete pElement;
    pElement = nullptr;
  }

  return hr;
}

AutomationEventHandler::AutomationEventHandler() {}

ULONG AutomationEventHandler::AddRef() {
  ULONG ret = InterlockedIncrement(&mRefCount);
  return ret;
}

ULONG AutomationEventHandler::Release() {
  ULONG ret = InterlockedDecrement(&mRefCount);
  if (ret == 0) {
    delete this;
    return 0;
  }
  return ret;
}

HRESULT AutomationEventHandler::QueryInterface(REFIID riid,
                                               void **ppInterface) {
  if (riid == __uuidof(IUnknown))
    *ppInterface = static_cast<IUIAutomationEventHandler *>(this);
  else if (riid == __uuidof(IUIAutomationEventHandler))
    *ppInterface = static_cast<IUIAutomationEventHandler *>(this);
  else {
    *ppInterface = nullptr;
    return E_NOINTERFACE;
  }
  this->AddRef();
  return S_OK;
}

HRESULT
AutomationEventHandler::HandleAutomationEvent(IUIAutomationElement *pSender,
                                              EVENTID eventId) {
  Log->Info(L"Automation change event received", GetCurrentThreadId(),
            __LONGFILE__);

  if (isEmptyIUIAutomationElement(pSender)) {
    return S_OK;
  }

  HRESULT hr{};
  Element *pElement{nullptr};

  hr = logIUIAutomationElement(pSender, __LONGFILE__);

  if (FAILED(hr)) {
    return hr;
  }

  pElement = new Element();

  hr = pElement->CopyFromIUIAutomationElement(pSender);

  if (FAILED(hr)) {
    goto CLEANUP;
  }

  hr = mTargetElement->Set(pElement);

  if (FAILED(hr)) {
    goto CLEANUP;
  }
  if (!SetEvent(mTargetEvent)) {
    Log->Fail(L"Failed to send event", GetCurrentThreadId(), __LONGFILE__);
  }

CLEANUP:

  if (pElement != nullptr) {
    delete pElement;
    pElement = nullptr;
  }

  return hr;
}
