/*
* Author : Mahdi Alikhasi, leily nourbakhsh
* Description:
* Functions::
*/
#include "dataStruct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "profile.h"
#include "utilities.h"
#include "controller1.h"
#include "controller2.h"

int index_p[2][11];//bazikon haye tooye teame ma hamashoono aval 0 mizarim
int main(){
	start();
	clearPage();
	status();
	char a[100];
	char last = 0;
	while(1){
		scanf("%99[^\n]", a);
		flushBuffer();
		if(strcmp(a, "damn") == 0){
			if(last == 's'){
				strcpy(a, "status");
			}else if(last == 'e'){
				strcpy(a, "exit");
			}else if(last == 'p'){
				strcpy(a, "procceed");
			}else if(last == 'l'){
				strcpy(a, "lineup");
			}
		}
		if (strcmp(a, "status") == 0) {
			status();
		}else if (strcmp(a, "exit") == 0) {
			return (EXIT_SUCCESS);
		}else if (strcmp(a,"lineup")==0) {
			lineup();
		}else if (strncmp(a, "procceed", 8) == 0) {
			int n = 1;
			char s[100];
			if(a[8] != 0)
				sscanf(a, "%s %d", s, &n);
			procceed(n);
		}else {
			printf("dastoor na motabar ast !! \n");
			printf("dobare vared kon!!\n");
			printf("%s", "Manzuret in bud :: ");
			if(strncmp(a, "s", 1) == 0){
				printf("%s\n", "status");
				last = 's';
			}else if(strncmp(a, "l", 1) == 0){
				printf("%s\n", "lineup");
				last = 'l';
			}else if(strncmp(a, "p", 1) == 0){
				printf("%s\n", "procceed");
				last = 'p';
			}else if(strncmp(a, "e", 1) == 0){
				printf("%s\n", "exit");
				last = 'e';
			}
			printf("%s\n", "Age Are benevis damn");
		}
	}
	
}