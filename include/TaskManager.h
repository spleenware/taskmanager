
#pragma once

#include <Arduino.h>
#include "AbsTask.h"
#include "DynPoolTask.h"

#define MAX_TASKS 16

class TaskManager {
  public:
    TaskManager();
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

    void quickSort(AbsTask* arr[], int left, int right);
    void remove(int index);
};

