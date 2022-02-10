#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


void readpage(int fd){

  uint size;
  struct stat st;
  char *text;

  fstat(fd, &st);                                   // gets file size to dimension buffer
  size = st.size;
  text = (char *) malloc(size);    
  
  if (read(fd, text, size) < 0){
    printf(2,"Read error \n");
    exit();
  }

  printf(1,text); 
  close(fd);
  free(text);
  exit();
}

int main(int argc, char *argv[]){

  int fd;  
  char sect[] = "man ";
  char path[255];   

  if (argc < 2) {
	  printf(2, "Usage: man [pagename]\n\nusing man [section number] [pagename] you can retrieve a page from a specific section\n\nfor further information use man man\n");
	  exit();
  }
  
  if (argc == 2){

    for (int i=1; i<=8;i++){
      
      strcpy(path,"/manpages/");
      char c = '0' + i;
      sect[3] = c;
      strcat(path,sect);
      strcat(path,"/");
      strcat(path,argv[1]);
          
      if ((fd = open(path, O_RDONLY)) > 0){            //As soon it finds the page exits the cycle and read it
        break;
      }

     if (i==8){
       printf(2,"This man page does not exist\n");
       exit();
     }
            
    }

    readpage(fd);    

  }

  if (argc == 3){

    if (strcmp(argv[1],"-f") == 0){

      int count = 0;

      for (int i=1; i<=9;i++){

        strcpy(path,"/manpages/");
        char c = '0' + i;
        sect[3] = c;
        strcat(path,sect);
        strcat(path,"/");
        strcat(path,argv[2]);

        if (i==9 && count==0){
          printf(2,"This man page does not exist\n");
          exit();
        }

        if ((fd = open(path, O_RDONLY)) > 0){                      // every time it finds the page it prints pagename and section number
          printf(1,argv[2]);
          printf(1,"  (%d)\n",i);
          count++;                                           
        }        
      }
      exit();    
    }

    if (strcmp(argv[1],"-w") == 0){

      int count = 0;

      for (int i=1; i<=9;i++){

        strcpy(path,"/manpages/");
        char c = '0' + i;
        sect[3] = c;
        strcat(path,sect);
        strcat(path,"/");
        strcat(path,argv[2]);

        if (i==9 && count==0){
          printf(2,"This man page does not exist\n");
          exit();
        }

        if ((fd = open(path, O_RDONLY)) > 0){                      // every time it finds the page it prints it's location
          printf(1,"%s\n",path);
          count++;                                           
        }        
      }
      exit();    
    }

    if (atoi(argv[1])<=8 && atoi(argv[1])>0 && strlen(argv[1])==1){             // checks if it's a valid section number
      
      strcpy(path,"/manpages/");
      char c = '0' + atoi(argv[1]);
      sect[3] = c;
      strcat(path,sect);
      strcat(path,"/");
      strcat(path,argv[2]);
                 
      if ((fd = open(path, O_RDONLY)) < 0){            
        printf(2,"This section does not contain the required page\n");
        exit();
      }
      
      readpage(fd);
    }

    else {
      printf(2,"Section not valid\n");
      exit();
    }

  }

  else{
    printf(2,"Syntax error: to see instruction type man man\n");
    exit();
  }

}



