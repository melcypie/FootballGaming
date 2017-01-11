#include "database.h"
#include "controller2.h"
#include "dataStruct.h"
#include <stdio.h>
#include <string.h>

void teamsSwap(team_t *t1, team_t *t2) {
	team_t temp;
	temp.count = *t1.count;
	*t1.count = *t2.count;
	*t2.count = temp.count;
	temp.id = *t1.id;
	*t1.id = *t2.id;
	*t2.id = temp.id;
	temp.isPlayer = *t1.isPlayer;
	*t1.isPlayer = *t2.isPlayer;
	*t2.isPlayer = temp.isPlayer;
	temp.khorde = *t1.khorde;
	*t1.khorde = *t2.khorde;
	*t2.khorde = temp.khorde;
	temp.money = *t1.money;
	*t1.money = *t2.money;
	*t2.money = temp.money;
	str(temp.name, *t1.name);
	str(*t1.name, *t2.name);
	str(*t2.name, temp.name);
	temp.score = *t1.score;
	*t1.score = *t2.score;
	*t2.score = temp.score;
	temp.zade = *t1.zade;
	*t1.zade = *t2.zade;
	*t2.zade = temp.zade;

}
void creatGamelist(void){
	team_t teams[16];
	getTeamsProfile(teams);
	game_t games[240];
	int counter = 0;
	for (int i = 0;i < 15;i++) {
		for (int j = 0; j < 8; j++) {
			games[counter].id = counter + 1;
			games[counter].team1id = teams[j].id;
			games[counter].team2id = teams[j+8].id;
			games[counter].week = i + 1;

			games[counter + 120].id = counter + 1 + 120;
			games[counter + 120].team1id = teams[j + 8].id;
			games[counter + 120].team2id = teams[j].id;
			games[counter].week = i + 1 + 15;
			counter++;
		}
		for (int j = 1; j <= 7; j++) {
			teamsSwap(&teams[j], &teams[8]);
		}
		for (int j = 15; j >= 9; j--) {
			teamsSwap(&teams[j], &teams[8]);
		}
	}
	saveGamesProfile(games, 240);

}

