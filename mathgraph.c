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

typedef struct {
	int funcOffset;
	int* graphXoffset;
	int graphHeight;
	int graphLength;
	int* graphYoffset;

} DrawParameters;
void DrawFunc(DrawParameters* dp);

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
		DrawParameters dp = {.funcOffset = funcOffset, .graphXoffset = &graphXoffset, .graphYoffset = &graphYoffset, .graphLength = graphLength, .graphHeight = graphHeight};
		DrawFunc(&dp);	
		CLRSCR();	
		remainder = start_time - time(0) + interval;
		funcOffset++;
	}
	SHOW_CURSOR();
	return 0;

}


void DrawFunc(DrawParameters* dp){

 for(int i = 0; i< (*dp).graphLength; i++){
	int value = (int)fmin((*dp).graphHeight + *dp->graphYoffset,(evaluate(Sin,(i+((*dp).funcOffset))) + (*dp->graphYoffset)));
        SETCURSOR(i+(*dp->graphXoffset),value);
	printf("■");
	if(value == (*dp).graphHeight + (*dp->graphYoffset)) continue;
	int temp_value = value;
	while(temp_value++){
		SETCURSOR(i+(*dp->graphXoffset),temp_value);
		printf("▣");
		if(temp_value >= (*dp).graphHeight + (*dp->graphYoffset)) break;
	}
        
   }
}

double evaluate( double (*f)(double),double x){
	return f(x);
}

double Sin(double x){
	return sin(x*0.1f)*10;
}
	

