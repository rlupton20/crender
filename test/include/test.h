#pragma once
/* Macros to provide a basic test infrastructure */
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

atomic_uintmax_t failed = 0;
atomic_uintmax_t passed = 0;

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
    if ((test)() == true) {                                                    \
      printf("\x1b[32m\x1b[1mPASS\x1b[0m\n");                                  \
      ++passed; \
    } else {                                                                   \
      ++failed;                                                                \
    }                                                                          \
  }

void
summarise_results(void)
{
  printf("\n\nSummary\n=======\n\n");
  printf("Passed: %zu\nFailed: %zu\n\n", passed, failed);
  if (failed) {
    exit(1);
  } else {
    printf("Success!\n\n");
  }
}
