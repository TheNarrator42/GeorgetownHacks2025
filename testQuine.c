#include <stdio.h>

// This is a template program that is meant to be passed to cQuine.py to make a quine. This program will not compile on its own.

int main() {
  printf("Hello world\n");

  const char *quineString = QUINE_STRING;
  printf(QUINE_PRINTF_ARGS);

  printf("Goodbye world\n");

  return 0;
}
