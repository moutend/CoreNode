#pragma once

#include <vector>
#include <windows.h>

#include <Commctrl.h>
#include <oleacc.h>

#include "types.h"

HRESULT fetchAllElements(std::vector<RawElement *> &v);

HRESULT walkIAccessible(HWND hWindow, IAccessible *pAcc, int depth, int index,
                        std::vector<RawElement *> &v);
