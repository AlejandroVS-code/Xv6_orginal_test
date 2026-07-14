#include "kernel/types.h"
#include "user/user.h"

void
busywait(int ticks)
{
  int start = uptime();
  while(uptime() - start < ticks);
}

int
main(void)
{
  printf("=== Scheduler Metrics Test (Original RR) ===\n\n");

  int pid_cpu = fork();
  if(pid_cpu == 0){
    int arrival = uptime();
    int first_run = uptime();
    printf("CPU-bound  pid=%d started\n", getpid());
    volatile long i = 0;
    for(i = 0; i < 500000000L; i++);
    int finish = uptime();
    printf("CPU-bound  pid=%d done\n", getpid());
    printf("  response_time  : %d ticks\n", first_run - arrival);
    printf("  turnaround     : %d ticks\n", finish - arrival);
    exit(0);
  }

  int pid_io = fork();
  if(pid_io == 0){
    int arrival = uptime();
    int first_run = uptime();
    printf("I/O-bound  pid=%d started\n", getpid());
    for(int j = 0; j < 5; j++){
      busywait(5);
      printf("I/O-bound  pid=%d woke up iter %d\n", getpid(), j);
    }
    int finish = uptime();
    printf("I/O-bound  pid=%d done\n", getpid());
    printf("  response_time  : %d ticks\n", first_run - arrival);
    printf("  turnaround     : %d ticks\n", finish - arrival);
    exit(0);
  }

  (void)pid_cpu;
  (void)pid_io;
  wait(0);
  wait(0);
  printf("\n=== Test Complete ===\n");
  exit(0);
}
