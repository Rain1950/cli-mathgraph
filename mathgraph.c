#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define CLRSCR() printf("\e[1;1H\e[2J");
#define HIDE_CURSOR()  printf("\33[?25l");
#define SHOW_CURSOR() printf("\33[?25h");
#define SETCURSOR(x,y) printf("\033[%d;%dH", (y), (x))


double evaluate(double (*f)(double),double x);
double Sin(double x);
void Draw(int funcOffset,int graphXoffset,int graphHeight,int graphLength,int graphYoffset);

int main(int argc, int **argv){
	

	
	char symbols[]  = {"■"};
	time_t remainder = 1;
	time_t start_time = 0;
	time_t interval = 1;
	int currentX = 0;
	int graphHeight = 25;
	int graphYoffset = 25;
	int graphXoffset = 10;
	int graphLength = 120;

	HIDE_CURSOR(); 
	struct winsize w;
	ioctl(STDOUT_FILENO,TIOCGWINSZ,&w);

	int funcOffset =0;
	while(1){ //main loop
		usleep(remainder*100000*2);
		start_time = time(0);
		ioctl(STDOUT_FILENO,TIOCGWINSZ,&w);
		CLRSCR();
		Draw(funcOffset,graphXoffset,graphHeight,graphLength,graphYoffset);	
		CLRSCR();	
		remainder = start_time - time(0) + interval;
		funcOffset++;
	}
	SHOW_CURSOR();
	return 0;

}


void Draw(int funcOffset,int graphXoffset,int graphHeight,int graphLength,int graphYoffset){

 for(int i = 0; i< graphLength; i++){
	int value = (int)fmin(graphHeight + graphYoffset,(evaluate(Sin,(i+funcOffset)) + graphYoffset));
        SETCURSOR(i+graphXoffset,value);
	printf("■");
	if(value == graphHeight + graphYoffset) continue;
	int temp_value = value;
	while(temp_value++){
		SETCURSOR(i+graphXoffset,temp_value);
		printf("▣");
		if(temp_value >= graphHeight + graphYoffset) break;
	}
        
   }
}

double evaluate( double (*f)(double),double x){
	return f(x);
}

double Sin(double x){
	return sin(x*0.1f)*15;
}

