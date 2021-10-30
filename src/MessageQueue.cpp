#include "MessageQueue.h"

// ----------------------------------------- MessageQueue -----------------------------------

MessageQueue::MessageQueue() {
  head = NULL;
}

void MessageQueue::append(MessageBuffer& msg) {
  if (head == NULL) {   // first element?
    head = &msg;
  } else {
    MessageBuffer *n = head;  // find LAST element
    while (n->next != NULL) {
      n = n->next;
    }
    n->next = &msg;
  }
  msg.next = NULL;  // this is now TAIL of queue, so has no next
}

MessageBuffer* MessageQueue::get() {
  MessageBuffer *n = head;
  if (n == NULL) return NULL;  // queue is empty

  head = n->next;
  n->next = NULL;

  return n;
}

MessageBuffer* MessageQueue::peek() {
  return head;
}

void MessageQueue::prepend(MessageBuffer& msg) {
  msg.next = head;
  head = &msg;
}

int MessageQueue::count() {
  int c = 0;
  MessageBuffer *n = head;
  while (n != NULL) {
    c++;
    n = n->next;
  }
  return c;
}

int MessageQueue::contains(MessageBuffer& msg) {
  MessageBuffer *next = head;
  while (next != NULL) {
    if (next == &msg) return 1;
    next = next->next;
  }
  return 0;
}