#pragma once

#include <Arduino.h>

class TaskManager;

class AbsTask {
  friend class TaskManager;

    #define TASK_DONE  -1
  public:
    AbsTask();

    // returns -1 if task should be removed, otherwise the delay in millis until next execution
    virtual int execute();
    virtual const char* name();
    virtual void onSignal(TaskManager& mgr, int code);
    virtual void onChildTaskFinshed(AbsTask& task);

  private:
    unsigned long next_millis;
};

extern bool millisHasNowPassed(unsigned long timestamp);
