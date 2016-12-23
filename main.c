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
	player_t *ptr = NULL;
	int player_count = getPlayersDatabase(&ptr);
	strcpy(ptr[19].lastname, "Alikhasi");
	saveProfile(teams,16,ptr,player_count);
	getTeamsProfile(teams);
	printf("%s\n", teams[15].name);
	getPlayersProfile(&ptr);
	printf("%s\n", ptr[19].lastname);
	clearProfile();
	return (EXIT_SUCCESS);
}