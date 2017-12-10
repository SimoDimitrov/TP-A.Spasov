#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	int fd = open("file", O_RDONLY);
	char a;
	
	while(read(fd, &a, 1))
	write(STDOUT_FILENO, &a, 1);
	write(STDOUT_FILENO, "\n", 1);
	
	close(fd);
	
	return 0;
}
