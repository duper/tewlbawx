#define _DEFAULT_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<utime.h>
#include<limits.h>
#include<sysexits.h>
#include<sys/param.h>
#include<sys/stat.h>
#include<sys/time.h>
#include<errno.h>

static void vexit(const char *__restrict fn) {
  perror(fn);

  exit(EXIT_FAILURE);
}

static void usage(const char *const a0) {
  fprintf(stderr, "usage: %s FILE\n", a0);

  if(errno)
    perror("getopt");

  exit(EX_USAGE);
}

int main(int argc, char *argv[], char *envp[]) {
  register time_t t = time(NULL);
  struct stat sb = { 0x0, };
  char resolvedname[MAXPATHLEN] = { 00 };
  const struct utimbuf *timp = NULL;

  if(argc <= 1)
    usage(*argv);

  const char *p = realpath(argv[1], resolvedname);

  srand(t); 

  if(utime(resolvedname, timp)<0)
    vexit("utime");

  stat(p, &sb);

  printf("dev: %u ino: %u mode: %o nlink: %u uid: %u gid: %u rdev: %u\n", \
    sb.st_dev, sb.st_ino, sb.st_mode, sb.st_nlink, sb.st_uid, sb.st_gid, sb.st_rdev);

  exit(EXIT_SUCCESS);
}
