#pragma once

#include <cstdint>
#include <mutex>
#include <windows.h>

#include <UIAutomationClient.h>

class Element {
public:
  Element();
  Element(IUIAutomationElement *pElement);
  Element(Element *pElement);

  ~Element();

  wchar_t *GetName();
  wchar_t *GetClassName();
  wchar_t *GetFrameworkName();
  int32_t GetControlTypeId();
  int32_t GetRole();
  int32_t GetLeft();
  int32_t GetTop();
  int32_t GetWidth();
  int32_t GetHeight();

  bool IsEqual(Element *pElement);

private:
  wchar_t *mName = nullptr;
  wchar_t *mClassName = nullptr;
  wchar_t *mFrameworkName = nullptr;
  int32_t mControlTypeId = 0;
  int32_t mRole = 0;
  int32_t mLeft = 0;
  int32_t mTop = 0;
  int32_t mWidth = 0;
  int32_t mHeight = 0;
};
