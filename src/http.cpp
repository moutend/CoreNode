#include <cpprest/http_client.h>
#include "http.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;

pplx::task<http_response> notifyAsync(Element *pElement) {
  json::value c;

  c[U("type")] = json::value(3);
  c[U("value")] = json::value(pElement->GetName());

  json::value postData;

  postData[U("commands")][0] = c;

  // Log->Info(postData.serialize().c_str(), GetCurrentThreadId(),
  // __LONGFILE__);

  http_client client(U("http://localhost:7902/v1/audio/command"));

  return client.request(methods::POST, U(""), postData.serialize(),
                        U("application/json"));
}

pplx::task<http_response> notifySync(Element *pElement) {
  json::value c0;
  c0[U("type")] = json::value(1);
  c0[U("value")] = json::value(7);

  json::value c1;
  c1[U("type")] = json::value(3);
  c1[U("value")] = json::value(pElement->GetName());

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
