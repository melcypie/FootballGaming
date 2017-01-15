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
extern int index_p[2][11] = {};//bazikon haye tooye teame ma hamashoono aval 0 mizarim
int main(){
	start();
	status();
	char a[100];
	while(1){
		fgets(a, 99, stdin);
		if (strcmp(a, "status") == 0) {
			status();
		}else if (strcmp(a, "exit") == 0) {
			return;
		}else if (strcmp(s,"lineup")==0) {
			lineup();
		}else if (strncmp(a, "procceed", 8) == 0) {
			int n = 1;
			char s[100];
			sscanf(a, "%s %d", s, &n);
			procceed(n);
		}else {
			printf("dastoor na motabar ast !! \n");
			printf("dobare vared kon!!\n");
		}
	}
	
}