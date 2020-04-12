// sleep

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc <= 1){
    fprintf(2, "usage: sleep time ...\n");
    exit(1);
  }
  int t = atoi(argv[1]);
  int begin = uptime();
  if(t > 0)
  {
    sleep(t);
    printf("duration: %d\n", uptime()-begin);
  }
  else
    fprintf(2, "invalid input %s\n", argv[1]);
  exit(0);
}