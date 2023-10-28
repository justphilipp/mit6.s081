#include "kernel/param.h"
#include "kernel/types.h"
#include "user/user.h"


void xargs(int ac, char *av[]) {
  int res = fork();
  if (res == 0) {
	exec(av[1], av + 1);
	exit(0);
  }
  
  wait((void *)0);
  // CANNOT exit here! return and process next lines!
  // exit(0);
  return;
}


int main(int argc, char *argv[]){
  char *paras[MAXARG];
  paras[argc + 1] = 0;
  int i;
  for (i = 0; i < argc; i++) {
	paras[i] = argv[i];
  }
  char buf[512];
  while (1) {
	gets(buf, 512);
	int len = strlen(buf);
	if (strlen(buf) == 0) {
	  break;
	}
	// clear '\n'
	buf[len - 1] = '\0';
	paras[argc] = buf;
	// printf("%d : %s0.o\n", strlen(buf), buf);
	xargs(argc + 1, paras);
  }
  return 0;

  /* handle every byte
  while (1) {
	char buf[512], ch;
	int index = 0;
	ch = (char)gets();
	if (ch == EOF) {
	  paras[i] = buf;
	  xargs(argc + 1, paras);
	  exit(0);
	}
	while (1) {
	  ch = (char)getchar();
	  if (ch == '\n') {
		paras[i] = buf;
		xargs(argc + 1, paras);
		buf[0] = '\0';
		index = 0;
		break;
	  }
	  buf[index++] = ch;
	}
  }
  */
}

