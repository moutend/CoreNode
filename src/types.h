#pragma once

#include <cstdint>
#include <windows.h>

#include <UIAutomationClient.h>
#include <oleacc.h>

typedef struct {
  int32_t Top;
  int32_t Left;
  int32_t Width;
  int32_t Height;
  int32_t ControlTypeId;
  int32_t NameLength;
  int32_t ClassNameLength;
  int32_t FrameworkNameLength;
  int32_t AriaRoleNameLength;
  wchar_t *NameData;
  wchar_t *ClassNameData;
  wchar_t *FrameworkNameData;
  wchar_t *AriaRoleNameData;
} RawElement;

typedef struct {
  int32_t EventId;
  RawElement *Element;
} RawEvent;

typedef int64_t(__stdcall *EventHandler)(RawEvent *e);

HRESULT RawElementFromIUIAutomationElement(IUIAutomationElement *pElement,
                                           RawElement **pRawElement);

HRESULT RawEventFromIUIAutomationElement(int32_t eventId,
                                         IUIAutomationElement *pElement,
                                         RawEvent **pRawEvent);

HRESULT RawElementFromIAccessible(IAccessible *pAcc, RawElement **pRawElement);

HRESULT RawEventFromIAccessible(int32_t eventId, IAccessible *pAcc,
                                RawEvent **pRawEvent);
