/*
* Author :leily nourbakhsh
* Description:
* Functions::
Game list:bazi haeei k gharere dar hafte bargozar beshe ra ba estefade az tabee 
va jabeb jaeie 2 ta team ba estefade az Swap va bad ham zakhire sazi ba tabe save
games
tabee goal assign mige ki goal zade va mogheeiatesh chi boode!
*
*/

#include "dataStruct.h"
#include "database.h"
#include "controller2.h"
#include "controller1.h"
#include <stdio.h>
#include <string.h>
#include "utilities.h"
extern int index_p[2][11];

void aghayeGoal(void){
	natayej_t *natayej;
	int natayejcount = getNatayej(&natayej);
	if(natayejcount == 0){
		printf("\tHanu bazi i anjam nashode, Hame ye bazi kona 0 goal zade an. Ishala az hafte haye bad aghaye goal ro bbin\n");
		return;
	}
	player_t *players;
	int count = getPlayersProfile(&players);
	bubblePlayers(players, count, playerGOAL);
	int k = 0;
	int i;
	for(i = count - 1; i >=0 ; i--){
		if(i == count - 1)
			k = players[i].goal;
		else if(k != players[i].goal)
			break;
	}
	int size = count - i -1;
	team_t teams[16];
	getTeamsProfile(teams);
	printf("\tAghaye goale League::\n");
	printAllPlayers(&players[count - size],size,teams);
}
void top10(void){
	natayej_t *natayej;
	int natayejcount = getNatayej(&natayej);
	if(natayejcount == 0){
		printf("\tHanu bazi i anjam nashode, vase hamin behtarin bazikona malum nistan. beza 2 ta bazi anjam beshe ta bbinim ki khobes\n");
		return;
	}
	player_t *players;
	int count = getPlayersProfile(&players);
	for(int i = 0; i < count; i++){
		players[i].sum= players[i].amadegi + players[i].rouhiye/2 -players[i].khastegi + players[i].skill;
	}
	bubblePlayers(players, count, playerSUM);
	team_t teams[16];
	getTeamsProfile(teams);
	printf("\tIna behtarin bazikonaye in league hastan alan\n");
	printAllPlayers(&players[count - 10], 10, teams);
}
void creatGamelist(void){
	team_t teams[16];
	getTeamsProfile(teams);//list team haro az profile migire
	int a = randomNo(10000000, 999999999);
	//gereftane yek adade randome 8 raghami baraye inke 8 ta bazi avalo avaz konim.
	for (int i = 0;i <4 ;i++) {
		//chon adade 8 raghami /100 pas 2 ta 2ta joda mishe pasi<4
		int temp = a % 100;
		teamsSwap(&teams[temp%10], &teams[temp/10]);
		a /= 100;
	}
	game_t games[240];
	//too har hafte 8 ta bazi 15 hafte gharare bargozar she raft va bargasht ham 15 ta.
	int counter = 0;
	//counter ma dare 240 taro por mikone. 
	for (int i = 0;i < 15;i++) {
		for (int j = 0; j < 8; j++) {
			//bazi haye raft :
			games[counter].id = counter + 1;
			games[counter].team1id = teams[j].id;
			games[counter].team2id = teams[j+8].id;
			games[counter].week = i + 1;
			// baazi haye bargaasht:

			games[counter + 120].id = counter + 1 + 120;
			games[counter + 120].team1id = teams[j + 8].id;
			games[counter + 120].team2id = teams[j].id;
			games[counter + 120].week = i + 1 + 15;
			counter++;
		}
		//jahaye team haro baham avaz karde!!
		for (int j = 1; j <= 7; j++) {
			teamsSwap(&teams[j], &teams[8]);
		}
		for (int j = 15; j >= 9; j--) {
			teamsSwap(&teams[j], &teams[8]);
		}
	}
	//bayad save she tooye profile:
	saveGamesProfile(games, 240);
}
void goalAssign(player_t *players, int index[2][11], int size,int type) {
	int tedadDefa = 0;
	int tedadHamle = 0;
	int tedadMiane = 0;
	//yek halghe k rooye bazikon ha micharkhad
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
		search = (baze - 0) / 1;
		pos = 3;
	}else if ( baze >= DefaRange &&  baze < MianeRange) {
		pos = 2;
		search = (baze - DefaRange) / 2;
	}
	else if (baze >= MianeRange && baze < HamleRange) {
		pos = 1;
		search = (baze - MianeRange) / 3;
	}
	int i = 0;
	for (;search >= 0;i++) {
		if (index[1][i] == pos)
			search--;
	}
	if(type == 0){
		players[index[0][i - 1]].goal++;
	}else {
		int k = index[0][i - 1];
		for (int i = 0;i < size;i++){
			if (players[i].id == k){
				players[i].goal++;
			}
		}
	}
}
//tabee playweek
//bazi haye hafteye n om ra migooyad
//n=hafte
void playWeek(int n,player_t *players,int size, team_t *teams){
	game_t *games;
	//list bazi haye anjaam shode ya anjam nashode ra az profile migirad.
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
	bubbleTeams(teams,16, teamID);
	for (int i = 0;i < 8;i++){		
		if (teams[gameShouldPlay[i].team1id - 1].isPlayer == 0 && teams[gameShouldPlay[i].team2id - 1].isPlayer == 0) {
			int goalTeam1 = 0;
			int goalTeam2 = 0;
			bubblePlayers(players, size, playerTEAMID);
			int size1 = 0;
			int size2 = 0;
			int team1Last = 0;
			int team2Last = 0;
			for (int j = 0;j < size;j++) {
				if (players[j].teamid == gameShouldPlay[i].team1id) {
					size1++;
					team1Last = j;
				}
				else if(players[j].teamid == gameShouldPlay[i].team2id){
					size2++;
					team2Last = j;
				}
			}
			playGameCC(&teams[gameShouldPlay[i].team1id - 1], &teams[gameShouldPlay[i].team2id - 1], &goalTeam1, &goalTeam2, &players[team1Last - size1 + 1],  size1, &players[team2Last-size2 + 1], size2);
			natayej_t natije;
			natije.gameid = gameShouldPlay[i].id;
			natije.team1goal = goalTeam1;
			natije.team2goal = goalTeam2;
			addNatayejProfile(&natije, 1);
		}else if(teams[gameShouldPlay[i].team1id - 1].isPlayer == 1 && teams[gameShouldPlay[i].team2id - 1].isPlayer == 0){
			int goalTeam1 = 0;
			int goalTeam2 = 0;
			bubblePlayers(players, size, playerTEAMID);
			int size1 = 0;
			int size2 = 0;
			int team1Last = 0;
			int team2Last = 0;
			for (int j = 0;j < size;j++) {
				if (players[j].teamid == gameShouldPlay[i].team1id) {
					size1++;
					team1Last = j;
				}
				else if (players[j].teamid == gameShouldPlay[i].team2id) {
					size2++;
					team2Last = j;
				}
			}
			playGameCP(&teams[gameShouldPlay[i].team2id - 1], &teams[gameShouldPlay[i].team1id - 1], &goalTeam2, &goalTeam1, &players[team2Last - size2 + 1], size2, &players[team1Last - size1 + 1], size1);
			natayej_t natije;
			natije.gameid = gameShouldPlay[i].id;
			natije.team1goal = goalTeam1;
			natije.team2goal = goalTeam2;
			addNatayejProfile(&natije, 1);
		}else {
			int goalTeam1 = 0;
			int goalTeam2 = 0;
			bubblePlayers(players, size, playerTEAMID);
			int size1 = 0;
			int size2 = 0;
			int team1Last = 0;
			int team2Last = 0;
			for (int j = 0;j < size;j++) {
				if (players[j].teamid == gameShouldPlay[i].team1id) {
					size1++;
					team1Last = j;
				}
				else if (players[j].teamid == gameShouldPlay[i].team2id) {
					size2++;
					team2Last = j;
				}
			}
			playGameCP(&teams[gameShouldPlay[i].team1id - 1], &teams[gameShouldPlay[i].team2id - 1], &goalTeam1, &goalTeam2, &players[team1Last - size1 + 1], size1, &players[team2Last - size2 + 1], size2);
			natayej_t natije;
			natije.gameid = gameShouldPlay[i].id;
			natije.team1goal = goalTeam1;
			natije.team2goal = goalTeam2;
			addNatayejProfile(&natije, 1);
		}
		bubblePlayers(players,size,playerID);
		bubbleTeams(teams,16,teamID);
		saveTeamsProfile(teams,16);
		savePlayersProfile(players,size);
	}
	printNatijeWeek(n);
}
void status(void) {
	team_t p[16];
	getTeamsProfile(p);
	printf("jadvale league bazi ha::\n");
	printLeagueData(p, 16);
	printf("baazi haye badi::\n");
	int count = 0;
	game_t *games;
	count = getGames(&games);
	natayej_t *natayej;
	int count1 = getNatayej(&natayej);
	int k = 0;
	for (int i = 0;i < count1;i++) {
		if (natayej[count1 - 1].gameid == games[i].id) {
			k = games[i].week;
			break;
		}
	}
	printGames(&games[8 * k], count - 8 * k, p);//ye tabas k too khodesh printf dare
}
void procceed(int n) {
	int count = 0;
	natayej_t *natayej;
	count = getNatayej(&natayej);
	int count1 = 0;
	player_t *players;
	count1 = getPlayersProfile(&players);
	team_t teams[16];
	getTeamsProfile(teams);
	game_t *games;
	int count3 = 0;
	count3 = getGames(&games);
	if(count == 0){
		if(n > 30){
			printf("\tNmishe bishtar az 30 hafte ro bargozar kard");
			return;
		}
	}else{
		if(n + games[natayej[count - 1].gameid -1].week > 30){
			printf("\tNmishe bishtar az 30 hafte ro bargozar kard");
			return;	
		}
	}
	for (int i = 0;i < n;i++) {
		bubblePlayers(players, count1, playerID);
		bubbleTeams(teams, 16, teamID);
		if(count == 0)
			playWeek(i + 1, players, count1, teams);
		else
			playWeek(games[natayej[count - 1].gameid -1].week + i + 1, players, count1, teams);
		bubblePlayers(players, count1, playerID);
		bubbleTeams(teams, 16, teamID);
		saveTeamsProfile(teams, 16);
		savePlayersProfile(players, count1);
	}		
}
void lineup(void) {
	int HaveSaved = 1;
	if(index_p[0][0] == 0){
		if(getIndex(index_p) == 0)
			HaveSaved = 0;
		else
			return;
	}
	int count1 = 0;
	player_t *players;
	count1 = getPlayersProfile(&players);
	team_t teams[16];
	getTeamsProfile(teams);
	int k = 0;
	for (int i = 0;i < 16;i++) {
		if (teams[i].isPlayer == 1)
			k=teams[i].id;
	}
	player_t players_in[11];
	if(HaveSaved == 1){
		printf("tamame bazikon hayat inha hasatand!!\n");
		printTeamPlayers(players, count1, teams, k);
		bubblePlayers(players, count1, playerID);
		bubbleTeams(teams, 16, teamID);
		for (int i = 0;i < 11;i++) {
				players_in[i].id = players[index_p[0][i] - 1].id;
				players_in[i].amadegi = players[index_p[0][i] - 1].amadegi;
				players_in[i].goal = players[index_p[0][i] - 1].goal;
				players_in[i].khastegi = players[index_p[0][i] - 1].khastegi;
				players_in[i].khoshunat = players[index_p[0][i] - 1].khoshunat;
				strcpy(players_in[i].name, players[index_p[0][i] - 1].name);
				players_in[i].position = players[index_p[0][i] - 1].position;
				players_in[i].rouhiye = players[index_p[0][i] - 1].rouhiye;
				players_in[i].sen = players[index_p[0][i] - 1].sen;
				players_in[i].shomare = players[index_p[0][i] - 1].shomare;
				players_in[i].skill = players[index_p[0][i] - 1].skill;
				players_in[i].sum = players[index_p[0][i] - 1].sum;
				players_in[i].teamid = players[index_p[0][i] - 1].teamid;

		}
		printf("\tbazikon haye tooye zamin inha hasatand!\n");
		//printTeamPlayers(players_in, 11, teams, k);
		printPlayerIn(players_in, 11,index_p, 1);
		printf("\tmikhay Arrengemant ra avaz koni??\n");
		printf("\tage mikhay bzan yes age nemikhay bzan no!\n");
	}
	char s[5];
	while (1) {
		if(HaveSaved){
			printf(GREEN "\x1b[3mPlayer@Host:$ " RESET);
			scanf("%4s", s);
			flushBuffer();
		}else{
			clearPage();
			printf("%s\n", "\tTo arrangmenti Nadari, Bayad Ye arrangmenti vase teamet besazi\n");
			strcpy(s, "yes");
		}
		if (strcmp(s, "no") == 0) {
			break;
		}else if (strcmp(s, "yes") == 0) {
			arrangment_t  *arrangment;
			int count = 0;
			count = getArrangments(&arrangment);
			printArrangment(arrangment, count);
			int defa = 0;
			int miane = 0;
			int hamle = 0;
			while (1) {
				printf("\tarrangment haye dade shode ra mikhay?\n");
				printf("\tage mikhay bzan yes age nemikhay bzan no!\n");
				printf(GREEN "\x1b[3mPlayer@Host:$ " RESET);
				scanf("%4s", s);
				flushBuffer();
				int status = 0;
				if (strcmp(s, "no") == 0) {
					clearPage();
					printf("\t3 ta adad be tartibe defa miane va hamle vared kon\n");
					while (1) {
						printf(GREEN "\x1b[3mPlayer@Host:$ " RESET);
						scanf("%d %d %d", &defa, &miane, &hamle);
						flushBuffer();
						if((defa+miane+hamle)!=10){
							printf("\triiidi ba in arrangmentet!!\n");
						}else{
							status = 1;
							break;
						}
					}
				}else if (strcmp(s, "yes") == 0) {
					printf("\tharkodam ra ke mikhahi shomarasho az jadval vared kon\n");
					int number = 1;
					while (1) {
						printf(GREEN "\x1b[3mPlayer@Host:$ " RESET);
						scanf("%d", &number);
						flushBuffer();
						if (number > count || number < 1) {
							printf("\tchenin arrangmenti vojood nadarad");
							printf("\tlotfan ye adade beine 1 ta %d vared konid\n", count);
						}else {
							status = 1;
							break;
						}						
					}
					defa = arrangment[number - 1].defa;
					miane = arrangment[number - 1].miane;
					hamle = arrangment[number - 1].hamle;
				}else {
					printf("\tvoroodi ghalat ast@@ dobare emtehan kon!!\n");
				}
				if(status)
					break;
			}
			int status = 0;
			int size = 0;
			int i = 0;
			for (i = 0; i < count1; i++) {
				if (players[i].teamid == k) {
					size++;
					status = 1;
				} else {
					if (status == 1)
						break;
				}
			}
			player_t players_mine[size];
			for (int j = 0; j < size; j++) {
				players_mine[j].id = players[i - size + j].id;
				players_mine[j].amadegi = players[i - size + j].amadegi;
				players_mine[j].goal = players[i - size + j].goal;
				players_mine[j].khastegi = players[i - size + j].khastegi;
				players_mine[j].khoshunat = players[i - size + j].khoshunat;
				strcpy(players_mine[j].name, players[i - size + j].name);
				players_mine[j].position = players[i - size + j].position;
				players_mine[j].rouhiye = players[i - size + j].rouhiye;
				players_mine[j].sen = players[i - size + j].sen;
				players_mine[j].shomare = players[i - size + j].shomare;
				players_mine[j].skill = players[i - size + j].skill;
				players_mine[j].sum = players[i - size + j].sum;
				players_mine[j].teamid = players[i - size + j].teamid;
			}
			int counter2 = 0;
			int darvazeban = 1;
			for (int i=0 ;  i < size ; i++ ){
				players_mine[i].sum= players_mine[i].amadegi + players_mine[i].rouhiye/2 -players_mine[i].khastegi + players_mine[i].skill;
			}
			bubblePlayers(players_mine, size, playerSUM);
			for (int k = size - 1; k >= 0 && counter2 == 0; k--) {
				if (players_mine[k].position == 4) {
					index_p[0][counter2] = players_mine[k].id;
					index_p[1][counter2] = 4;
					counter2++;
				}
			}

			if (counter2 == 0) {
				darvazeban = 0;
			}

			for (int k = size - 1; k >= 0 && defa > 0; k--) {
				if (players_mine[k].position == 3) {
					index_p[0][counter2] = players_mine[k].id;
					index_p[1][counter2] = 3;
					counter2++;
					defa--;
				}
			}
			for (int k = size - 1; k >= 0 && hamle > 0; k--) {
				if (players_mine[k].position == 1) {
					index_p[0][counter2] = players_mine[k].id;
					index_p[1][counter2] = 1;
					counter2++;
					hamle--;
				}
			}
			for (int k = size - 1; k >= 0 && miane > 0; k--) {
				if (players_mine[k].position == 2) {
					index_p[0][counter2] = players_mine[k].id;
					index_p[1][counter2] = 2;
					counter2++;
					miane--;
				}
			}
			if (defa != 0) {
				for (int k = size - 1; k >= 0 && defa > 0; k--) {
					for (int i = 0; i < counter2; i++) {
						if (players_mine[k].id == index_p[0][i])
							break;
						else if (i == counter2 - 1) {
							index_p[0][counter2] = players_mine[k].id;
							index_p[1][counter2] = 3;
							counter2++;
							defa--;
						}
					}
				}
			}
			if (hamle != 0) {
				for (int k = size - 1; k >= 0 && hamle > 0; k--) {
					for (int i = 0; i < counter2; i++) {
						if (players_mine[k].id == index_p[0][i])
							break;
						else if (i == counter2 - 1) {
							index_p[0][counter2] = players_mine[k].id;
							index_p[1][counter2] = 1;
							counter2++;
							hamle--;
						}
					}
				}
			}

			if (miane != 0) {
				for (int k = size - 1; k >= 0 && miane > 0; k--) {
					for (int i = 0; i < counter2; i++) {
						if (players_mine[k].id == index_p[0][i])
							break;
						else if (i == counter2 - 1) {
							index_p[0][counter2] = players_mine[k].id;
							index_p[1][counter2] = 2;
							counter2++;
							miane--;
						}
					}
				}
			}

			if (darvazeban == 0) {
				for (int k = size - 1; k >= 0 && darvazeban != 0; k--) {
					for (int i = 0; i < counter2; i++) {
						if (players_mine[k].id == index_p[0][i])
							break;
						else if (i == counter2 - 1) {
							index_p[0][counter2] = k;
							index_p[1][counter2] = 4;
							counter2++;
							darvazeban++;
						}
					}
				}
			}
			break;
		}else {
			printf("\tvoroodi ghalat ast@@ dobare emtehan kon\n");
		}
	}
	printf("\talaan in bazikon ha tooye zamin hastand!\n");
	bubblePlayers(players, count1, playerID);
	for (int i = 0;i < 11;i++) {
		players_in[i].id = players[index_p[0][i] - 1].id;
		players_in[i].amadegi = players[index_p[0][i] - 1].amadegi;
		players_in[i].goal = players[index_p[0][i] - 1].goal;
		players_in[i].khastegi = players[index_p[0][i] - 1].khastegi;
		players_in[i].khoshunat = players[index_p[0][i] - 1].khoshunat;
		strcpy(players_in[i].name, players[index_p[0][i] - 1].name);
		players_in[i].position = players[index_p[0][i] - 1].position;
		players_in[i].rouhiye = players[index_p[0][i] - 1].rouhiye;
		players_in[i].sen = players[index_p[0][i] - 1].sen;
		players_in[i].shomare = players[index_p[0][i] - 1].shomare;
		players_in[i].skill = players[index_p[0][i] - 1].skill;
		players_in[i].sum = players[index_p[0][i] - 1].sum;
		players_in[i].teamid = players[index_p[0][i] - 1].teamid;
	}
	printPlayerIn(players_in, 11,index_p, 1);
	printf("\tmikhay bazikon haye tooye zamin ra avaz koni??\n");
	printf("\tyes/no?\n");
	while (1) {
		printf(GREEN "\x1b[3mPlayer@Host:$ " RESET);
		scanf("%s", s);
		flushBuffer();
		if (strcmp(s, "no") == 0) {
			saveIndex(index_p);
			return;
		}else if (strcmp(s, "yes") == 0) {
			printTeamPlayers(players, count1, teams, k);
			printf("\thala bazikon hato avaz kon\n");
			printf("\tharvaght karet tamoom shod '-1' bezan!\n");
			while (1) {
				printf("\tkio ba ki mikhay avaz koni??\n");
				printf("\tid bazikone tooye zamino vared kon!\n");
				int id1 = 0;
				while (1) {
					printf(GREEN "\x1b[3mPlayer@Host:$ " RESET);
					scanf("%d", &id1);
					flushBuffer();
					if (id1 == -1)
						return;
					int status = 0;
					for (int i = 0; i < 11; i++) {
						if (index_p[0][i] == id1)
							status = 1;
					}
					if (status == 0) {
						printf("\tin bazikon dar zamin nist\n");
						printf("\tbazikon haye daroon zamin ra entekhab kon\n");
					}else {
						break;
					}
				}
				printf("\tid nafare dovomo vared kon!\n");
				int id2 = 0;
				bubbleTeams(teams, 16, teamID);
				bubblePlayers(players, count1, playerID);
				while (1) {
					printf(GREEN "\x1b[3mPlayer@Host:$ " RESET);
					scanf("%d", &id2);
					flushBuffer();
					if (teams[players[id2 - 1].teamid - 1].isPlayer == 0) {
						printf("\tin bazikon male shoma nist!\n");
					}
					else {
						break;
					}
				}
				int status = 0;
				for (int i = 0;i < 11;i++) {
					if (id2 == index_p[0][i]) {
						status = 1;
						break;
					}
				}
				if (status == 1) {
					int k1 = 0;
					int k2 = 0;
					for (int i = 0;i < 11;i++) {
						if (index_p[0][i] == id1)
							k1 = i;
						else if (index_p[0][i] == id2)
							k2 = i;
					}
					/*int temp = index_p[0][k1];
					index_p[0][k1] = index_p[0][k2];
					index_p[0][k2] = temp;*/
					index_p[0][k1] ^= index_p[0][k2];
					index_p[0][k2] ^= index_p[0][k1];
					index_p[0][k1] ^= index_p[0][k2];
				}else {
					for (int i = 0;i < 11;i++) {
						if (index_p[0][i] == id1)
							index_p[0][i] = id2;
					}
				}
			}
			saveIndex(index_p);
		}else{
			printf("\tDasturet na motabare !\n");
		}
	}
}