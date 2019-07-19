#include <stdatomic.h>

#include <test.h>

static atomic_uintmax_t failed = 0;
static atomic_uintmax_t passed = 0;

void
_RUN_TEST(bool (*test)(void))
{
  if ((test)() == true) {
    printf("\x1b[32m\x1b[1mPASS\x1b[0m\n");
    ++passed;
  } else {
    ++failed;
  }
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
