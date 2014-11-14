// 2014-05-18
#include<errno.h>
#include<sys/ioctl.h>
#include<fcntl.h>
#include<linux/cdrom.h>
#include<stdio.h>
#include<string.h>


int main(int argc, char *argv[]){
    int cdrom;
    int command = CDROMSTART;

    if ( argc > 1 ) { 
        if ( strcmp(argv[1],"-t") == 0 ) {
            command = CDROMCLOSETRAY;
        }
    }


    cdrom = open("/dev/cdrom", O_RDONLY|O_NONBLOCK); 
    if ( cdrom == -1 ) { 
        perror("Oh noes"); 
        return 5;
    }
    if ( ioctl(cdrom, command, 0) == -1 ) { 
        perror("Oh noes"); 
        return 8;
    }
    close(cdrom);
    return 0;
}

