/*
* Author :leily nourbakhsh
* Description:
* Functions::
Game list:bazi haeei k gharere dar hafte bargozar beshe ra ba estefade az tabee 
va jabeb jaeie 2 ta team ba estefade az Swap va bad ham zakhire sazi ba tabe save
games
*
*/


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
	int a = randomNo(10000000, 999999999);
	for (int i = 0;i <4 ;i++) {
		int temp = a % 100;
		Swap(&team[temp%10], &team[temp/10]);
		a /= 100;
	}
	

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


void goalAssign(player_t *players, int index[2][11], int size) {

	int tedadDefa = 0;
	int tedadHamle = 0;
	int tedadMiane = 0;
	for (int i = 0;i < 11;i++) {
		if (index[1][i] == 1)
			tedadHamle++;
		else if (index[1][i] == 2)
			tedadMiane++;
		else if (index[1][i] == 3)
			tedadDefa++;
	}
	int DefaRange = tedadDefa * 1;
	int MianeRange = DefaRange + tedadMiane * 2;
	int HamleRange = MianeRange + tedadHamle * 3;
	int pos = 0;
	int baze = randomNo(0, HamleRange);
	if (baze >= 0 && baze < DefaRange) {
		int search = (baze-0) / 1;
		pos = 3;
	}
	else if ( baze>=MianeRange &&  baze< MianeRange) {
		pos = 2;
		int search = (baze-DefaRange) / 2;
	}
	else if (baze >= HamleRange && baze < HamleRange) {
		pos = 1;
		int search = (baze-MianeRange) / 3;

	}
	int i = 0;
	for (;search > 0;i++) {
		if (index[1][i] == pos)
			search--;
	}
	players[index[0][i - 1]].goal++;


}










		
		



	
		



}
