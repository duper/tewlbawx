#include<stdio.h>
#include<stdlib.h>
#include<sysexits.h>
#include<time.h>

static void usage(const char *arg0) {
  fprintf(stdout, "usage: %s UNXTM\n", arg0);
  fprintf(stdout, " UNXTM  Unix 32-bit time stamp in seconds since Epoch (1 Jan 1970)\n\n");
  fprintf(stdout, "ex. %s 1463501690\n\n", arg0);

  exit(EX_USAGE);
}

int main(int argc, char *argv[]) {
    if(argc != 2)
      usage(*argv);

    time_t t = atoi(argv[1]);

    fputs(ctime(&t), stdout);

    exit(EXIT_SUCCESS);
}
