#pragma once

#include <cstdint>
#include <mutex>

#include "element.h"

class Event {
public:
  Event(int32_t eventId, Element *pElement);
  ~Event();

  int32_t GetEventId();
  Element *GetElement();

private:
  int32_t mEventId = 0;
  Element *mElement = nullptr;
};

class EventQueue {
public:
  EventQueue(int32_t maxEvents);
  ~EventQueue();

  void Set(Event *event);
  Event *Get();
  void Next();

private:
  std::mutex mMutex;

  int32_t mMaxEvents = 0;
  int32_t mReadIndex = 0;
  int32_t mWriteIndex = 0;

  Event **mEvents = nullptr;
};

class EventFilter {
public:
  EventFilter();
  ~EventFilter();

  bool IsDup(Event *pEvent);

private:
  int32_t mEventId = 0;
  int32_t mControlTypeId = 0;
  int32_t mRole = 0;
  int32_t mLeft = 0;
  int32_t mTop = 0;
  int32_t mWidth = 0;
  int32_t mHeight = 0;
};

class EventHandler {
public:
  EventHandler();
  ~EventHandler();

  void Handle(Event *pEvent);

private:
  std::mutex mMutex;
  int32_t mEventCount = 0;
};
