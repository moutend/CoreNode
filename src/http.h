#pragma once

#include <cpprest/http_client.h>

#include "element.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;

pplx::task<void> notifySync(Element *pElement);
pplx::task<void> notifyAsync(Element *pElement);
