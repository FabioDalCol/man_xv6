#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


void readinput(int fd, char *buf){                                   //takes input from console and writes it on the file when '&' is sent on a new line 
    int n = 0;
    
    while((n = read(0, buf, sizeof(buf)))>0){
        if(buf[0]=='&') {        
            write(fd,"\n",1); 
            break;
        }  

        write(fd,buf,n);   
    }
}

int main(int argc, char *argv[]){

    int fd;
    char sect[] = "man ";
    char path[255];
    char buf[512];
    char desc[100];
    strcpy(desc, "\n          MANPAGE for: ");

    if (argc != 3){
        printf(2,"Syntax error. Usage: manadd [pagename] [section number]\n");
        exit();
    }

    if (atoi(argv[2])<0||atoi(argv[2])>8){
        printf(2,"Section not valid\n");
        exit();
    }

    strcpy(path,"/manpages/");
    char c = '0' + atoi(argv[2]);
    sect[3] = c;
    strcat(path,sect);
    strcat(path,"/");
    strcat(path,argv[1]);

    if((fd = open(path, O_RDWR))>0){
        printf(2,"Manpage already exists. To change it delete first the old one.\n");
        exit();
    }

    if((fd = open(path, O_CREATE | O_RDWR))<0){
        printf(2,"Creation error.\n");
        exit();
    }

    strcat(desc,argv[1]);
    strcat(desc,"\n\n");

    printf(1,"Write part: NAME. When done send '&' on a new line\n");

    write(fd,desc,strlen(desc));
    write(fd,"NAME\n",5);

    readinput (fd,buf);

    printf(1,"Write part: SYNOPSIS. When done send '&' on a new line \n");
    write(fd,"SYNOPSIS\n",9);

    readinput (fd,buf);

    printf(1,"Write part: DESCRIPTION. When done send '&' on a new line \n");
    write(fd,"DESCRIPTION\n",12);

    readinput (fd,buf);

    printf(1,"Write part: OPTIONS. When done send '&' on a new line \n");
    write(fd,"OPTIONS\n",8);

    readinput (fd,buf);

    printf(1,"Write part: AUTHOR. When done send '&' on a new line \n");
    write(fd,"AUTHOR\n",7);

    readinput (fd,buf);

    printf(1,"Manpage successfully saved\n");

    close(fd);
    exit();

}