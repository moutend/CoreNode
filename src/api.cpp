#include <cpplogger/cpplogger.h>
#include <cstring>
#include <fstream>
#include <mutex>
#include <windows.h>

#include <strsafe.h>

#include "api.h"
#include "context.h"
#include "logloop.h"
#include "requestloop.h"
#include "uialoop.h"
#include "util.h"

extern Logger::Logger *Log;

bool isActive{false};
std::mutex apiMutex;

LogLoopContext *logLoopCtx{nullptr};
UIALoopContext *uiaLoopCtx{nullptr};
RequestLoopContext *requestLoopCtx{nullptr};

HANDLE logLoopThread{nullptr};
HANDLE uiaLoopThread{nullptr};
HANDLE requestLoopThread{nullptr};

void __stdcall Setup(int32_t *code, int32_t logLevel) {
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

  requestLoopCtx = new RequestLoopContext();

  requestLoopCtx->QuitEvent =
      CreateEventEx(nullptr, nullptr, 0, EVENT_MODIFY_STATE | SYNCHRONIZE);

  if (requestLoopCtx->QuitEvent == nullptr) {
    Log->Fail(L"Failed to create event", GetCurrentThreadId(), __LONGFILE__);
    *code = -1;
    return;
  }

  Log->Info(L"Create request loop thread", GetCurrentThreadId(), __LONGFILE__);

  requestLoopThread = CreateThread(
      nullptr, 0, requestLoop, static_cast<void *>(requestLoopCtx), 0, nullptr);

  if (requestLoopThread == nullptr) {
    Log->Fail(L"Failed to create thread", GetCurrentThreadId(), __LONGFILE__);
    *code = -1;
    return;
  }

  uiaLoopCtx = new UIALoopContext();

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

  Log->Info(L"Delete uia loop thread", GetCurrentThreadId(), __LONGFILE__);

  if (!SetEvent(requestLoopCtx->QuitEvent)) {
    Log->Fail(L"Failed to send event", GetCurrentThreadId(), __LONGFILE__);
    *code = -1;
    return;
  }

  WaitForSingleObject(requestLoopThread, INFINITE);
  SafeCloseHandle(&requestLoopThread);

  Log->Info(L"Delete request loop thread", GetCurrentThreadId(), __LONGFILE__);

  SafeCloseHandle(&notifyEvent);

  delete uiaLoopCtx;
  uiaLoopCtx = nullptr;

  delete requestLoopCtx;
  requestLoopCtx = nullptr;

  Log->Info(L"Complete teardown CoreNode", GetCurrentThreadId(), __LONGFILE__);

  if (!SetEvent(logLoopCtx->QuitEvent)) {
    Log->Fail(L"Failed to send event", GetCurrentThreadId(), __LONGFILE__);
    *code = -1;
    return;
  }

  WaitForSingleObject(logLoopThread, INFINITE);
  SafeCloseHandle(&logLoopThread);

  isActive = false;
}
