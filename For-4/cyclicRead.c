#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "gen.h"
#include "gen.c"
#include "cyclicBuf.h"


int main()
{
	int memFd = shm_open("memory", O_RDONLY, 0);
	if(memFd == -1)
	{
		perror("Can't open this file");
		return 1;
	}

	struct buffer* memory = mmap( NULL, sizeof(struct buffer), PROT_READ, MAP_SHARED, memFd, 0 );
	if(memory == NULL)
	{
		perror("Problem with mmap");
		return 1;
	}
    
    uint64_t position = memory->position;
    uint64_t seed;
    uint64_t genuineseed;
	
	printf("starting at %ld\n", position);
    int i=0;

    while(1)
	{
       		 while(memory -> position != position)
			{
	       		 seed = verify((void *)memory->array[position %=COUNT]);
	        	 if(seed==-1)
			 {
		        	printf("Verify error\n");
	        	 }

	        	 if(memory->position >= position + COUNT )
			 {
	            		printf("overload");
	            		return 1;
	        	 }

	        	 if(i==0)
			 {
            			genuineseed=seed;
                		i = 1;
	        	 }
				 else if(genuineseed + 1 == seed)
			 {
	            		printf("Error in seed");
	        	 }
			 else
			 {
           			genuineseed++;
	        	 }

            		 printf("Veryfy array[%ld] - seed:%d\n",position %=COUNT,seed);
            		 position ++;
        	}
    	}  
	return 0;
}
