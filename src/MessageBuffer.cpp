#include "MessageBuffer.h"

// ----------------------------------------- MessageBuffer -----------------------------------

MessageBuffer::MessageBuffer() {
  len = 0;
  next = NULL;
  extra = 0;
}

void MessageBuffer::copyData(uint8_t *src, uint8_t _len, uint8_t other) {
  memcpy(buf, src, _len);
  len = _len;
  from_to = other;
}
