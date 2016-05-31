#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include<sysexits.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

static void vexit(const char *fn) {
  perror(fn);

  exit(EXIT_FAILURE);
}

static void usage(const char *const a0) {
  fprintf(stderr, "usage: %s BASE10IP4\n", a0);
  fputs(" BASE10IP4  numeric IPv4 address encoded in decimal\n", stderr); 

  exit(EX_USAGE);
}

int main(int ac, char *av[], char *ev[]) {
  static struct sockaddr_in sa = { '\0' };
  char ia[INET_ADDRSTRLEN] = { 0 };

  if(ac < 2)
    usage(*av);

  sa.sin_addr.s_addr = atoi(av[1]);
 
  if(!inet_ntop(PF_INET, &(sa.sin_addr), ia, sizeof ia))
    vexit("inet_ntop");

  puts(ia);

  exit(EXIT_SUCCESS);
}
