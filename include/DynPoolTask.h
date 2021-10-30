#pragma once

#include <Arduino.h>
#include "AbsTask.h"

class TaskManager;

class DynPoolTask : public AbsTask {
  friend class TaskManager;

  protected:
    AbsTask* parent;
  public:
    DynPoolTask();

    virtual void onSignal(TaskManager& mgr, int code);
};

