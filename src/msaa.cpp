#include "msaa.h"

HRESULT fetchAllElements(std::vector<RawElement *> &v) {
  HWND hWindow = GetForegroundWindow();

  if (hWindow == nullptr) {
    return E_FAIL;
  }

  HRESULT hr{};
  IAccessible *pAcc{};

  hr = AccessibleObjectFromWindow(hWindow, OBJID_NATIVEOM, IID_IAccessible,
                                  &pAcc);

  if (FAILED(hr)) {
    return hr;
  }

  hr = walkIAccessible(pAcc, v);

  return hr;
}

HRESULT walkIAccessible(IAccessible *pAcc, int depth, int index,
                        std::vector<RawElement *> &v) {
  if (pAcc == nullptr) {
    return S_OK;
  }

  HRESULT hr{};
  RawElement *rawElement{};

  hr = RawElementFromIUIAutomationElement(pAcc, &rawElement);

  if (FAILED(hr)) {
    return hr
  }

  v.push_back(rawElement);

  long childCount{};

  hr = pAcc->get_accChildCount(&childCount);

  if (FAILED(hr)) {
    return hr;
  }
  if (childCount == 0) {
    return S_OK;
  }

  long returnCount{};
  VARIANT *pArray = new VARIANT[childCount];

  hr = AccessibleChildren(pAcc, 0, childCount, pArray, &returnCount);

  if (FAILED(hr)) {
    return hr;
  }
  for (int x = 0; x < returnCount; x++) {
    VARIANT vtChild = pArray[x];

    if (vtChild.vt != VT_DISPATCH) {
      continue;
    }

    IDispatch *pDisp = vtChild.pdispVal;
    IAccessible *pChild{};

    hr = pDisp->QueryInterface(IID_IAccessible,
                               reinterpret_cast<void **>(&pChild));

    if (SUCCEEDED(hr)) {
      walkIAccessible(pChild, depth + 1, x);
    }

    SafeRelease(&pDisp);
    SafeRelease(&pChild);
  }

  delete[] pArray;
  pArray = nullptr;

  return S_OK;
}
