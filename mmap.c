// 2013-10-24
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


int main() {
	int fsize = 6 * sizeof(char);
	char *mymemorymap=NULL;
	int myfd = open("/tmp/kak", O_RDWR); 
	mymemorymap = mmap(NULL, fsize, PROT_READ | PROT_WRITE, MAP_SHARED, myfd, 0);

	if ( mymemorymap == MAP_FAILED )
		fprintf(stderr,"Something went wrongi\n");

//fprintf(stdout,"%s", mymemorymap[0]);
	if ( mymemorymap[0] == 'H' )
		fprintf(stdout,"It's an H\n");
	
	write(1, mymemorymap, fsize );
	fflush(stdout);
	//mymemorymap[1] = 'S';
//	strncpy(mymemorymap, "Ha", 2);
		char a;
		fgets(&a,2,stdin);
		mymemorymap[0] = a;
		write(1, mymemorymap, fsize);
	write(1, mymemorymap, fsize);
	munmap(mymemorymap, fsize);
	close(myfd);
	return 0;
}
