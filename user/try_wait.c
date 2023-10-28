#include "kernel/types.h"
#include "user/user.h"


int
main(int argc, char *argv[])
{
   int pid;
   pid = getpid();
   printf("parent process: %d\n", pid); 
   pid = fork();
   if (pid == 0) {
     pid = getpid();
     printf("child process: %d\n", pid);
     exit(0);
   } else {
     int sync = pid;
     pid = 0;
     pid = wait(&sync);
     printf("parent wait : %d\n", pid);
   }
   exit(0);
   return 0;
}
