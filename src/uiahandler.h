#pragma once

#include <UIAutomation.h>
#include <cstdint>
#include <oleauto.h>
#include <windows.h>

#include "element.h"

class FocusChangeEventHandler : public IUIAutomationFocusChangedEventHandler {
public:
  FocusChangeEventHandler();

  // IUnknown methods
  ULONG STDMETHODCALLTYPE AddRef();
  ULONG STDMETHODCALLTYPE Release();
  HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppInterface);

  // IUIAutomationFocusChangedEventHandler methods
  HRESULT STDMETHODCALLTYPE
  HandleFocusChangedEvent(IUIAutomationElement *pSender);
  bool isSameElement(Element *pElement);

  ElementSingleton *mTargetElement = nullptr;
  ElementSingleton *mWindowElement = nullptr;
  HANDLE mTargetEvent = nullptr;
  HANDLE mWindowEvent = nullptr;

private:
  LONG mRefCount;
  int32_t mLeft = 0;
  int32_t mTop = 0;
  int32_t mWidth = 0;
  int32_t mHeight = 0;
};

class PropertyChangeEventHandler
    : public IUIAutomationPropertyChangedEventHandler {
public:
  PropertyChangeEventHandler();

  // IUnknown methods
  ULONG STDMETHODCALLTYPE AddRef();
  ULONG STDMETHODCALLTYPE Release();
  HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppInterface);

  // IUIAutomationPropertyChangedEventHandler methods
  HRESULT STDMETHODCALLTYPE HandlePropertyChangedEvent(
      IUIAutomationElement *sender, PROPERTYID propertyId, VARIANT newValue);

  ElementSingleton *mTargetElement = nullptr;
  HANDLE mTargetEvent = nullptr;

private:
  LONG mRefCount;
};

class AutomationEventHandler : public IUIAutomationEventHandler {
public:
  AutomationEventHandler();

  // IUnknown methods
  ULONG STDMETHODCALLTYPE AddRef();
  ULONG STDMETHODCALLTYPE Release();
  HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppInterface);

  // IUIAutomationEventHandler methods
  HRESULT STDMETHODCALLTYPE HandleAutomationEvent(IUIAutomationElement *sender,
                                                  EVENTID eventId);

  ElementSingleton *mTargetElement = nullptr;
  HANDLE mTargetEvent = nullptr;

private:
  LONG mRefCount;
};
