#include<stdio.h>
#include<stdlib.h>
#include<sysexits.h>
#include<arpa/inet.h>

_Noreturn static void usage(const char *restrict arg0) {
  printf("\n%s LONG\n LONG  unsigned long integer\n\nex. %s 80\n\n", arg0, arg0);

  exit(EX_USAGE);
}

int main(int argc, char *argv[]) {
  unsigned long l = 0;

  if(argc != 2)
    usage(*argv);

  l = atoi(argv[1]);

  printf("%u\n", ntohl(l));

  exit(EXIT_SUCCESS);
}

