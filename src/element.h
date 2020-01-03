#pragma once

#include <cstdint>
#include <mutex>
#include <windows.h>

#include <UIAutomationClient.h>

class Element {
public:
  Element();
  ~Element();

  wchar_t *mName = nullptr;
  int32_t mControlTypeId = 0;
  int32_t mRole = 0;
  int32_t mTop = 0;
  int32_t mLeft = 0;
  int32_t mWidth = 0;
  int32_t mHeight = 0;
  int64_t mUnixSec = 0;
  int64_t mUnixNano = 0;

  bool IsEqual(Element *pElement);
  HRESULT CopyFromElement(Element *pElement);
  HRESULT CopyFromIUIAutomationElement(IUIAutomationElement *pElement);
};

class ElementSingleton {
public:
  ElementSingleton();
  ~ElementSingleton();

  HRESULT Get(Element *pElement);
  HRESULT Set(Element *pElement);
  bool IsSent();
  void Sent();

private:
  std::mutex mMutex;
  bool mSent = false;
  wchar_t *mLastElementName = nullptr;
  Element *mElement = nullptr;
};
