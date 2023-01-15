#include <stdio.h>
#include <string.h>
#include <x86intrin.h>
#include <stdint.h>
#define size 128

uint8_t array1[128*4096];

void read_memory(){
	int i;
	uint8_t *addr;
	for(i=0;i<size;i++){
		array1[i*4096]=0;
	}
	for(i=0;i<size;i++){
		_mm_clflush(&array1[i*4096]);//flushing array from cache
	}

	array1[12*4096]=0xFF;
	int at=0;
	register unsigned long int time1;
	register unsigned long int time2;
	unsigned int junk=0;
	unsigned long int fastest=500;
	for(i=0;i<size;i++){
		addr=&array1[i*4096];
		time1=__rdtscp(&junk);
		junk=*addr;
		time2=__rdtscp(&junk)-time1;
		printf("%ld\n",time2);
		if(time2<=fastest){
			fastest=time2;
			at=i;
		}
	}
	printf("fastest is %ld at %d",fastest,at);
}

int main(){
	read_memory();
}