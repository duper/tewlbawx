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

static void usage(const char *restrict const a0) {
  fprintf(stderr, "usage: %s BASE10IP4\n", a0);
  fputs(" BASE10IP4  numeric IPv4 address encoded in decimal\n", stderr); 

  exit(EX_USAGE);
}

typedef struct sockaddr_in struct sockaddr_in4;

int main(int ac, char *av[], char *ev[]) {
  struct sockaddr_in4 in4 = { 0x00, };
  struct sockaddr_in6 in6 = { 0x00, };
  signed char ip4[INET_ADDRSTRLEN] = { '\0', }, ip6[INET6_ADDRSTRLEN] = { '\0', }, *end;


  if(ac < 2)
    usage(*av);

  const signed long int dec = strtol(av[1], &env, 0xA);
 
  if(!inet_ntop(PF_INET, &(sa.sin_addr), ia, sizeof ia))
    vexit("inet_ntop");

  puts(ia);

  exit(EXIT_SUCCESS);
}
