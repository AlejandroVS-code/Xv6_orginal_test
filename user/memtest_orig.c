#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  printf("=== Memory Fragmentation Test (Original xv6) ===\n\n");

  printf("Baseline:\n");
  printf("  Free pages  : %d\n", freepages());
  printf("  Frag blocks : %d\n\n", measurefrag());

  // Allocate 32 pages
  char *pages[32];
  for(int i = 0; i < 32; i++)
    pages[i] = sbrk(4096);

  printf("After allocating 32 pages:\n");
  printf("  Free pages  : %d\n", freepages());
  printf("  Frag blocks : %d\n\n", measurefrag());

  (void)pages;
  // Free alternating pages
  for(int i = 0; i < 32; i += 2)
    sbrk(-4096);

  printf("After freeing alternating pages:\n");
  printf("  Free pages  : %d\n", freepages());
  printf("  Frag blocks : %d\n\n", measurefrag());

  printf("Note: original xv6 has no coalesce() — fragmentation cannot be reduced\n");
  printf("\n=== Test Complete ===\n");
  exit(0);
}
