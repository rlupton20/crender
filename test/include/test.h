#pragma once
/* Macros to provide a basic test infrastructure */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(cond)                                                           \
  {                                                                            \
    if (!(cond)) {                                                             \
      printf("\x1b[31m\x1b[1mFAIL\x1b[0m \n  %s:%d assertion failed: %s\n",    \
             __FILE__,                                                         \
             __LINE__,                                                         \
             #cond);                                                           \
      return false;                                                            \
    }                                                                          \
  }

#define ASSERT_NOT(cond) ASSERT(!(cond))

#define RUN_TEST(test)                                                         \
  {                                                                            \
    printf("%-50s \t", #test);                                                 \
    _RUN_TEST((test));                                                         \
  }

void
_RUN_TEST(bool(test)(void));

void
summarise_results(void);
