#include<stdarg.h>
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include<sysexits.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

_Noreturn static void vexit(const char *const f) {
  perror(f);

  exit(EX_OSERR);
}

_Noreturn static void usage(const char *arg0) { 
  fprintf(stderr, "\nusage: %s BASE10IP [-b]\n", arg0);
  fputs("  IPV4ADDR  numeric IPv4 address styled as dotted quad octets\n", stderr);
  fputs("  -b        change socket endian-ness (host-to-network vs. network-to-host)\n", stderr);
  fprintf(stderr, "ex. %s 2090631340\n\n", arg0);

  exit(EX_USAGE);
}

signed int main(int argc, char *argv[], char *envp[]) {
	register const char *p = NULL;
  struct sockaddr_in addr = { 0x0, };

  if(argc < 2)
    usage(*argv);

  memset(&addr, '\0', sizeof addr);

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = atoi(argv[1]);

  if(argc >= 3) 
    addr.sin_addr.s_addr = ntohl(addr.sin_addr.s_addr);

  p = inet_ntoa(addr.sin_addr);

  if(!p)
    vexit("inet_ntoa");

  puts(p);
  
  exit(EXIT_SUCCESS);
} 
