#include "kernel/types.h"
#include "user/user.h"
#include "kernel/sysinfo.h"

int main(int argc, char *argv[]){
  if (argc != 1) {
	printf("correct input is : info *sysinfo\n");
	return -1;
  }
  struct sysinfo si;
  sysinfo((struct sysinfo *)&si);
  if (si.nproc == 0) {
	printf("sysinfo error\n");
	return -1;
  }
  printf("free memory: %d, free proc: %d\n", si.freemem, si.nproc);
  printf("sysinfotest:OK\n");
  return 0;
}
