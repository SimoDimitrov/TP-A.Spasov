#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "cyclicBuf.h"
#include "gen.h"
#include "gen.c"

int main()
{
	int memFd = shm_open("simple_memory", O_CREAT | O_RDWR, S_IRWXU);
	if( memFd == -1 )
	{
		perror("Opening file problem");
		return 1;
	}

	int res = ftruncate(memFd, sizeof(struct buffer));
	if(res == -1)
	{
		perror("Truncate problem");
		return res;
	}
	
	struct buffer* memory = mmap(NULL, sizeof(struct buffer), PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0);
	if( memory == NULL )
	{
		perror("mmap problem, so bad");
		return -1;
	}
	
    	memory->position = 0;
    	uint32_t seed = 0;
		
    	while(1)
	{
		
			generate((void*)memory->array[memory->position %= COUNT], seed);
			printf("Generate: array[%ld] - seed: %d\n", memory->position %= COUNT,seed);
			memory->position++;
			seed++;
    	}

	return 0;
}
