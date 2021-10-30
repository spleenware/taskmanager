#include "AbsTask.h"

AbsTask::AbsTask() {  
  next_millis = 0;
}

int AbsTask::execute() {
  return 0;
}

const char* AbsTask::name() {
  return "";
}

void AbsTask::onSignal(TaskManager& mgr, int code) {
}

void AbsTask::onChildTaskFinshed(AbsTask& task) {
}