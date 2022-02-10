#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char *args[] = { "sh", 0 };

void subdir(int n){                                      
 
  char c = '0' + n ;   
  char str[] = "man ";
  str[3] = c;  
      
  if(chdir(str)<0){

    if(mkdir(str) < 0){
      printf(2, "sub mkdir error\n");
      exit();    
    }

    if(chdir(str) < 0){
      printf(2, "chdir error\n");
      exit();
    }   

  }

  chdir("..");    

}

int main(void){

  if(chdir("manpages")<0){

    if(mkdir("manpages") < 0){
      printf(2, "mkdir error\n");
      exit();    
    }

    if(chdir("manpages") < 0){
      printf(2, "chdir error\n");
      exit();
    }

  }

  for(int i=1;i<9;i++){                           //generates the 8 subdirectories for the different sections
    subdir(i);
  }  
  
  if(chdir("..") < 0){
    printf(2, " chdir error\n");
    exit();
  }

  if (open("manpage", O_RDONLY)>0 ){              // at first boot moves man manual page from root to the correct section
    link("manpage", "/manpages/man1/man");
    unlink("manpage");
  }


  exec(args[0], args);                            //after building required directories executes shell

}
