#include <cpplogger/cpplogger.h>
#include <cpprest/http_client.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "context.h"
#include "element.h"
#include "event.h"
#include "logloop.h"
#include "requestloop.h"
#include "util.h"

extern Logger::Logger *Log;

DWORD WINAPI requestLoop(LPVOID context) {
  Log->Info(L"Start request loop", GetCurrentThreadId(), __LONGFILE__);
  RequestLoopContext *ctx = static_cast<RequestLoopContext *>(context);

  if (ctx == nullptr) {
    return E_FAIL;
  }

  bool isActive{true};

  while (isActive) {
    HANDLE waitArray[1] = {ctx->QuitEvent};
    DWORD waitResult = WaitForMultipleObjects(1, waitArray, FALSE, INFINITE);

    if (waitResult == WAIT_OBJECT_0 + 0) {
      isActive = false;
      continue;
    }
  }

  Log->Info(L"End request loop", GetCurrentThreadId(), __LONGFILE__);

  return S_OK;
}
