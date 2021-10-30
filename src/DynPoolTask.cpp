#include "DynPoolTask.h"
#include "TaskManager.h"

DynPoolTask::DynPoolTask() {
  parent = NULL;
}

void DynPoolTask::onSignal(TaskManager& mgr, int code) {
  if (code < 0) {
    if (parent != NULL) {
      parent->onChildTaskFinshed(*this);
      parent = NULL;   // reset for next re-use
    }
    mgr.addToPool(*this);   // put Task back in dynamic pool
  }
}
