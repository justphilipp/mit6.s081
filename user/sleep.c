// #include "kernel/sysproc.c"
#include "kernel/types.h"
// #include "kernel/stat.h"
// #include "kernel/defs.h"
// #include "user/ulib.c"
#include "user/user.h"

int 
main(int argc, char *argv[])
{
  if (argc != 2){
    fprintf(2, "Usage sleep times...\n");
    exit(1);
  }

  int time = atoi(argv[1]);
  sleep(time);
  
  /*
  while (time > 0) {
    sys_sleep();
    time--;
  }
  */
  exit(0);
  return 0;
}



