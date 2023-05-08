#ifndef clox_object_h
#define clox_object_h

#include "chunk.h"
#include "common.h"
#include "value.h"

typedef enum {
  OBJ_FUNCTION,
  OBJ_STRING,
} ObjType;

struct Obj {
  ObjType type;
  struct Obj *next;
};

struct ObjString {
  Obj obj;
  int length;
  uint32_t hash;
  char chars[];
};

typedef struct {
  Obj obj;
  int arity;
  Chunk chunk;
  ObjString *name;
} ObjFunction;

#define OBJ_TYPE(value) (AS_OBJ(value)->type)

#define IS_FUNCTION(value) isObjType(value, OBJ_FUNCTION)
#define IS_STRING(value) isObjType(value, OBJ_STRING)

#define AS_FUNCTION(value) ((ObjFunction *)AS_OBJ(value))
#define AS_STRING(value) ((ObjString *)AS_OBJ(value))
#define AS_CSTRING(value) (((ObjString *)AS_OBJ(value))->chars)

static inline bool isObjType(Value value, ObjType type) {
  return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

ObjFunction *newFunction(void);
ObjString *copyString(const char *chars, int length);
ObjString *takeString(char *chars, int length);
void printObject(Value value);
uint32_t hash;

#endif
