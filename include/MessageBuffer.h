#pragma once

#include <Arduino.h>

class MessageQueue;

class MessageBuffer {
  friend class MessageQueue;

  public:
    MessageBuffer();
    void copyData(uint8_t *_buf, uint8_t _len, uint8_t other);

    MessageBuffer *next;
    uint8_t *buf;
    uint8_t len;
    uint8_t from_to;
    uint8_t flags;
    uint32_t extra;
};
