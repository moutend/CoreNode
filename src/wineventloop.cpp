#include <cpplogger/cpplogger.h>
#include <windows.h>

#include <Commctrl.h>
#include <oleacc.h>

#include "context.h"
#include "util.h"
#include "wineventloop.h"

extern Logger::Logger *Log;

static WinEventLoopContext *winEventLoopCtx{};

void eventCallback(HWINEVENTHOOK hHook, DWORD event, HWND hWindow,
                   LONG objectId, LONG childId, DWORD threadId,
                   DWORD eventTime) {
  if (objectId <= OBJID_ALERT) {
    return;
  }
  if (!IsWindow(hWindow)) {
    return;
  }
  if (objectId == 0 && childId == 0) {
    objectId = OBJID_CLIENT;
  }

  IAccessible *pAcc{nullptr};
  VARIANT vChild{};

  HRESULT hr{};

  hr = AccessibleObjectFromEvent(hWindow, objectId, childId, &pAcc, &vChild);

  if (FAILED(hr)) {
    return;
  }
  if (vChild.vt == VT_I4) {
    // todo
  }

  SafeRelease(&pAcc);
}

DWORD WINAPI winEventLoop(LPVOID context) {
  return 0;

  Log->Info(L"Start Windows event loop thread", GetCurrentThreadId(),
            __LONGFILE__);

  HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

  if (FAILED(hr)) {
    Log->Fail(L"Failed to call CoInitializeEx", GetCurrentThreadId(),
              __LONGFILE__);
    return hr;
  }

  winEventLoopCtx = static_cast<WinEventLoopContext *>(context);

  if (winEventLoopCtx == nullptr) {
    Log->Fail(L"Failed to obtain context", GetCurrentThreadId(), __LONGFILE__);
    return E_FAIL;
  }

  HWINEVENTHOOK hookIds[24];
  const DWORD events[24] = {EVENT_SYSTEM_DESKTOPSWITCH,
                            EVENT_SYSTEM_FOREGROUND,
                            EVENT_SYSTEM_ALERT,
                            EVENT_SYSTEM_MENUSTART,
                            EVENT_SYSTEM_MENUEND,
                            EVENT_SYSTEM_MENUPOPUPSTART,
                            EVENT_SYSTEM_MENUPOPUPEND,
                            EVENT_SYSTEM_SCROLLINGSTART,
                            EVENT_SYSTEM_SWITCHEND,
                            EVENT_OBJECT_FOCUS,
                            EVENT_OBJECT_SHOW,
                            EVENT_OBJECT_HIDE,
                            EVENT_OBJECT_DESTROY,
                            EVENT_OBJECT_DESCRIPTIONCHANGE,
                            EVENT_OBJECT_LOCATIONCHANGE,
                            EVENT_OBJECT_NAMECHANGE,
                            EVENT_OBJECT_REORDER,
                            EVENT_OBJECT_SELECTION,
                            EVENT_OBJECT_SELECTIONADD,
                            EVENT_OBJECT_SELECTIONREMOVE,
                            EVENT_OBJECT_SELECTIONWITHIN,
                            EVENT_OBJECT_STATECHANGE,
                            EVENT_OBJECT_VALUECHANGE,
                            EVENT_OBJECT_LIVEREGIONCHANGED};

  for (int i = 0; i < 24; i++) {
    hookIds[i] = SetWinEventHook(events[i], events[i], nullptr, eventCallback,
                                 0, 0, WINEVENT_OUTOFCONTEXT);

    if (hookIds[i] == 0) {
      Log->Warn(L"Failed to call SetWinEventHook()", GetCurrentThreadId(),
                __LONGFILE__);
    }
  }

  Log->Info(L"Register callbacks", GetCurrentThreadId(), __LONGFILE__);

  MSG msg;

  while (GetMessage(&msg, nullptr, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);

    if (winEventLoopCtx->IsActive) {
      break;
    }
  }
  for (int i = 0; i < 24; i++) {
    if (hookIds[i] == 0) {
      continue;
    }

    UnhookWinEvent(hookIds[i]);
  }

  CoUninitialize();

  Log->Info(L"Finish Windows event loop thread", GetCurrentThreadId(),
            __LONGFILE__);

  return S_OK;
}
