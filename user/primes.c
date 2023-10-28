#include "kernel/types.h"
#include "user/user.h"


void
RunProcess(int listenfd)
{	
  int forked = 0;
  int num = 0;
  int read_num;
  int pipes[2];

  while (1) {
    int read_bytes = read(listenfd, &read_num, 4);

    if (read_bytes == 0) {
      close(listenfd);
      if (forked) {
	close(pipes[1]);
	int child_pid;
	wait(&child_pid);
      }
      exit(0);
    }

    if (num == 0) {
      num = read_num;
      printf("prime %d\n", num);
    }

    if (read_num % num != 0) {
      if (!forked) {
	forked = 1;
	pipe(pipes);
	int res = fork();
	if (res == 0) {
	  close(listenfd);
	  close(pipes[1]);
	  RunProcess(pipes[0]);
	} else {
	  close(pipes[0]);
	}

      }
      write(pipes[1], &read_num, 4);
    }
  }
}


int
main(int argc, char *argv[])
{
  int fd[2];
  pipe(fd);
  for (int i = 2; i <= 35; i++) {
    write(fd[1], &i, 4);
  }
  close(fd[1]);  
  RunProcess(fd[0]);
  exit(0);
}


  

