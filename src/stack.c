#include "stack.h"

void init(Stack *s) {
  s->num_elems = s->size = 0;
  s->bottom = s->top = NULL;
}

// push n bytes of data onto Stack s
// returns number of bytes copied
size_t push(Stack *s, const void *data, size_t n) {
  if(n < 1)
    return 0;

  // limit the size of individual elements
  if(n + sizeof(size_t) > STACK_SIZE)
    return -E2BIG;

  // stack buffer hasnt been allocated
  if(s->bottom == NULL) {
    s->bottom = s->top = malloc(STACK_SIZE);
    if(s->bottom == NULL)
      return -ENOMEM;
    s->size = STACK_SIZE;
  }

  // stack buffer doesn't have enough space,
  // create a new buffer twice as large
  if(n + sizeof(size_t) > s->size - (s->top - s->bottom)) {
    char *tmp = NULL;
    size_t stack_size = s->size * 2; // new stack size is twice as large.
    size_t len = s->top - s->bottom; // length of data in stack buffer

    // allocate the new buffer
    tmp = malloc(stack_size);
    if(tmp == NULL)
      return -ENOMEM;

    // copy the stack to the new buffer
    // and free original buffer
    memcpy(tmp, s->bottom, s->size);
    free(s->bottom);

    // set stack pointers to the new buffer
    s->bottom = tmp;
    s->top = s->bottom + len;
    s->size = stack_size;
  }

  // copy data to the stack buffer
  memcpy(s->top, data, n);
  s->top += n;

  // store the length of the data (n) on the top of the stack
  memcpy(s->top, &n, sizeof(size_t));
  s->top += sizeof(size_t);

  s->num_elems++;
  return n;
}

// pop top element off of Stack s into dest
// returns number of bytes copied
size_t pop(Stack *s, void *dest) {
  size_t n;

  // nothing in stack
  if(s->num_elems < 1)
    return -1;

  // copy the length of the top element into n
  s->top -= sizeof(size_t);
  memcpy(&n, s->top, sizeof(size_t));

  // copy element into dest
  s->top -= n;
  memcpy(dest, s->top, n);

  s->num_elems--;
  return n;
}

void destroy(Stack *s) {
  free(s->bottom);
}
