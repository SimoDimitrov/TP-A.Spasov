#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	int fd = open("file", O_WRONLY);
	char* str = "Tova e neshto napisano tuk v tozi chas";
	
	write(fd, str, strlen(str));
	
	close(fd);
	
	return 0;
}
