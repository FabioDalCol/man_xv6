// init: The initial user-level program

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


char *argv[] = { "manbuild", 0 };                     //init.c executes manbuild
void subdir(int n);

int main(void){

  int pid, wpid; 
      
  if(open("console", O_RDWR) < 0){
    mknod("console", 1, 1);
    open("console", O_RDWR);
  }

  dup(0);  // stdout
  dup(0);  // stderr  
 
  for(;;){
    printf(1, "init: starting manbuild\n");
    pid = fork();
    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
      exec(argv[0], argv);
      printf(1, "init: exec manbuild failed\n");
      exit();
    }
    while((wpid=wait()) >= 0 && wpid != pid)
      printf(1, "zombie!\n");
  }
}


