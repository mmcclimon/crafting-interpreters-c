#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "value.h"
#include "vm.h"

#define ALLOCATE_OBJ(type, objectType)                                         \
  (type *)allocateObject(sizeof(type), objectType)

static Obj *allocateObject(size_t size, ObjType type) {
  Obj *object = (Obj *)reallocate(NULL, 0, size);
  object->type = type;

  object->next = vm.objects;
  vm.objects = object;

  return object;
}

static ObjString *allocateString(const char *chars, int length) {
  // We need to allocate enough memory for our variable length array here.
  ObjString *string = (ObjString *)allocateObject(
      sizeof(ObjString) + 1 + sizeof(char) * length, OBJ_STRING);

  memcpy(string->chars, chars, length);
  string->chars[length] = '\0';
  string->length = length;

  return string;
}

ObjString *copyString(const char *chars, int length) {
  return allocateString(chars, length);
}

ObjString *takeString(char *chars, int length) {
  return allocateString(chars, length);
}

void printObject(Value value) {
  switch (OBJ_TYPE(value)) {
  case OBJ_STRING:
    printf("%s", AS_CSTRING(value));
    break;
  }
}
