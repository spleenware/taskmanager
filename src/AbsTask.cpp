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

// Utility function -- handles the case where millis() wraps around back to zero
//   2's complement arithmetic will handle any unsigned subtraction up to HALF the word size (32-bits in this case)
bool millisHasNowPassed(unsigned long timestamp) {
  return (long)(millis() - timestamp) > 0;
}
