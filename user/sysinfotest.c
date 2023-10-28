#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
  if (argc != 2) {
	printf("correct input is : info *sysinfo\n");
	return -1;
  }
  struct sysinfo *si;
  si = (struct sysinfo *)argv[1];
  sysinfo(si);
  return 0;
}
