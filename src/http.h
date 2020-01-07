#pragma once

#include <cpprest/http_client.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;

pplx::task<void> notifySync();
pplx::task<void> notifyAsync();
