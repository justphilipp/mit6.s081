#include "kernel/types.h"
#include "user/user.h"

void filter(int listenfd) {
  int forked = 0;
  int curr_num;
  int num = 0;
  int fd[2];
	  
  while (1) {
	int read_bytes = read(listenfd, &curr_num, 4);
	if (read_bytes == 0) {
		close(fd[1]);
		int child_pid;
		wait(&child_pid);
		exit(0);
	}

    if (num == 0) {
	  num = curr_num;
      printf("prime %d\n", curr_num);
	  continue;
    }

  	if (curr_num % num != 0) {
	  if (!forked) {
	    pipe(fd);
	    int pid = fork();
	    if (pid == 0) {
		  close(fd[1]);
		  close(listenfd);
		  // printf("prime %d\n", curr_num);
		  filter(fd[0]);
		  exit(0);
	    } else {
	      forked = 1;
		  close(fd[0]);
		}
	  }
	  write(fd[1], &curr_num, 4);
	}
  }
}


int main(int argc, char *argv[]){
  if (argc != 1){
	printf("wrong use of prime\n");
	exit(-1);
  }
  int fd[2];
  pipe(fd);
  for (int i = 2; i < 36; i++) {
	write(fd[1], &i, 4);
  }
  close(fd[1]);
  filter(fd[0]);
  exit(0);
}
