#include <test.h>

bool
test_scale_normalised_coord();

int
main(int argc, char* argvp[])
{
  printf("\nStarting tests\n\n");

  RUN_TEST(test_scale_normalised_coord);

  summarise_results();
  return 0;
}
