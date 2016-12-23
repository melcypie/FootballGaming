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

int main(){
	team_t teams[16];
	getTeamsDatabase(teams);
	strcpy(teams[15].name, "Mahdi Alikhasi");
	saveProfile(teams,16);
	getTeamsProfile(teams);
	printf("%s\n", teams[15].name);
	clearProfile();
	return (EXIT_SUCCESS);
}