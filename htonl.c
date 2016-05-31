#include<stdio.h>
#include<stdlib.h>
#include<sysexits.h>
#include<arpa/inet.h>

_Noreturn static void usage(const char *restrict arg0) {
  fprintf(stdout, "\nusage\033[39m:\033[m \033[30;47m%s LONG\033[m\n", arg0); 
  fprintf(stdout, " \033[36mLONG  unsigned long integer\033[m\n\n");
  fprintf(stdout, "ex. \033[33;44m%s 80\033[m\n\n", arg0);

  exit(EX_USAGE);
}

int main(int argc, char *argv[]) {
  unsigned long int l = 0;

  if(argc != 2)
    usage(*argv);

  l = atoi(argv[1]);

  printf("%u\n", htonl(l));

  exit(EXIT_SUCCESS);
}

