#include <stdio.h>
#include "stack.h"

int main(void) {
  size_t n;

  // create a new stack and initialize it
  Stack s;
  init(&s);

  // These dont have to be strings.
  // The stack is type agnostic and will store anything within size limits.
  char *str1 = "Hello";
  char *str2 = "World";
  char *a = malloc(32);

  // push some strings
  push(&s, str1, strlen(str1)+1);
  push(&s, str2, strlen(str2)+1);

  // pop all the elements off and print them
  while(s.num_elems > 0) {
    n = pop(&s, a);
    printf("Pop: n: %lu, %s\n", n, a);
  }

  destroy(&s);

  return 0;
}
