#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define STACK_SIZE 512

struct stack {
  size_t num_elems;
  size_t size;
  char *end;
  char *data;
};
typedef struct stack Stack;

void init(Stack *s) {
  s->num_elems = s->size = 0;
  s->data = s->end = NULL;
}

size_t push(Stack *s, const void *data, size_t n) {
  if(n < 1)
    return 0;
  if(n + sizeof(size_t) > STACK_SIZE)
    return -E2BIG;

  if(s->data == NULL) {
    s->data = s->end = malloc(STACK_SIZE);
    if(s->data == NULL)
      return -ENOMEM;
    s->size = STACK_SIZE;
  }

  if(n + sizeof(size_t) > s->size - (s->end - s->data)) {
    char *tmp = NULL;
    size_t stack_size = s->size * 2;
    size_t len = s->end - s->data;

    tmp = malloc(stack_size);
    if(tmp == NULL)
      return -ENOMEM;

    memcpy(tmp, s->data, s->size);
    free(s->data);

    s->data = tmp;
    s->end = s->data + len;
    s->size = stack_size;
  }

  memcpy(s->end, data, n);
  s->end += n;

  memcpy(s->end, &n, sizeof(size_t));
  s->end += sizeof(size_t);

  s->num_elems++;
  return n;
}

size_t pop(Stack *s, void *dest) {
  size_t n;

  if(s->num_elems < 1)
    return -1;

  s->end -= sizeof(size_t);
  memcpy(&n, s->end, sizeof(size_t));
  n = (size_t) *s->end;

  s->end -= n;
  memcpy(dest, s->end, n);

  s->num_elems--;
  return n;
}

int main(void) {
  size_t n;
  Stack s;
  init(&s);

  char *str1 = "Hello";
  char *str2 = "World";
  char *a = malloc(6);

  push(&s, str1, strlen(str1)+1);
  push(&s, str2, strlen(str2)+1);

  while(s.num_elems > 0) {
    n = pop(&s, a);
    printf("Pop: n: %lu, %s\n", n, a);
  }

  return 0;
}
