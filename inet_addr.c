#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sysexits.h>
#include<stdnoreturn.h>
#include<stdbool.h>

static noreturn void usage(const char *const a0) {
  if(isatty(STDERR_FILENO) && getenv("LS_COLORS")) {
    fprintf(stderr, "\033[36musage\033[m\033[38m:\033[m \033[44m\033[39m%s\033[m \033[32m[-n] [-u] [-x] [-?]\033[m \033[44m\033[39mIPV4ADDR\033[m\r\n", a0); 
    /* fprintf(stderr, " \033[32m-h\033[m, \033[33m--ntohl\033[m \033[48mnetwork to host long\033[m\r\n"); */
    fprintf(stderr, " \033[32m-a\033[m, \033[48mcalculate all supported representations\033[m\r\n"); 
    fprintf(stderr, " \033[32m-h\033[m, \033[48mconvert value to host byte order\033[m\r\n"); 
    fprintf(stderr, " \033[32m-u\033[m, \033[48mmake decimal (base10) value unsigned (non-negative)\033[m\r\n"); 
    fprintf(stderr, " \033[32m-v\033[m, \033[48mincrease output verbosity\033[m\r\n"); 
    fprintf(stderr, " \033[32m-x\033[m, \033[48mshow result as hexadecimal (base16)\033[m\r\n"); 
    fprintf(stderr, " \033[32m-?\033[m, \033[48mdisplay usage info currently being shown\033[m\r\n"); 
    fprintf(stderr, " \033[44m\033[39mIPV4ADDR\033[m  \033[48mdotted-quad string of numeric IPv4 address\033[m\r\n");
    fprintf(stderr, " \033[35mexample: %s -av 127.0.0.1\033[m\r\n", a0);
    /* fprintf(stderr," \033[35mnote: typedef uint32_t in_addr_t;\r\n"); */
  } else {
    fprintf(stderr, "usage: %s [-a] [-n] [-u] [-x] [-?] IPV4ADDR\r\n", a0);
    fprintf(stderr, " -a, calculate all supported representations\r\n");
    fprintf(stderr, " -h, convert value to host byte order\r\n");
    fprintf(stderr, " -u, make decimal (base10) value unsigned (non-negative)\r\n"); 
    fprintf(stderr, " -v, increase output verbosity\r\n");
    fprintf(stderr, " -x, show result as hexadecimal (base16)\r\n"); 
    fprintf(stderr, " -?, display usage info currently being shown\r\n");
    fprintf(stderr, " IPV4ADDR  dotted-quad string of numeric IPv4 address\r\n");
    fprintf(stderr, "example: %s -av 127.0.0.1\033[m\r\n", a0);
    /* fprintf(stderr,"  note: typedef uint32_t in_addr_t;\r\n"); */
  }

  exit(EX_USAGE);
}

int main(int argc, char *argv[], char *envp[]) {
  bool aflag = false, hflag = false, uflag = false, vflag = false, xflag = false;
  in_addr_t adeci = INADDR_ANY;
  register signed int opt = 0x0;

  if(argc < 2)
    usage(*argv);

  while((opt = getopt(argc, argv, "ahuvx?")) != -1) {
    switch(opt) {
      case 'a':
        aflag = true;

        break;
      case 'h':
        hflag = true;

        break;
      case 'u':
        uflag = true;

        break;
      case 'v':
        vflag = true;

        break;
      case 'x':
        xflag = true;

        break;
      default:
      case '?':
        usage(*argv);
    }
  }

  if(optind >= argc)
    usage(*argv);

  adeci = inet_addr(argv[optind]);

  /* if errno is zero, then INADDR_NONE is actually INADDR_BROADCAST */
  if(errno && adeci == INADDR_NONE) {
    perror("inet_addr");

    exit(EX_IOERR);
  }

  if(aflag) {
    printf(vflag ? "network byte order signed: %d\n" : "%d\n", adeci);
    printf(vflag ? "network byte order unsigned: %u\n" : "%u\n", adeci);
    printf(vflag ? "network byte order hexadecimal: %x\n" : "%x\n", adeci);

    adeci = ntohl(adeci);

    printf(vflag ? "host byte order signed: %d\n" : "%d\n", adeci);
    printf(vflag ? "host byte order unsigned: %u\n" : "%u\n", adeci);
    printf(vflag ? "host byte order hexadecimal: %x\n" : "%x\n", adeci);
  } else {
    if(hflag) {
      if(vflag)
        fputs("host byte order ", stdout);

      adeci = ntohl(adeci);
    }
    

    if(xflag)
      printf(vflag ? "hexadecimal: %x\n" : "%x\n", adeci);
    else if(uflag)
      printf(vflag ? "unsigned: %u\n" : "%u\n", adeci);
    else
      printf(vflag ? "signed: %d\n" : "%d\n", adeci);
  } 

  exit(EXIT_SUCCESS);
}
