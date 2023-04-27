#include <stdlib.h>

#include "chunk.h"
#include "memory.h"
#include "value.h"

static void initLines(Lines *lines) {
  lines->count = 0;
  lines->cap = 0;
  lines->lines = NULL;
}

void initChunk(Chunk *chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  initLines(&chunk->lines);
  initValueArray(&chunk->constants);
}

void freeChunk(Chunk *chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  FREE_ARRAY(Lines, chunk->lines.lines, chunk->lines.cap);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

// lines is a run-length encoded array like [line-num, max-offset, ...]
static void growLines(Lines *ll) {
  int oldcap = ll->cap;
  ll->cap = GROW_CAPACITY(oldcap);
  ll->lines = GROW_ARRAY(int, ll->lines, oldcap, ll->cap);
}

static void addLine(Lines *ll, int line, int offset) {
  if (ll->cap == 0)
    growLines(ll);

  int maxLine = ll->lines[ll->count - 2];

  // we already have the line we care about; just increase the max offet of
  // the last byte
  if (line == maxLine) {
    ll->lines[ll->count - 1] = offset;
    return;
  }

  if (ll->cap < ll->count + 2)
    growLines(ll);

  ll->lines[ll->count++] = line;
  ll->lines[ll->count++] = offset;
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int oldcap = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldcap);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldcap, chunk->capacity);
  }

  chunk->code[chunk->count] = byte;
  addLine(&chunk->lines, line, chunk->count);
  chunk->count++;
}

int addConstant(Chunk *chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}

int getLine(Chunk *chunk, int offset) {
  Lines ll = chunk->lines;

  for (int i = 1; i < ll.count; i += 2) {
    if (ll.lines[i] >= offset)
      return ll.lines[i - 1];
  }

  return -1;
}
