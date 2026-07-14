#include "kernel/types.h"
#include "user/user.h"

// Busy-wait for approximately 'ticks' timer ticks
void
wait_ticks(int ticks)
{
  int start = uptime();
  while(uptime() - start < ticks);
}

int
main(void)
{
  int pid;
  int start, end;

  printf("=== Scheduler Behavior Test ===\n\n");

  // Test 1: proceso I/O-bound solo
  printf("[Test 1] I/O-bound solo\n");
  start = uptime();
  pid = fork();
  if(pid == 0){
    for(int i = 0; i < 5; i++){
      wait_ticks(2);
      printf("  I/O-bound iter %d at tick %d\n", i, uptime());
    }
    exit(0);
  }
  wait(0);
  end = uptime();
  printf("  Total ticks: %d\n\n", end - start);

  // Test 2: proceso CPU-bound solo
  printf("[Test 2] CPU-bound solo\n");
  start = uptime();
  pid = fork();
  if(pid == 0){
    volatile long i = 0;
    for(i = 0; i < 100000000L; i++);
    printf("  CPU-bound done at tick %d\n", uptime());
    exit(0);
  }
  wait(0);
  end = uptime();
  printf("  Total ticks: %d\n\n", end - start);

  // Test 3: ambos compitiendo
  printf("[Test 3] I/O-bound vs CPU-bound compitiendo\n");
  start = uptime();

  int pid_io = fork();
  if(pid_io == 0){
    int io_start = uptime();
    for(int i = 0; i < 5; i++){
      wait_ticks(2);
      printf("  I/O-bound iter %d at tick %d\n", i, uptime());
    }
    printf("  I/O-bound total ticks: %d\n", uptime() - io_start);
    exit(0);
  }

  int pid_cpu = fork();
  if(pid_cpu == 0){
    int cpu_start = uptime();
    volatile long i = 0;
    for(i = 0; i < 100000000L; i++);
    printf("  CPU-bound total ticks: %d\n", uptime() - cpu_start);
    exit(0);
  }

  wait(0);
  wait(0);
  end = uptime();
  printf("  Total ticks competing: %d\n", end - start);

  printf("\n=== Test Complete ===\n");
  exit(0);
}
