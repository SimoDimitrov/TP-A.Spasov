#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "Buffercheto.h"

int main()
{
	int memFd = shm_open( "memory", O_RDONLY, 0 );
	if( memFd == -1 )
	{
		perror("Sorry, unexpected open error");
		return 1;
	}

	struct buffera* mem = mmap( NULL, sizeof(struct buffera), PROT_READ, MAP_SHARED, memFd, 0 );
	if( mem == NULL )
	{
		perror("Problem with mmap");
		return -1;
	}	

	uint64_t pos = ( mem->pos + 2048 ) % 4096;
	printf("starts at %ld\n", pos);
	
	while(true)
	{
		if( mem->pos == pos )
		{
			sleep(1);
			continue;
		}
		
		printf("%d\n", mem->array[pos]);
		pos++;
		pos %= 4096;
	}
	
	return 0;
}
