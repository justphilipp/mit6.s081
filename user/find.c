#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


void
find(char *path, char *pattern)
{
  int fd;
  struct dirent de;
  struct stat st;


  if((fd = open(path, 0)) < 0){
	fprintf(2, "find : cannot open %s\n", path);
	exit(-1);
  }

  // find out the reason
  if (fstat(fd, &st) < 0){
	fprintf(2, "find : cannot stat %s\n", path);
	close(fd);
	exit(-1);
  }

  switch(st.type){
  case T_DEVICE:
  case T_FILE:
  {
  	char *compare;
	char *p;
	for (p = path + strlen(path); p >= path && *p != '/'; p--);
	p++;
	compare = p;
  	if(strcmp(compare, pattern) == 0){
	  printf("%s\n", path);
	}
	close(fd);
	break;
  }
  case T_DIR:
  {
	char buf[512];
	char *p;
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)){
	  printf("find : path too long\n");
	  close(fd);
	  break;
	}
	strcpy(buf, path);
	p = buf + strlen(buf);
	*p++ = '/';
	while (read(fd, &de, sizeof(de)) == sizeof(de)) {
	  if (de.inum == 0) {
		continue;
	  }
	  if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) {
		continue;
	  }
	  memmove(p, de.name, DIRSIZ);
	  p[DIRSIZ] = 0;
	  find(buf, pattern);
	  
	}
	close(fd);
  }
  }
}



	
int
main(int argc, char *argv[])
{
  if(argc != 3){
    fprintf(2, "usage find <path> cmp\n");
    exit(-1);
  }
  find(argv[1], argv[2]);
  exit(0);
}
