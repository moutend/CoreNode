#include <cpplogger/cpplogger.h>
#include <cstring>
#include <mutex>
#include <vector>
#include <windows.h>

#include <strsafe.h>

#include "api.h"
#include "context.h"
#include "logloop.h"
#include "msaa.h"
#include "types.h"
#include "uialoop.h"
#include "util.h"
#include "wineventloop.h"

extern Logger::Logger *Log;

static bool isActive{false};
static std::mutex apiMutex;

static LogLoopContext *logLoopCtx{};
static UIALoopContext *uiaLoopCtx{};
static WinEventLoopContext *winEventLoopCtx{};

static HANDLE logLoopThread{};
static HANDLE uiaLoopThread{};
static HANDLE winEventLoopThread{};

void __stdcall Setup(int32_t *code, int32_t logLevel,
                     EventHandler eventHandler) {
  std::lock_guard<std::mutex> lock(apiMutex);

  if (code == nullptr) {
    return;
  }
  if (isActive) {
    Log->Warn(L"Already initialized", GetCurrentThreadId(), __LONGFILE__);
    *code = -1;
    return;
  }

  Log = new Logger::Logger(L"CoreNode", L"v0.1.0-develop", 4096);

  Log->Info(L"Setup CoreNode", GetCurrentThreadId(), __LONGFILE__);

  logLoopCtx = new LogLoopContext();

  logLoopCtx->QuitEvent =
      CreateEventEx(nullptr, nullptr, 0, EVENT_MODIFY_STATE | SYNCHRONIZE);

  if (logLoopCtx->QuitEvent == nullptr) {
    Log->Fail(L"Failed to create event", GetCurrentThreadId(), __LONGFILE__);
    *code = -1;
    return;
  }

  Log->Info(L"Create log loop thread", GetCurrentThreadId(), __LONGFILE__);

  logLoopThread = CreateThread(nullptr, 0, logLoop,
                               static_cast<void *>(logLoopCtx), 0, nullptr);

  if (logLoopThread == nullptr) {
    Log->Fail(L"Failed to create thread", GetCurrentThreadId(), __LONGFILE__);
    *code = -1;
    return;
  }

  uiaLoopCtx = new UIALoopContext();

  uiaLoopCtx->HandleFunc = eventHandler;

  uiaLoopCtx->QuitEvent =
      CreateEventEx(nullptr, nullptr, 0, EVENT_MODIFY_STATE | SYNCHRONIZE);

  if (uiaLoopCtx->QuitEvent == nullptr) {
    Log->Fail(L"Failed to create event", GetCurrentThreadId(), __LONGFILE__);
    *code = -1;
    return;
  }

  Log->Info(L"Create uia loop thread", GetCurrentThreadId(), __LONGFILE__);

  uiaLoopThread = CreateThread(nullptr, 0, uiaLoop,
                               static_cast<void *>(uiaLoopCtx), 0, nullptr);

  if (uiaLoopThread == nullptr) {
    Log->Fail(L"Failed to create thread", GetCurrentThreadId(), __LONGFILE__);
    *code = -1;
    return;
  }

  Log->Info(L"Complete setup CoreNode", GetCurrentThreadId(), __LONGFILE__);

  winEventLoopCtx = new WinEventLoopContext();

  winEventLoopCtx->HandleFunc = eventHandler;

  winEventLoopCtx->QuitEvent =
      CreateEventEx(nullptr, nullptr, 0, EVENT_MODIFY_STATE | SYNCHRONIZE);

  if (winEventLoopCtx->QuitEvent == nullptr) {
    Log->Fail(L"Failed to create event", GetCurrentThreadId(), __LONGFILE__);
    *code = -1;
    return;
  }

  Log->Info(L"Create windows event loop thread", GetCurrentThreadId(),
            __LONGFILE__);

  winEventLoopThread =
      CreateThread(nullptr, 0, winEventLoop,
                   static_cast<void *>(winEventLoopCtx), 0, nullptr);

  if (winEventLoopThread == nullptr) {
    Log->Fail(L"Failed to create thread", GetCurrentThreadId(), __LONGFILE__);
    *code = -1;
    return;
  }

  Log->Info(L"Complete setup CoreNode", GetCurrentThreadId(), __LONGFILE__);

  isActive = true;
}

void __stdcall Teardown(int32_t *code) {
  std::lock_guard<std::mutex> lock(apiMutex);

  if (code == nullptr) {
    return;
  }
  if (!isActive) {
    *code = -1;
    return;
  }

  Log->Info(L"Teardown CoreNode", GetCurrentThreadId(), __LONGFILE__);

  if (uiaLoopThread == nullptr) {
    goto END_UIALOOP_CLEANUP;
  }
  if (!SetEvent(uiaLoopCtx->QuitEvent)) {
    Log->Fail(L"Failed to send event", GetCurrentThreadId(), __LONGFILE__);
    *code = -1;
    return;
  }

  WaitForSingleObject(uiaLoopThread, INFINITE);
  SafeCloseHandle(&uiaLoopThread);
  SafeCloseHandle(&(uiaLoopCtx->QuitEvent));

  delete uiaLoopCtx;
  uiaLoopCtx = nullptr;

  Log->Info(L"Delete uia loop thread", GetCurrentThreadId(), __LONGFILE__);

END_UIALOOP_CLEANUP:

  if (winEventLoopThread == nullptr) {
    goto END_WINEVENTLOOP_CLEANUP;
  }

  winEventLoopCtx->IsActive = false;

  WaitForSingleObject(winEventLoopThread, INFINITE);
  SafeCloseHandle(&winEventLoopThread);
  SafeCloseHandle(&(winEventLoopCtx->QuitEvent));

  delete winEventLoopCtx;
  winEventLoopCtx = nullptr;

  Log->Info(L"Delete windows event loop thread", GetCurrentThreadId(),
            __LONGFILE__);

END_WINEVENTLOOP_CLEANUP:

  Log->Info(L"Complete teardown CoreNode", GetCurrentThreadId(), __LONGFILE__);

  if (logLoopThread == nullptr) {
    goto END_LOGLOOP_CLEANUP;
  }
  if (!SetEvent(logLoopCtx->QuitEvent)) {
    Log->Fail(L"Failed to send event", GetCurrentThreadId(), __LONGFILE__);
    *code = -1;
    return;
  }

  WaitForSingleObject(logLoopThread, INFINITE);
  SafeCloseHandle(&logLoopThread);
  SafeCloseHandle(&(logLoopCtx->QuitEvent));

  delete logLoopCtx;
  logLoopCtx = nullptr;

END_LOGLOOP_CLEANUP:

  isActive = false;
}

void __stdcall BulkFetch(int32_t *code, BulkFetchHandler handleFunc) {
  std::lock_guard<std::mutex> lock(apiMutex);

  if (code == nullptr) {
    return;
  }

  Log->Info(L"Called BulkFetch", GetCurrentThreadId(), __LONGFILE__);

  std::vector<RawElement *> v;

  HRESULT hr = fetchAllElements(v);

  if (FAILED(hr)) {
    *code = -1;
    return;
  }

  wchar_t *buffer = new wchar_t[256]{};

  hr = StringCbPrintfW(buffer, 511, L"Found %d items", v.size());

  if (FAILED(hr)) {
    *code = -1;
    return;
  }

  Log->Info(buffer, GetCurrentThreadId(), __LONGFILE__);

  delete[] buffer;
  buffer = nullptr;

  RawElement **rawElements = new RawElement *[v.size()] {};
  int32_t rawElementsLen = v.size();

  for (int i = 0; i < v.size(); i++) {
    rawElements[i] = v[i];

    wchar_t *b = new wchar_t[256]{};

    StringCbPrintfW(b, 511, L"Name=%s\tLocation={%d,%d,%d,%d}",
                    rawElements[i]->NameData, rawElements[i]->Left,
                    rawElements[i]->Top, rawElements[i]->Width,
                    rawElements[i]->Height);
    Log->Info(b, GetCurrentThreadId(), __LONGFILE__);
    delete[] b;
    b = nullptr;
  }

  handleFunc(rawElements, rawElementsLen);

  for (int i = 0; i < v.size(); i++) {
    delete v[i];
    v[i] = nullptr;
    rawElements[i] = nullptr;
  }

  delete[] rawElements;
  rawElements = nullptr;

  return;
}
