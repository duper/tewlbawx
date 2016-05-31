#include<stdio.h>
#include<stdlib.h>
#include<sysexits.h>
#include<wordexp.h>

static void usage(const char *const a0) {
  fprintf(stderr, "\nusage: %s EXPSTR\n", a0);
  fprintf(stderr, " EXPSTR  shell expansion string\n\n");

  exit(EX_USAGE);
}

signed int main(signed int ac, const char **av) {
  wordexp_t p = { 0x0, };
  char **w;
  register signed int i;

  if(ac < 2) 
    usage(*av);

  i = wordexp(av[1], &p, 0);

  switch(i) {
    case WRDE_BADCHAR:
      break;
    case WRDE_BADVAL:
      break;
    case WRDE_CMDSUB:
      break;
    case WRDE_NOSPACE:
      break;
    case WRDE_SYNTAX:
      break;
    default:
      break;
    case 0:
      break;
  }

  w = p.we_wordv;

  while(i < p.we_wordc)
    puts(w[i++]);

  wordfree(&p);

  exit(EXIT_SUCCESS);
}
