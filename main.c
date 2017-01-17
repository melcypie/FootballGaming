/*
* Author : Mahdi Alikhasi, leily nourbakhsh
* Description:
* Functions::
*/
#include "dataStruct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "utilities.h"
#include "controller1.h"
#include "controller2.h"
#include "database.h"
int index_p[2][11]; //bazikon haye tooye teame ma
int main(){
	clearPage(); //clear page first
	start(); //and start the game
	clearPage(); //clear it again
	status();
	char a[100];
	char last = 0;
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); //get the height of screen
	while(1){
		{ //Print a valid code list and wait for user to put code
			printf("\n\n\n\033[%d;0H\x1b[3m", w.ws_row); //go to end of screen with italic
			printf("\t%s", "status lineup table procceed help about exit"); //print valid codes
			printf("\033[3A\n"); //go two lines Up
			printf(GREEN "Player@Host:$ " RESET); //wait to get code
		}
		scanf("%99[^\n]", a); //get the code
		flushBuffer();
		printf("\033[%d;0H\033[K", w.ws_row); //go to end of screen and errase it
		if(strcmp(a, "damn") == 0){ //Some damn code ^__^
			if(last == 's'){
				strcpy(a, "status");
			}else if(last == 'e'){
				strcpy(a, "exit");
			}else if(last == 'p'){
				strcpy(a, "procceed");
			}else if(last == 'l'){
				strcpy(a, "lineup");
			}else if(last == 't'){
				strcpy(a, "table");
			}
		}
		if (strcmp(a, "status") == 0) {
			status();
		}else if (strcmp(a, "exit") == 0) {
			return (EXIT_SUCCESS);
		}else if (strcmp(a,"lineup") == 0) {
			lineup();
		}else if (strncmp(a, "procceed", 8) == 0) {
			int n = 1;
			char s[100];
			if(a[8] != 0)
			sscanf(a, "%s %d", s, &n);
			procceed(n);
			status();
		}else if(strcmp(a,"table") == 0){
			team_t teams[16];
			getTeamsProfile(teams);
			printLeagueData(teams, 16);
		}else {
			printf("\tdastoor na motabar ast !! \n");
			printf("\tdobare vared kon!!\n");
			if(strncmp(a, "s", 1) == 0){
				printf("%s", "\tManzuret in bud :: ");
				printf("%s\n", "status");
				last = 's';
				printf("%s\n", "\tAge Are benevis damn");
			}else if(strncmp(a, "l", 1) == 0){
				printf("%s", "\tManzuret in bud :: ");
				printf("%s\n", "lineup");
				last = 'l';
				printf("%s\n", "\tAge Are benevis damn");
			}else if(strncmp(a, "p", 1) == 0){
				printf("%s", "\tManzuret in bud :: ");
				printf("%s\n", "procceed");
				last = 'p';
				printf("%s\n", "\tAge Are benevis damn");
			}else if(strncmp(a, "e", 1) == 0){
				printf("%s", "\tManzuret in bud :: ");
				printf("%s\n", "exit");
				last = 'e';
				printf("%s\n", "\tAge Are benevis damn");
			}else if(strncmp(a, "t", 1) == 0){
				printf("%s", "\tManzuret in bud :: ");
				printf("%s\n", "table");
				last = 't';
				printf("%s\n", "\tAge Are benevis damn");
			}else{
				last = ' ';
			}
		}
	}
	
}