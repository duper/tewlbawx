#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sysexits.h>
#include<err.h>

static char *my_strdup(const char *s) {
  register size_t alen = 0;
  register char *aret = NULL;

  if(!s)
    return aret;

  if(!*s) {
    aret = malloc(1);
    
    if(!aret)
      err(EX_OSERR, NULL);

    *aret = '\0';

    return aret;
  }

  alen = strlen(s);
  aret = malloc(++alen);

  if(!aret)
    err(EX_OSERR, NULL);

  strcpy(aret, s);

  return aret;
}

char **split_dir(char *adir) {
  register char *aptr = strchr(adir, '/');
  static char *ptrs[BUFSIZ];
  register size_t slash_cnt = 0, loop_ctr = 0;

  ptrs[0] = adir + 1;

  if(aptr)
    do {
      *aptr = '\0';
      ptrs[++slash_cnt] = aptr + 1;
      aptr = strchr(ptrs[slash_cnt], '/');
    } while(aptr && *aptr);

 ptrs[++slash_cnt] = NULL;

 char **sdir = malloc(slash_cnt * sizeof*sdir);

 if(!sdir)
  err(EX_OSERR, NULL);

 for(loop_ctr = 0;loop_ctr < slash_cnt;++loop_ctr) {
   sdir[loop_ctr] = my_strdup(ptrs[loop_ctr]);

   if(!sdir[loop_ctr])
     err(EX_OSERR, NULL);

   if(loop_ctr)
     *ptrs[loop_ctr] = '/';
 }

 sdir[loop_ctr] = NULL; 

 return ++sdir;
}

size_t slash_count(char *dname) {
  register size_t r = 0;
  register char *p = dname;

  if(p)
    do 
      if(*p == '/')
        r++;
    while(*++p);

  return r;
}

char **unique_dirs(char **dstrs) {
  register char *restrict *restrict pp = dstrs, *restrict *restrict words = NULL, *restrict *restrict pw = NULL;
  register size_t dir_cnt = 0;
  
  if(pp)
    do {
      dir_cnt += slash_count(*pp);
      words = split_dir(*pp);
      
      for(pw = words;*pw;++pw)
        if(**pw)
          puts(*pw);
    } while(*++pp);

#ifdef DEBUG
  fprintf(stderr, "*?* dir_cnt: %u\n", dir_cnt);
#endif

  return dstrs;
}

int main(int argc, char *argv[]) {
  register char **sptr = unique_dirs(&argv[1]);

  for(;sptr && *sptr;++sptr)
    printf("-%s-\n", *sptr);

  exit(EXIT_SUCCESS);
}
