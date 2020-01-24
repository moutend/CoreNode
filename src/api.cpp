#include <cpplogger/cpplogger.h>
#include <cstring>
#include <mutex>
#include <windows.h>

#include <strsafe.h>

#include "api.h"
#include "context.h"
#include "logloop.h"
#include "types.h"
#include "uialoop.h"
#include "util.h"

extern Logger::Logger *Log;

bool isActive{false};
std::mutex apiMutex;

LogLoopContext *logLoopCtx{nullptr};
UIALoopContext *uiaLoopCtx{nullptr};

HANDLE logLoopThread{nullptr};
HANDLE uiaLoopThread{nullptr};

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

  if (!SetEvent(uiaLoopCtx->QuitEvent)) {
    Log->Fail(L"Failed to send event", GetCurrentThreadId(), __LONGFILE__);
    *code = -1;
    return;
  }

  WaitForSingleObject(uiaLoopThread, INFINITE);
  SafeCloseHandle(&uiaLoopThread);

  delete uiaLoopCtx;
  uiaLoopCtx = nullptr;

  Log->Info(L"Delete uia loop thread", GetCurrentThreadId(), __LONGFILE__);

  Log->Info(L"Complete teardown CoreNode", GetCurrentThreadId(), __LONGFILE__);

  if (!SetEvent(logLoopCtx->QuitEvent)) {
    Log->Fail(L"Failed to send event", GetCurrentThreadId(), __LONGFILE__);
    *code = -1;
    return;
  }

  WaitForSingleObject(logLoopThread, INFINITE);
  SafeCloseHandle(&logLoopThread);

  delete logLoopCtx;
  logLoopCtx = nullptr;

  isActive = false;
}
