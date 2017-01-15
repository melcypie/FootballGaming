/*
* Author : Mahdi Alikhasi
* Description: some utilities that will need in the program like clearing page, printing data and so on
* Functions::
*		clearPage: clear the entire page using shell built in functions
*		welcomeFootball: play a playload txet
*		randomNo : arguman f and l. make a random number between f and l
*		flushBuffer: clear input buffer
*/
#include "dataStruct.h"
#include <stdlib.h>
#include "utilities.h"
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>

static int seed_count = 0;
//Sort
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
void playersSwap(player_t *t1, player_t *t2) {
	player_t temp;
	temp.id = t1->id;
	t1->id = t2->id;
	t2->id = temp.id;
	temp.teamid = t1->teamid;
	t1->teamid = t2->teamid;
	t2->teamid = temp.teamid;
	temp.goal = t1->goal;
	t1->goal = t2->goal;
	t2->goal = temp.goal;
	temp.position = t1->position;
	t1->position = t2->position;
	t2->position = temp.position;
	temp.skill = t1->skill;
	t1->skill = t2->skill;
	t2->skill = temp.skill;
	strcpy(temp.name, t1->name);
	strcpy(t1->name, t2->name);
	strcpy(t2->name, temp.name);
	temp.amadegi = t1->amadegi;
	t1->amadegi = t2->amadegi;
	t2->amadegi = temp.amadegi;
	temp.khastegi = t1->khastegi;
	t1->khastegi = t2->khastegi;
	t2->khastegi = temp.khastegi;
	temp.rouhiye = t1->rouhiye;
	t1->rouhiye = t2->rouhiye;
	t2->rouhiye = temp.rouhiye;
	temp.khoshunat = t1->khoshunat;
	t1->khoshunat = t2->khoshunat;
	t2->khoshunat = temp.khoshunat;
	temp.sen = t1->sen;
	t1->sen = t2->sen;
	t2->sen = temp.sen;
	temp.shomare = t1->shomare;
	t1->shomare = t2->shomare;
	t2->shomare = temp.shomare;
	temp.sum = t1->sum;
	t1->sum = t2->sum;
	t2->sum = temp.sum;
}
void bubblePlayers(player_t *players, int size, int type){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size - 1 - i; j++){
			switch (type){
				case playerTEAMID:
					if(players[j].teamid > players[j+1].teamid){
						playersSwap(&players[j], &players[j+1]);
					}
					break;
				case playerNAME:
					if(strcmp(players[j].name , players[j+1].name) > 0){
						playersSwap(&players[j], &players[j+1]);
					}
					break;
				case playerGOAL:
					if(players[j].goal > players[j+1].goal){
						playersSwap(&players[j], &players[j+1]);
					}
					break;
				case playerPOSITION:
					if(players[j].position > players[j+1].position){
						playersSwap(&players[j], &players[j+1]);
					}
					break;
				case playerSKILL:
					if(players[j].skill > players[j+1].skill){
						playersSwap(&players[j], &players[j+1]);
					}
					break;
				case playerAMADEGI:
					if(players[j].amadegi > players[j+1].amadegi){
						playersSwap(&players[j], &players[j+1]);
					}
					break;
				case playerKHASTEGI:
					if(players[j].khastegi > players[j+1].khastegi){
						playersSwap(&players[j], &players[j+1]);
					}
					break;
				case playerROUHIYE:
					if(players[j].rouhiye > players[j+1].rouhiye){
						playersSwap(&players[j], &players[j+1]);
					}
					break;
				case playerKHOSHUNAT:
					if(players[j].khoshunat > players[j+1].khoshunat){
						playersSwap(&players[j], &players[j+1]);
					}
					break;
				case playerSUM:
					if(players[j].sum > players[j+1].sum){
						playersSwap(&players[j], &players[j+1]);
					}
					break;
				default:
					if(players[j].id > players[j+1].id){
						playersSwap(&players[j], &players[j+1]);
					}
					break;
			}
		}
	}
}
void bubbleTeams(team_t *teams, int size, int type){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size - 1 - i; j++){
			switch (type){
				case teamNAME:
					if(strcmp(teams[j].name , teams[j+1].name) > 0){
						teamsSwap(&teams[j], &teams[j+1]);
					}
					break;
				case teamISPLAYER:
					if(teams[j].isPlayer > teams[j+1].isPlayer){
						teamsSwap(&teams[j], &teams[j+1]);
					}
					break;
				case teamMONEY:
					if(teams[j].money > teams[j+1].money){
						teamsSwap(&teams[j], &teams[j+1]);
					}
					break;
				case teamSCORE:
					if(teams[j].score > teams[j+1].score){
						teamsSwap(&teams[j], &teams[j+1]);
					}
					break;
				case teamZADE:
					if(teams[j].zade > teams[j+1].zade){
						teamsSwap(&teams[j], &teams[j+1]);
					}
					break;
				case teamKHORDE:
					if(teams[j].khorde > teams[j+1].khorde){
						teamsSwap(&teams[j], &teams[j+1]);
					}
					break;
				case teamCOUNT:
					if(teams[j].count > teams[j+1].count){
						teamsSwap(&teams[j], &teams[j+1]);
					}
					break;
				default:
					if(teams[j].id > teams[j+1].id){
						teamsSwap(&teams[j], &teams[j+1]);
					}
					break;
			}
		}
	}
}
void bubbleTeamsLeague(team_t *teams, int size){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size - 1; j++){
			if((teams + j)->score < (teams + j + 1)->score){
				teamsSwap(&teams[j], &teams[j+1]);
			}else if((teams + j)->score == (teams + j + 1)->score){
				if((teams + j)->zade < (teams + j + 1)->zade){
					teamsSwap(&teams[j], &teams[j+1]);
				}else if((teams + j)->zade == (teams + j + 1)->zade){
					if((teams + j)->khorde > (teams + j + 1)->khorde){
						teamsSwap(&teams[j], &teams[j+1]);
					}else if((teams + j)->khorde == (teams + j + 1)->khorde){
						if((teams + j)->id > (teams + j + 1)->id){
							teamsSwap(&teams[j], &teams[j+1]);
						}
					}
				}
			}
		}
	}
}
void clearPage(){
	printf("\033[H\033[J");
}
void welcomeFootball(void){
	char line[5][59] = {
		" mmmmmm  mmmm   mmmm mmmmmmm mmmmm    mm   m      m     ", 
		" #      m\"  \"m m\"  \"m   #    #    #   ##   #      #     ", 
		" #mmmmm #    # #    #   #    #mmmm\"  #  #  #      #     ", 
		" #      #    # #    #   #    #    #  #mm#  #      #     ", 
		" #       #mm#   #mm#    #    #mmmm\" #    # #mmmmm #mmmmm"
	};
	printf("\033[H\033[J");
	int len = 56;
	struct timespec tim, tim2;
    tim.tv_sec = 0;
	tim.tv_nsec = 50000000;
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    for(int i = 0; i + 1 < w.ws_row; i++){
		if(i == 0){
			printf("┏");
			for(int j = 0; j + 2< w.ws_col; j++){
				printf("━");		
			}
			printf("┓\n");
			continue;
		}else if(i == w.ws_row - 2){
			printf("┗");
			for(int j = 0; j + 2 < w.ws_col; j++){
				printf("━");		
			}
			printf("┛\n");
			break;
		}
		printf("┃");
		if(i % 2){
			for(int j = 0; j + 2< w.ws_col; j++){
				printf("\u2059");		
			}
		}else{
			for(int j = 0; j + 2< w.ws_col; j++){
				printf(" ");		
			}
		}
		printf("┃");
		printf("\n");
	}
	struct timespec tim3;
    tim3.tv_sec = 0;
	tim3.tv_nsec = 500000000;
	nanosleep(&tim3, &tim2);
	for(int i = 0; i < w.ws_col; i++){
		printf("\033[H\033[J");
		printf("\033[%d;0H\x1b[3m", w.ws_row / 2 - 2);
		for(int j = 0; j < i; printf(" "),j++);
		printf("%s\n", line[0]);
		for(int j = 0; j < i; printf(" "),j++);
		printf("%s\n", line[1]);
		for(int j = 0; j < i; printf(" "),j++);
		printf("%s\n", line[2]);
		for(int j = 0; j < i; printf(" "),j++);
		printf("%s\n", line[3]);
		for(int j = 0; j < i; printf(" "),j++);
		printf("%s\n", line[4]);
		if(i > w.ws_col - len - 1){
			line[0][w.ws_col - i - 2] = '\0';
			line[1][w.ws_col - i - 2] = '\0';
			line[2][w.ws_col - i - 2] = '\0';
			line[3][w.ws_col - i - 2] = '\0';
			line[4][w.ws_col - i - 2] = '\0';
		}
		nanosleep(&tim, &tim2);	
	}
	printf("\033[H\033[J\x1b[0m");
}
int randomNo(int f, int l){
	srand(time(NULL) + seed_count++);
	return (rand() % (l + 1 - f) + f);
}
void flushBuffer(void){
	char tmp;
	scanf("%c", &tmp);
	while(tmp != '\n'){
		scanf("%c", &tmp);
	}
}
//Prints...
void printAllPlayers(player_t *players, int size, team_t *teams){
	enum playerField pf;
	pf = playerTEAMID;
	bubblePlayers(players, size, pf);
	enum teamField tf;
	tf = teamID;
	bubbleTeams(teams, 16, tf);
	printf(BLUE "┏━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━┳━━━━┳━━━━━━━━━━┳━━━━━┳━━━━━━━┳━━━━━━━━┳━━━━━━━┳━━━━━━━━━┓\n" RESET);
	printf(BLUE "┃" RESET "%4s" BLUE "┃" RESET "%20s" BLUE "┃" RESET "%10s" BLUE "┃" RESET "%20s" BLUE "┃" RESET "%4s" BLUE "┃" RESET "%4s" BLUE "┃" RESET "%10s" BLUE "┃" RESET "%5s" BLUE "┃" RESET "%7s" BLUE "┃" RESET "%8s" BLUE "┃" RESET "%7s" BLUE "┃" RESET "%9s" BLUE "┃" RESET "\n", "id","Team", "Shomare","Name", "Sen", "goal", "position" , "skill", "amadegi", "khastegi", "rouhiye", "khoshunat");
	for(int i = 0; i < size; i++){
		printf(BLUE "┣━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━╋━━━━╋━━━━━━━━━━╋━━━━━╋━━━━━━━╋━━━━━━━━╋━━━━━━━╋━━━━━━━━━┫\n" RESET);
		printf(BLUE "┃" RESET "%4d" BLUE "┃" RESET "%20s" BLUE "┃" RESET "%10d" BLUE "┃" RESET "%20s" BLUE "┃" RESET "%4d" BLUE "┃" RESET "%4d" BLUE "┃" RESET "%10s" BLUE "┃" RESET "%5d" BLUE "┃" RESET "%7d" BLUE "┃" RESET "%8d" BLUE "┃" RESET "%7d" BLUE "┃" RESET "%9d" BLUE "┃" RESET "\n", (players + i)->id,teams[(players + i)->teamid - 1].name, (players + i)->shomare ,(players + i)->name, (players + i)->sen, (players + i)->goal, ((players + i)->position == 1) ? "Hamle" : (((players + i)->position == 2) ? "Miane" : (((players + i)->position == 3) ? "Defa" : "DarvazeBan")), (players + i)->skill, (players + i)->amadegi, (players + i)->khastegi, (players + i)->rouhiye, (players + i)->khoshunat);
	}
	printf(BLUE "┗━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━┻━━━━┻━━━━━━━━━━┻━━━━━┻━━━━━━━┻━━━━━━━━┻━━━━━━━┻━━━━━━━━━┛\n" RESET);
}
void printTeamPlayers(player_t *players, int size, team_t *teams, int id){
	enum playerField pf;
	pf = playerTEAMID;
	bubblePlayers(players, size, pf);
	enum teamField tf;
	tf = teamID;
	bubbleTeams(teams, 16, tf);
	int status = 0;
	printf(BLUE "┏━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━┳━━━━┳━━━━━━━━━━┳━━━━━┳━━━━━━━┳━━━━━━━━┳━━━━━━━┳━━━━━━━━━┓\n" RESET);
	printf(BLUE "┃" RESET "%4s" BLUE "┃" RESET "%20s" BLUE "┃" RESET "%10s" BLUE "┃" RESET "%20s" BLUE "┃" RESET "%4s" BLUE "┃" RESET "%4s" BLUE "┃" RESET "%10s" BLUE "┃" RESET "%5s" BLUE "┃" RESET "%7s" BLUE "┃" RESET "%8s" BLUE "┃" RESET "%7s" BLUE "┃" RESET "%9s" BLUE "┃" RESET "\n", "id","Team", "Shomare","Name", "Sen", "goal", "position" , "skill", "amadegi", "khastegi", "rouhiye", "khoshunat");
	for(int i = 0; i < size; i++){
		if(id != (players + i)->teamid){
			if(status == 0){
				continue;
			}else{
				break;
			}
		}else{
			status = 1;
		}
		printf(BLUE "┣━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━╋━━━━╋━━━━━━━━━━╋━━━━━╋━━━━━━━╋━━━━━━━━╋━━━━━━━╋━━━━━━━━━┫\n" RESET);
		printf(BLUE "┃" RESET "%4d" BLUE "┃" RESET "%20s" BLUE "┃" RESET "%10d" BLUE "┃" RESET "%20s" BLUE "┃" RESET "%4d" BLUE "┃" RESET "%4d" BLUE "┃" RESET "%10s" BLUE "┃" RESET "%5d" BLUE "┃" RESET "%7d" BLUE "┃" RESET "%8d" BLUE "┃" RESET "%7d" BLUE "┃" RESET "%9d" BLUE "┃" RESET "\n", (players + i)->id,teams[(players + i)->teamid - 1].name, (players + i)->shomare ,(players + i)->name, (players + i)->sen, (players + i)->goal, ((players + i)->position == 1) ? "Hamle" : (((players + i)->position == 2) ? "Miane" : (((players + i)->position == 3) ? "Defa" : "DarvazeBan")), (players + i)->skill, (players + i)->amadegi, (players + i)->khastegi, (players + i)->rouhiye, (players + i)->khoshunat);
	}
	printf(BLUE "┗━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━┻━━━━┻━━━━━━━━━━┻━━━━━┻━━━━━━━┻━━━━━━━━┻━━━━━━━┻━━━━━━━━━┛\n" RESET);
}
void printAllTeamsList(team_t *teams, int size){
	enum teamField tf;
	tf = teamID;
	bubbleTeams(teams, 16, tf);
	printf(BLUE "┏━━━━┳━━━━━━━━━━━━━━━━━━━━┓\n" RESET);
	printf(BLUE "┃" RESET "%4s" BLUE "┃" RESET "%20s" BLUE "┃" RESET "\n", "id","Name");
	for(int i = 0; i < size; i++){
		printf(BLUE "┣━━━━╋━━━━━━━━━━━━━━━━━━━━┫\n" RESET);
		printf(BLUE "┃" RESET "%4d" BLUE "┃" RESET "%20s" BLUE "┃" RESET "\n", (teams + i)->id, (teams + i)->name);
	}
	printf(BLUE "┗━━━━┻━━━━━━━━━━━━━━━━━━━━┛\n" RESET);
}
void printLeagueData(team_t *teams, int size){
	bubbleTeamsLeague(teams, 16);
	printf(BLUE "┏━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━┳━━━━┳━━━━━━┳━━━━━┓\n" RESET);
	printf(BLUE "┃" RESET "%4s" BLUE "┃" RESET "%20s" BLUE "┃" RESET "%5s" BLUE "┃" RESET "%4s" BLUE "┃" RESET "%6s" BLUE "┃" RESET "%5s" BLUE "┃" RESET"\n", "id","Name", "Score", "Zade", "Khorde", "Tedad");
	for(int i = 0; i < size; i++){
		printf(BLUE "┣━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━╋━━━━╋━━━━━━╋━━━━━┫\n" RESET);
		if((teams + i)->isPlayer == 0)
			printf(BLUE "┃" RESET "%4d" BLUE "┃" RESET "%20s" BLUE "┃" RESET "%5d" BLUE "┃" RESET "%4d" BLUE "┃" RESET "%6d" BLUE "┃" RESET "%5d" BLUE "┃" RESET "\n", (teams + i)->id, (teams + i)->name, (teams + i)->score, (teams + i)->zade, (teams + i)->khorde, (teams + i)->count);
		else
			printf(BLUE "┃" RED "%4d" BLUE "┃" RED "%20s" BLUE "┃" RED "%5d" BLUE "┃" RED "%4d" BLUE "┃" RED "%6d" BLUE "┃" RED "%5d" BLUE "┃" RESET "\n", (teams + i)->id, (teams + i)->name, (teams + i)->score, (teams + i)->zade, (teams + i)->khorde, (teams + i)->count);
	}
	printf(BLUE "┗━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━┻━━━━┻━━━━━━┻━━━━━┛\n" RESET);
}
void printGames(game_t *games, int size, team_t *teams){
	if(size == 0)
		return;
	int week = -1;
	bubbleTeams(teams, 16, teamID);
	printf(BLUE "┏━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━┓\n" RESET);
	printf(BLUE "┃" RESET "%4s" BLUE "┃" RESET "%20s" BLUE "┃" RESET "%20s" BLUE "┃" RESET "%4s" BLUE "┃" RESET"\n", "id","Team 1", "Team 2", "Week");
	for(int i=0; i < size; i++){
		if(games[i].week != week){
			if(week != -1){
				printf(BLUE "┗━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━┛\n" RESET);
				printf("\n");
				printf(BLUE "┏━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━┓\n" RESET);
				printf(BLUE "┃" RESET "%4s" BLUE "┃" RESET "%20s" BLUE "┃" RESET "%20s" BLUE "┃" RESET "%4s" BLUE "┃" RESET"\n", "id","Team 1", "Team 2", "Week");
			}
			week = games[i].week;
		}
		printf(BLUE "┣━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━┫\n" RESET);
		printf(BLUE "┃" RESET "%4d" BLUE "┃" "%s" "%20s" BLUE "┃" "%s" "%20s" BLUE "┃" RESET "%4d" BLUE "┃" RESET"\n", games[i].id, (teams[games[i].team1id - 1].isPlayer == 1 ? RED : RESET), teams[games[i].team1id - 1].name, (teams[games[i].team2id - 1].isPlayer == 1 ? RED : RESET),teams[games[i].team2id - 1].name, games[i].week);	
	}
	printf(BLUE "┗━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━┛\n" RESET);
}
void printGameGoals(){

}
void printWeekGames(){

}
void printArrangment(arrangment_t *arrangments, int size){

}