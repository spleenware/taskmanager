#include "stdlib.h"
#include "TaskManager.h"

TaskManager::TaskManager() {
  num = 0;
  next = 0;
  logStream = NULL;

  int i;
  for (i = 0; i < MAX_TASKS; i++) { tasks[i] = NULL; }
}

void TaskManager::start(AbsTask& task) {
  if (num >= MAX_TASKS || tasks[num] != NULL) {
    // LOG ERROR
    return;
  }
  tasks[num++] = &task;
}

void TaskManager::startChild(DynPoolTask& task, AbsTask* parent) {
  task.parent = parent;
  start(task);
}

void TaskManager::startDelayed(AbsTask& task, int delayMillis) {
    task.next_millis = millis() + delayMillis;
    start(task);
}

void TaskManager::logTo(Stream& stream) {
  logStream = &stream;
}

void TaskManager::quickSort(AbsTask* arr[], int left, int right) {
     int i = left, j = right;
     AbsTask* tmp;
     unsigned long pivot = arr[(left + right) / 2]->next_millis;

     /* partition */
     while (i <= j) {
           while (arr[i]->next_millis < pivot)
                 i++;
           while (arr[j]->next_millis > pivot)
                 j--;
           if (i <= j) {
                 tmp = arr[i];
                 arr[i] = arr[j];
                 arr[j] = tmp;
                 i++;
                 j--;
           }
     };

     /* recursion */
     if (left < j)
           quickSort(arr, left, j);
     if (i < right)
           quickSort(arr, i, right);
}

void TaskManager::signal(int code) {
  for (int i = 0; i < num; i++) {
    AbsTask* t = tasks[i];
    t->onSignal(*this, code);
  }
}

void TaskManager::loop() {
  if (next >= num) {
    next = 0;  // cycle back to start

    // sort by next_millis
    if (num > 1) quickSort(tasks, 0, num - 1);

    if (num > 0) {
      long diff = tasks[0]->next_millis - millis();
      if (diff > 0) {
        if (logStream) {
          logStream->print("sleeping for ");
          logStream->print(diff);
          logStream->println(" millis");
        }
        delay(diff);
      }
    }
  }
 
  if (next < num) {
    AbsTask* t = tasks[next];
    if (millis() < t->next_millis) {
      // not enough delay time has passed
      next++;
    } else {
      unsigned long start = millis();
      if (logStream) {
        logStream->print("Executing task: ");
        logStream->print(t->name());
      }

      int delayMillis = t->execute();

      if (logStream) {
        logStream->print(" (");
        logStream->print(millis() - start);
        logStream->println(" millis)");
      }

      if (delayMillis < 0) {
        remove(next);
        t->onSignal(*this, -1);
      } else {
        t->next_millis = millis() + delayMillis;
        next++;
      }
    }
  }
}

boolean TaskManager::contains(AbsTask& task) {
  int i = 0;
  while (i < num) {
    if (tasks[i] == &task) { 
      return true;
    }
    i++;
  }
  return false;
}

boolean TaskManager::containsName(const char* name) {
  int i = 0;
  while (i < num) {
    if (strcmp(tasks[i]->name(), name) == 0) { 
      return true;
    }
    i++;
  }
  return false;
}

void TaskManager::remove(int index) {
  if (index >= num) {
    // LOG FATAL ERROR
    return;
  }
  while (index < num - 1) {
    tasks[index] = tasks[index + 1];
    index++;
  }
  num--;
  tasks[num] = NULL;   // make last slot available again
}

DynPoolTask* TaskManager::getFromPool(const char* name) {
  int i = MAX_TASKS;  // search starting up from bottom
  while (i > num) {
    i--;
    if (tasks[i]->name() == name) {
      AbsTask* t = tasks[i];
      tasks[i] = NULL;  // free up this slot
      return (DynPoolTask*) t;
    }
  }
  // LOG FATAL ERROR
  return NULL;  // Not found!
}

void TaskManager::addToPool(DynPoolTask& task) {
  int i = MAX_TASKS;  // add starting up from bottom
  while (i > num) {
    i--;
    if (tasks[i] == NULL) break;
  }

  if (i == num) {
    // LOG FATAL ERROR
    return;
  }
  tasks[i] = &task;
}
