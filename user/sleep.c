#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(2, "Usage: sleep number\n");
	exit(1);
  }
  int var = 0;
  var = atoi(argv[1]);
  sleep(var);
  exit(0);
}
