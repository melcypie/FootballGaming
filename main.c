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
	//welcomeFootball();
	team_t teams[16];
	getTeamsDatabase(teams);
	player_t *players;
	int count = getPlayersDatabase(&players);
	printAllPlayers(players, count, teams);
	printTeamPlayers(players, count, teams, 3);
	printAllTeamsList(teams, 16);
	return (EXIT_SUCCESS);
}