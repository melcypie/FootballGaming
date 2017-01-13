/*
* Author :leily nourbakhsh
* Description:
* Functions::
Game list:bazi haeei k gharere dar hafte bargozar beshe ra ba estefade az tabee 
va jabeb jaeie 2 ta team ba estefade az Swap va bad ham zakhire sazi ba tabe save
games
*
*/

#include "dataStruct.h"
#include "database.h"
#include "controller2.h"
#include "controller1.h"
#include <stdio.h>
#include <string.h>
#include "utilities.h"

void teamsSwap(team_t *t1, team_t *t2) {
	team_t temp;
	temp.count = t1->count;
	t1->count = t2->count;
	t2->count = temp.count;
	temp.id = t1->id;
	t1->id = t2->id;
	t2->id = temp.id;
	temp.isPlayer = t1->isPlayer;
	t1->isPlayer = t2->isPlayer;
	t2->isPlayer = temp.isPlayer;
	temp.khorde = t1->khorde;
	t1->khorde = t2->khorde;
	t2->khorde = temp.khorde;
	temp.money = t1->money;
	t1->money = t2->money;
	t2->money = temp.money;
	strcpy(temp.name, t1->name);
	strcpy(t1->name, t2->name);
	strcpy(t2->name, temp.name);
	temp.score = t1->score;
	t1->score = t2->score;
	t2->score = temp.score;
	temp.zade = t1->zade;
	t1->zade = t2->zade;
	t2->zade = temp.zade;

}
void creatGamelist(void){
	team_t teams[16];
	getTeamsProfile(teams);
	int a = randomNo(10000000, 999999999);
	for (int i = 0;i <4 ;i++) {
		int temp = a % 100;
		teamsSwap(&teams[temp%10], &teams[temp/10]);
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
			games[counter + 120].week = i + 1 + 15;
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
	int search = 0;
	if (baze >= 0 && baze < DefaRange) {
		 search = (baze-0) / 1;
		pos = 3;
	}
	else if ( baze>=MianeRange &&  baze< MianeRange) {
		pos = 2;
		 search = (baze-DefaRange) / 2;
	}
	else if (baze >= HamleRange && baze < HamleRange) {
		pos = 1;
		 search = (baze-MianeRange) / 3;

	}
	int i = 0;
	for (;search > 0;i++) {
		if (index[1][i] == pos)
			search--;
	}
	players[index[0][i - 1]].goal++;


}
//tabee playweek
//n=hafte

void playWeek(int n,player_t*players,int size, team_t *teams){
	game_t *games;
	
	int m = getGames(&games);
	game_t gameShouldPlay[8];
	int k = 0;
	for (int i = 0;i < m;i++) {

		if (games[i].week == n) {
			gameShouldPlay[k].id = games[i].id;
			gameShouldPlay[k].team1id = games[i].team1id;
			gameShouldPlay[k].team2id = games[i].team2id;

			k++;

		}
	}
	for (int i = 0;i < 8;i++)
		if (teams[gameShouldPlay[i].team1id - 1].isPlayer == 0 && teams[gameShouldPlay[i].team2id - 1].isPlayer == 0) {
			int goalTeam1 = 0;
			int goalTeam2 = 0;
			bubblePlayers(players, size, playerTEAMID);
			int size1 = 0;
			int size2 = 0;
			int team1Last = 0;
			int team2Last = 0;
			for (int i = 0;i < size;i++) {
				if (players[i].teamid == gameShouldPlay[i].team1id) {
					size1++;
					team1Last = i;
				}
				else if(players[i].teamid == gameShouldPlay[i].team2id){
					size2++;
					team2Last = i;
				}
			}
			playGameCC(&teams[gameShouldPlay[i].team1id - 1], &teams[gameShouldPlay[i].team2id - 1], &goalTeam1, &goalTeam2, &players[team1Last-size1-1],  size1, &players[team2Last-size2-1], size2);
			natayej_t natije;
			natije.gameid = gameShouldPlay[i].id;
			natije.team1goal = goalTeam1;
			natije.team2goal = goalTeam2;

			addNatayejProfile(&natije,  1);
		}
}