#include <UIAutomationClient.h>
#include <UIAutomationCore.h>
#include <cpplogger/cpplogger.h>

#include "event.h"
#include "types.h"
#include "uiahandler.h"
#include "util.h"

extern Logger::Logger *Log;

FocusChangeEventHandler::FocusChangeEventHandler(EventHandler handleFunc) {
  mEventHandler = handleFunc;
}

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

HRESULT
FocusChangeEventHandler::HandleFocusChangedEvent(
    IUIAutomationElement *pSender) {
  Log->Info(L"Focus change event received", GetCurrentThreadId(), __LONGFILE__);

  RawEvent *pRawEvent{};

  if (FAILED(RawEventFromIUIAutomationElement(UIA_AutomationFocusChangedEventId,
                                              pSender, &pRawEvent))) {
    return E_FAIL;
  }
  if (mEventHandler(pRawEvent) != 0) {
    return E_FAIL;
  }

  SafeRelease(&pSender);

  delete pRawEvent->Element;
  pRawEvent->Element = nullptr;

  delete pRawEvent;
  pRawEvent = nullptr;

  return S_OK;
}

PropertyChangeEventHandler::PropertyChangeEventHandler(
    EventHandler handleFunc) {
  mEventHandler = handleFunc;
}

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

  RawEvent *pRawEvent{};

  if (FAILED(RawEventFromIUIAutomationElement(
          UIA_AutomationPropertyChangedEventId, pSender, &pRawEvent))) {
    return E_FAIL;
  }
  if (mEventHandler(pRawEvent) != 0) {
    return E_FAIL;
  }

  delete pRawEvent->Element;
  pRawEvent->Element = nullptr;

  delete pRawEvent;
  pRawEvent = nullptr;

  return S_OK;
}

AutomationEventHandler::AutomationEventHandler(EventHandler handleFunc) {
  mEventHandler = handleFunc;
}

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
  Log->Info(L"Automation event received", GetCurrentThreadId(), __LONGFILE__);

  RawEvent *pRawEvent{};

  if (FAILED(RawEventFromIUIAutomationElement(eventId, pSender, &pRawEvent))) {
    return E_FAIL;
  }
  if (mEventHandler(pRawEvent)) {
    return E_FAIL;
  }

  delete pRawEvent->Element;
  pRawEvent->Element = nullptr;

  delete pRawEvent;
  pRawEvent = nullptr;

  SafeRelease(&pSender);

  return S_OK;
}
