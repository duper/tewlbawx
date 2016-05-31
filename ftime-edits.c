/*                                                                       *
 * Change the creation, access and modification times of a certain file! *
 *                                                                       */

#include<stdbool.h>
#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<sysexits.h>
#include<unistd.h>
#include<utime.h>
#include<dirent.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/time.h>
#include<sys/stat.h>
#include<sys/param.h>
#include<sys/dirent.h>

#define NAMEABIN "edits-ftime"

static char *filename = ".";

static void hand_sig(const int signum) {
  register unsigned int flag = 0U;

  fputs("*-* Caught ", stderr);
  fflush(stderr);

  switch(signum) {
    case SIGTERM: 
      fputs("SIGTERM", stderr);

      break;
    case SIGPIPE:
      fputs("SIGPIPE", stderr);

      break;
    case SIGQUIT:
      fputs("SIGQUIT", stderr);

      break;
    case SIGINT:
      fputs("SIGINT", stderr);

      break;
    default:
      fputs("Unknown", stderr);

      flag++;
  }

  fputs(" signal!\n", stderr);

  if(flag) {
    flag--;

    return; 
  }

  exit(EX_OSERR); /* atexit() ? */
}

static void vexit(const char *const afunc, const char *afile, const size_t aline) {
  fprintf(stderr, "[%s:%u] ", afile, aline);
  fflush(stderr);

  perror(afunc);

  exit(EX_SOFTWARE);
}

/* comprehensive error-checking version of 4.4BSD's strdup function */

static signed int fe_errno = 0;

#define fe_return_errno(X); { fe_errno = X; return 0; }

static char *fe_strdup(const char *const astr) {
  register size_t alen = 0U;
  register signed char *aret = NULL, *adst = NULL;

  if(!(astr && *astr)) 
    fe_return_errno(EINVAL);

  alen = strlen(astr);

  if(alen > MAXPATHLEN) 
    fe_return_errno(ENAMETOOLONG);
 
  aret = malloc(++alen);

  if(!aret) {
    perror("malloc");

    fe_return_errno(ENOMEM);
  }

  adst = strcpy(aret, astr);

  if(adst != aret)
    fe_return_errno(EFAULT);

  if(strcmp(adst, astr) || strcmp(aret, astr))
    fe_return_errno(EBADMSG);

  return aret;
}

#define vexit(s) vexit(s, __FILE__, __LINE__)

static void usage(char *argv0) {
  const char *abin = NAMEABIN;

  if(!(argv0 && *argv0)) {
    argv0 = strdup(abin);

    if(!(abin && *abin) && argv0 && *argv0)
      perror("strdup");
  }
    
  fprintf(stderr, "usage: %s FILENAME [FILETIME]\n", *argv0);
  fputs("  FILENAME  -  fully qualified path of file to give new time values\n", stderr);
  fputs("  FILETIME  -  recognizable ASCII or numeric UNIX time string/integer\n", stderr);

  /* asctime_r() localtime_r() */

  exit(EX_USAGE);
}

static int do_time(const DIR *const adirp, const char *const apath, const time_t atime) {
  static struct stat st = { 0 };  
  static struct timespec times[3] = { { 0x0 }, { 0x0 }, { 0x0 } };
  static time_t timez[3] = { 0U, 0U, 0U };
  static long ltimez[3] = { 0L, 0L, 0L };
  signed int flags = '\x00';
  register int fd = dirfd(adirp);
  register unsigned long int k = 0UL, j = 0UL;

  if(!(adirp && apath && *apath) && ((fd = dirfd(adirp)) < 0))
    fe_return_errno(EBADF);

  if(utimensat(fd, apath, (const struct timespec*)times, &flags) < 0)
    fe_return_errno(EAGAIN);

  if(stat(apath, &st) < 0) {
    perror("stat");

    fe_return_errno(errno);
  } else {
#ifdef _NETBSD_SOURCE
    times[0], times[1], times[2] = st.st_atimespec, st.st_ctimespec, st.st_mtimespec;
#else
    timez[0], timez[1], timez[2] = st.st_atime, st.st_ctime, st.st_mtime;
    ltimez[0], ltimez[1], ltimez[3] = st.st_atimensec, st.st_ctimensec, st.st_mtimensec;
#endif
  }

#ifdef DEBUG 
  for(k = 0;k < 3;++k) 
#ifdef _NETBSD_SOURCE
    fprintf(stderr, "!!! times[k].tv_sec = %u, times[k].tv_nsec = %u\n", 
      k, times[k].tv_sec, k, times[k].tv_nsec);
#else
    fprintf(stderr, "!!! timez[k] = %u, ltimez[k] = %u\n",
      k, times[k], k, ltimez[k]);
#endif
#endif

  return fd;
}

int main(int argc, char *argv[], char *envp[]) {
  time_t atime = 0, rtime = 0;
  unsigned int seed[2] = { 0U, 0U };
  signed char resolvedname[2 + MAXPATHLEN] = { '\0' }, *apath = NULL;

  signal(SIGTERM, hand_sig);
  signal(SIGPIPE, hand_sig);
  signal(SIGQUIT, hand_sig);
  signal(SIGINT, hand_sig);

  switch(argc) {
    case 3:
      usage(*argv);

      break;
    case 2:
        apath = realpath(argv[1], resolvedname);

        if(!(resolvedname && *resolvedname))
          vexit("realpath");

        fprintf(stdout, "*+* Targeting full pathname: %s\n", resolvedname);
    case 1:
        if(time(&atime) == ((time_t)-1))
          vexit("time");
        
        srand(atime);

        /* rtime = rand_r(!(atime % 2) ? &seed[0] : &seed[1]); */

      break;
    default:
      usage(*argv);
  }

  do { 
    struct dirent *entry = NULL;
    signed int rddr_ret = '\x00';
    register DIR *dirp = opendir(filename);
    struct dirent *result;
   
    if(!dirp)
      vexit("opendir");

    entry = calloc(1, sizeof *entry);

    if(!entry)
      vexit("calloc");

    rddr_ret = readdir_r(dirp, entry, &result);

    if(!result) {
      fputs("*** End of directory reached!\n", stdout);

      break;
    } else if(rddr_ret)
      vexit("readdir_r");

    if(!strcmp(apath, entry->d_name)) {
#ifdef DEBUG    
      fprintf(stderr, "!!! entry[d_name]: [result][d_name]:\n", 
        entry->d_name, (*result)->d_name);
#endif

      if(!do_time(dirp, apath, atime)) {
        if(!errno)
          errno = fe_errno;

        perror("do_time");
      }
    }

    closedir(dirp);
  } while(true);

  exit(EXIT_SUCCESS);
}
