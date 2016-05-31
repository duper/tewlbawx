#include<stdio.h>
#include<stdlib.h>
#include<sysexits.h>
#include<arpa/inet.h>

_Noreturn static void usage(const char *restrict arg0) {
  fprintf(stdout, "\nusage: %s IP4DEC\n\n", arg0); /* TODO: switch usage with inet_ntoa.c */
  fprintf(stdout, " IP4DEC  Internet Protocol version four decimal address (host byte order)\n\n");
  fprintf(stdout, "ex. %s 16777343\n\n", arg0);

  exit(EX_USAGE);
}

int main(int argc, char *argv[]) {
  if(argc != 2)
    usage(*argv);

  fprintf(stdout, "%d\n", inet_addr(argv[1]));

  exit(EXIT_SUCCESS);
}
