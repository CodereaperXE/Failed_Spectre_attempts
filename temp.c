#include <stdio.h>
#include <stdint.h>
#include <string.h>
#ifdef _MSC_VER
#include <intrin.h> /* for rdtscp and clflush */
#pragma optimize("gt", on)
#else
#include <x86intrin.h> /* for rdtscp and clflush */
#endif


int iterations=25;
int flag=0;
int main() {
	printf("First iteration would be more than 80 since value b was put back into ram\n");
	printf("If in cache the threshold would range less than 80\n");
	while(iterations--){
	register uint64_t time1;
	register uint64_t time2;
	int i;
	int a=0,b=1;

	if(flag==0){
	_mm_clflush(&b);
		flag++;
	}

	time1=__rdtscp(&a);
	a=b;
	time2=__rdtscp(&a)-time1;
	printf("%ld",time2);


	//_mm_clflush(&b);//uncomment to flush value from cache to ram
	
	time1=__rdtscp(&a);
	a=b;
	time2=__rdtscp(&a)-time1;

	printf("|");
	printf("%ld",time2);
	printf("|");
  }
	
}