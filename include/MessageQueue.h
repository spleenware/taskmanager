#pragma once

#include <Arduino.h>
#include "MessageBuffer.h"

class MessageQueue {
  public:
    MessageQueue();
    void append(MessageBuffer& msg);
    MessageBuffer* get();
    MessageBuffer* peek();
    void prepend(MessageBuffer& msg);
    int count();
    int contains(MessageBuffer& msg);

  private:
    MessageBuffer *head;
};
