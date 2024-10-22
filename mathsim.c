#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define clrscr() printf("\e[1;1H\e[2J")


int main(int argc, int **argv){
	printf("rat1\n");
	printf("guh\n");
	time_t remainder = 1;
	time_t start_time = 1;
	int count = 0;
	printf("\33[?25l");

	

	while(1){ //main loop
		usleep(remainder*50000);
		start_time = time(0);
		printf("■ %d \n",count);
		clrscr();
		
		count++;
		remainder = (start_time + 1) - time(0);

	}

	


	
}

