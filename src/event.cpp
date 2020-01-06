#include <mutex>

#include "event.h"

Event::Event(int32_t eventId, Element *pElement)
    : mEventId(eventId), mElement(pElement) {}

Event::~Event() {
  delete mElement;
  mElement = nullptr;
}

int32_t Event::GetEventId() { return mEventId; }
Element *Event::GetElement() { return mElement; }

EventQueue::EventQueue(int32_t maxEvents) : mMaxEvents(maxEvents) {
  mEvents = new Event *[maxEvents] {};
}

EventQueue::~EventQueue() {
  for (int32_t i = 0; i < mMaxEvents; i++) {
    if (mEvents[i] != nullptr) {
      delete mEvents[i];
      mEvents[i] = nullptr;
    }
  }

  delete[] mEvents;
  mEvents = nullptr;
}

void EventQueue::Set(Event *pEvent) {
  std::lock_guard<std::mutex> lock(mMutex);

  if (mEvents[mWriteIndex] != nullptr) {
    delete mEvents[mWriteIndex];
    mEvents[mWriteIndex] = nullptr;
  }

  mEvents[mWriteIndex] = pEvent;
  mWriteIndex = (mWriteIndex > mMaxEvents - 1) ? 0 : mWriteIndex + 1;
}

Event *EventQueue::Get() {
  std::lock_guard<std::mutex> lock(mMutex);

  return mEvents[mReadIndex];
}

void EventQueue::Next() {
  std::lock_guard<std::mutex> lock(mMutex);

  mReadIndex = (mReadIndex > mMaxEvents - 1) ? 0 : mReadIndex + 1;
}

EventFilter::EventFilter() {}

EventFilter::~EventFilter() {}

bool EventFilter::IsDup(Event *pEvent) {
  if (pEvent == nullptr || pEvent->GetElement() == nullptr) {
    return true;
  }

  bool cond{true};

  cond &= mEventId == pEvent->GetEventId();
  cond &= mControlTypeId == pEvent->GetElement()->GetControlTypeId();
  cond &= mRole == pEvent->GetElement()->GetRole();
  cond &= mLeft == pEvent->GetElement()->GetLeft();
  cond &= mTop == pEvent->GetElement()->GetTop();
  cond &= mWidth == pEvent->GetElement()->GetWidth();
  cond &= mHeight == pEvent->GetElement()->GetHeight();

  mEventId = pEvent->GetEventId();
  mControlTypeId = pEvent->GetElement()->GetControlTypeId();
  mRole = pEvent->GetElement()->GetRole();
  mLeft = pEvent->GetElement()->GetLeft();
  mTop = pEvent->GetElement()->GetTop();
  mWidth = pEvent->GetElement()->GetWidth();
  mHeight = pEvent->GetElement()->GetHeight();

  return cond;
}
