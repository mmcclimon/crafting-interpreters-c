#include <stdio.h>

#include "memory.h"
#include "value.h"

void initValueArray(ValueArray *array) {
  array->capacity = 0;
  array->count = 0;
  array->values = NULL;
}

void freeValueArray(ValueArray *array) {
  FREE_ARRAY(Value, array->values, array->capacity);
  initValueArray(array);
}

void writeValueArray(ValueArray *array, Value value) {
  if (array->capacity < array->count + 1) {
    int oldcap = array->capacity;
    array->capacity = GROW_CAPACITY(oldcap);
    array->values = GROW_ARRAY(Value, array->values, oldcap, array->capacity);
  }

  array->values[array->count++] = value;
}

void printValue(Value value) {
  printf("%g", value);
}
