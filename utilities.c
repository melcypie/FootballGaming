/*
* Author : Mahdi Alikhasi
* Description: some utilities that will need in the program like clearing page, printing data and so on
* Functions::
*		clearPage: clear the entire page using shell built in functions
*/
#include "dataStruct.h"
#include <stdlib.h>
#include "utilities.h"
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
void clearPage(){
	#ifdef __linux__ 
    	system("clear");
	#elif _WIN32
    	system("cls");
	#else
		system("clear")
	#endif
}
void welcomeFootball(int len, char line1[], char line2[], char line3[], char line4[], char line5[], long long int nsec){
	printf("\033[H\033[J");
	struct timespec tim, tim2;
    tim.tv_sec = 0;
	tim.tv_nsec = nsec;
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	for(int i = 0; i < w.ws_col; i++){
		printf("\033[H\033[J");
		printf("\033[%d;0H", w.ws_row / 2 - 2);
		for(int j = 0; j < i; printf(" "),j++);
		printf("%s\n", line1);
		for(int j = 0; j < i; printf(" "),j++);
		printf("%s\n", line2);
		for(int j = 0; j < i; printf(" "),j++);
		printf("%s\n", line3);
		for(int j = 0; j < i; printf(" "),j++);
		printf("%s\n", line4);
		for(int j = 0; j < i; printf(" "),j++);
		printf("%s\n", line5);
		if(i > w.ws_col - len - 1){
			line1[w.ws_col - i - 2] = '\0';
			line2[w.ws_col - i - 2] = '\0';
			line3[w.ws_col - i - 2] = '\0';
			line4[w.ws_col - i - 2] = '\0';
			line5[w.ws_col - i - 2] = '\0';
		}
		nanosleep(&tim, &tim2);	
	}
	printf("\033[H\033[J");
}
int random(int f, int l){
	srand(time(NULL));
	return (rand() % (l + 1 - f) + f);
}