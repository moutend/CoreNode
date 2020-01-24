#pragma once

#include <UIAutomationClient.h>
#include <cstdint>
#include <windows.h>

#include "types.h"

HRESULT RawElementFromIUIAutomationElement(IUIAutomationElement *pElement,
                                           RawElement **pRawElement);

HRESULT RawEventFromIUIAutomation(int32_t eventId,
                                  IUIAutomationElement *pElement,
                                  RawEvent **pRawEvent);
