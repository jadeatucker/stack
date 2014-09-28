#include <errno.h>
#include <stdlib.h>
#include <string.h>

#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 512

typedef struct stack {
  size_t num_elems; // number of elements in the stack
  size_t size;      // total size of the stack in bytes
  char *top;        // pointer to the top of the stack
  char *bottom;     // pointer to the bottom of the stack
} Stack;

void init(Stack *s);

size_t push(Stack *s, const void *data, size_t n);

size_t pop(Stack *s, void *dest);

void destroy(Stack *s);

#endif
