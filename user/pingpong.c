// pingpong

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pipe1[2], pipe2[2];
  pipe(pipe1);
  pipe(pipe2); 
  
  int pid = fork();
  char buf[10] = {0};
  if(pid > 0){
    //pid = wait(0);
    read(pipe2[0], buf, 10);
    write(pipe1[1], "ping", 5);
    printf("%d: recieved %s\n", pid, buf);
    
    close(pipe1[0]); close(pipe1[1]);
    close(pipe2[0]); close(pipe2[1]);
  } else if(pid == 0){
    write(pipe2[1], "pong", 5);
    read(pipe1[0], buf, 10);
    printf("%d: recieved %s\n", pid, buf);
    
    close(pipe1[0]); close(pipe1[1]);
    close(pipe2[0]); close(pipe2[1]);
    exit(0);
  } else {
    printf("fork error\n");
  }
  
  exit(0);
}