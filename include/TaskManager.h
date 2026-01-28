
#pragma once

#include <Arduino.h>
#include "AbsTask.h"
#include "DynPoolTask.h"

#define MAX_TASKS 16

class TaskManager {
  public:
    TaskManager();
    void setCustomSleepCallback(void (*sleep_fn)(unsigned long ms)) { custom_sleep = sleep_fn; }
    void start(AbsTask& task);
    void startDelayed(AbsTask& task, int delayMillis);
    boolean contains(AbsTask& task);
    boolean containsName(const char* name);
    void addToPool(DynPoolTask& task);
    DynPoolTask* getFromPool(const char* name);
    void startChild(DynPoolTask& task, AbsTask* parent);

    void logTo(Stream& stream);
    void loop();
    void signal(int code);

  private:
    AbsTask* tasks[MAX_TASKS];
    int num, next;
    Stream* logStream;
    void (*custom_sleep)(unsigned long ms);

    void quickSort(AbsTask* arr[], int left, int right);
    void remove(int index);
};

