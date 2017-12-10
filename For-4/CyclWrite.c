#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "Buffercheto.h"

int main()
{
	int memFd = shm_open("memory", O_CREAT | O_RDWR, S_IRWXU);
	if(memFd == -1)
	{
		perror("Sorry, unexpected open error");
		return 1;
	}

	int theres;
	theres = ftruncate(memFd, sizeof(struct cyclic_buffer));
	if(theres == -1)
	{
		perror("You have a truncate problem");
		return theres;
	}
	
	struct cyclic_buffer* mem = mmap(NULL, sizeof(struct cyclic_buffer), PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0);
	if(mem == NULL)
	{
		perror("Problem with mmap");
		return -1;
	}

	mem->pos %= 4096;
	int current = mem -> array[mem -> pos];
	while(true)
	{
		mem -> pos++;
		mem -> pos %= 4096;
		mem -> array[mem -> pos] = current;
		current++;
		if(mem->pos % 512 == 0)
		{
			sleep(1);
		}
	}	

	return 0;
}