// pingpong

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void redirect(int k, int pd[])
{
	close(k);
	dup(pd[k]);
	close(pd[0]);
	close(pd[1]);
}

void s(int p)
{
  int n;
  while (read(0, &n, sizeof(n)))
  {
    if((n % p) != 0) 
    {
      fprintf(2, "n: %d\n", n);
      write(1, &n, 4);
    }
  }
}

int gp()
{
  int p;
  if(read(0, &p, sizeof(p)) == 0) exit();
  printf("prime: %d\n", p);
  
  int pl[2];
  pipe(pl);
  
  if(fork() != 0) // parent
  {
    redirect(0, pl);
    gp();
  }
  else
  {
    redirect(1, pl);
    s(p);
  }
  
  exit();
}

int
main(int argc, char *argv[])
{   
  int pr[2];

  pipe(pr);
  
  int pid = fork();
  
  if(pid == 0){
    redirect(1, pr);
    for(int i = 2; i <= 35; i++)
    {
      write(1, &i, sizeof(i));
    }
    
    fprintf(2, "exited.\n");
    
  }else
  {
    redirect(0, pr);
    gp();
  }
  exit();
}