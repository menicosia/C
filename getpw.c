#include <stdio.h>
#include <pwd.h>

main(int argc, char **argv) {
  struct passwd *user ;

  if (argc != 2) exit (1) ;
  printf("%s\t%s\n", argv[0], argv[1]) ;
  user = getpwnam(argv[1]) ;
  printf("%s\t%s\n", user->pw_name, user->pw_passwd) ;
}

