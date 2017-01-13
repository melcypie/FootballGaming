/*
* Author : Mahdi Alikhasi
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

int main(){
	start();
	status();
	char a[100];
	fgets(a,99, stdin);
	if (strcmp(a, "status") == 0) {
		status();
	}
	else if (strcmp(a, "exit") == 0) {
		return;
	}
	else if (strncmp(a, "procceed", 8) == 0) {
		int n = 0;
		char s[100];
		sscanf(a, "%s %d", s, &n);
		procceed(n);
	}
	
}