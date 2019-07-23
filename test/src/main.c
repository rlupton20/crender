#include <test.h>

bool
test_projective_cube_to_screen();

int
main(int argc, char* argvp[])
{
  printf("\nStarting tests\n\n");

  RUN_TEST(test_projective_cube_to_screen);

  summarise_results();
  return 0;
}
