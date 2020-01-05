#include <cpplogger/cpplogger.h>
#include <cpprest/http_client.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "context.h"
#include "element.h"
#include "logloop.h"
#include "util.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;

extern Logger::Logger *Log;

pplx::task<http_response> notifyTargetChange(Element *pElement) {
  json::value c;

  c[U("type")] = json::value(3);
  c[U("value")] = json::value(pElement->mName);

  json::value postData;

  postData[U("commands")][0] = c;

  // Log->Info(postData.serialize().c_str(), GetCurrentThreadId(),
  // __LONGFILE__);

  http_client client(U("http://localhost:7902/v1/audio/command"));

  return client.request(methods::POST, U(""), postData.serialize(),
                        U("application/json"));
}

pplx::task<http_response> notifyWindowChange(Element *pElement) {
  json::value c0;
  c0[U("type")] = json::value(1);
  c0[U("value")] = json::value(5);

  json::value c1;
  c1[U("type")] = json::value(3);
  c1[U("value")] = json::value(pElement->mName);

  json::value postData;

  postData[U("commands")][0] = c0;
  postData[U("commands")][1] = c1;

  /*
    Log->Info(postData.serialize().c_str(), GetCurrentThreadId(), __LONGFILE__);
    */
  http_client client(U("http://localhost:7902/v1/audio/command?force=true"));

  return client.request(methods::POST, U(""), postData.serialize(),
                        U("application/json"));
}

DWORD WINAPI requestLoop(LPVOID context) {
  Log->Info(L"Start request loop", GetCurrentThreadId(), __LONGFILE__);
  RequestLoopContext *ctx = static_cast<RequestLoopContext *>(context);

  if (ctx == nullptr) {
    return E_FAIL;
  }

  HRESULT hr{};
  Element *pElement = new Element();
  bool isActive{true};

  while (isActive) {
    HANDLE waitArray[3] = {ctx->QuitEvent, ctx->TargetEvent, ctx->WindowEvent};
    DWORD waitResult = WaitForMultipleObjects(3, waitArray, FALSE, INFINITE);

    if (waitResult == WAIT_OBJECT_0 + 0) {
      isActive = false;
      continue;
    }
    switch (waitResult) {
    case WAIT_OBJECT_0 + 1: // ctx->TargetEvent
      if (ctx->TargetElement->IsSent()) {
        Log->Info(L"Already sent target element", GetCurrentThreadId(),
                  __LONGFILE__);
        continue;
      }

      hr = ctx->TargetElement->Get(pElement);

      if (FAILED(hr)) {
        Log->Warn(L"Failed to get target element", GetCurrentThreadId(),
                  __LONGFILE__);
        continue;
      }
      try {
        notifyTargetChange(pElement).wait();
      } catch (...) {
        Log->Warn(L"Failed to send HTTP request", GetCurrentThreadId(),
                  __LONGFILE__);
        continue;
      }

      ctx->TargetElement->Sent();

      break;
    case WAIT_OBJECT_0 + 2: // ctx->WindowEvent
      hr = ctx->WindowElement->Get(pElement);

      if (FAILED(hr)) {
        Log->Warn(L"Failed to get window element", GetCurrentThreadId(),
                  __LONGFILE__);
        continue;
      }
      try {
        notifyWindowChange(pElement).wait();
        Log->Info(pElement->mName, GetCurrentThread(), __LONGFILE__);
      } catch (...) {
        Log->Warn(L"Failed to send HTTP request", GetCurrentThreadId(),
                  __LONGFILE__);
        continue;
      }

      break;
    }
  }

  Log->Info(L"End request loop", GetCurrentThreadId(), __LONGFILE__);

  return S_OK;
}
