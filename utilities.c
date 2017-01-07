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
//Sort
void bubblePlayers(player_t *players, int size, int type){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size - 1 - i; j++){
			switch (type){
				case playerTEAMID:
					if(players[j].teamid > players[j+1].teamid){
						player_t tmp;
						tmp = players[j];
						players[j] = players[j+1];
						players[j+1] = tmp;
					}
					break;
				case playerNAME:
					if(strcmp(players[j].name , players[j+1].name) > 0){
						player_t tmp;
						tmp = players[j];
						players[j] = players[j+1];
						players[j+1] = tmp;
					}
					break;
				case playerGOAL:
					if(players[j].goal > players[j+1].goal){
						player_t tmp;
						tmp = players[j];
						players[j] = players[j+1];
						players[j+1] = tmp;
					}
					break;
				case playerPOSITION:
					if(players[j].position > players[j+1].position){
						player_t tmp;
						tmp = players[j];
						players[j] = players[j+1];
						players[j+1] = tmp;
					}
					break;
				case playerSKILL:
					if(players[j].skill > players[j+1].skill){
						player_t tmp;
						tmp = players[j];
						players[j] = players[j+1];
						players[j+1] = tmp;
					}
					break;
				case playerAMADEGI:
					if(players[j].amadegi > players[j+1].amadegi){
						player_t tmp;
						tmp = players[j];
						players[j] = players[j+1];
						players[j+1] = tmp;
					}
					break;
				case playerKHASTEGI:
					if(players[j].khastegi > players[j+1].khastegi){
						player_t tmp;
						tmp = players[j];
						players[j] = players[j+1];
						players[j+1] = tmp;
					}
					break;
				case playerROUHIYE:
					if(players[j].rouhiye > players[j+1].rouhiye){
						player_t tmp;
						tmp = players[j];
						players[j] = players[j+1];
						players[j+1] = tmp;
					}
					break;
				case playerKHOSHUNAT:
					if(players[j].khoshunat > players[j+1].khoshunat){
						player_t tmp;
						tmp = players[j];
						players[j] = players[j+1];
						players[j+1] = tmp;
					}
					break;
				case playerSUM:
					if(players[j].sum > players[j+1].sum){
						player_t tmp;
						tmp = players[j];
						players[j] = players[j+1];
						players[j+1] = tmp;
					}
					break;
				default:
					if(players[j].id > players[j+1].id){
						player_t tmp;
						tmp = players[j];
						players[j] = players[j+1];
						players[j+1] = tmp;
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
						team_t tmp;
						tmp = teams[j];
						teams[j] = teams[j+1];
						teams[j+1] = tmp;
					}
					break;
				case teamISPLAYER:
					if(teams[j].isPlayer > teams[j+1].isPlayer){
						team_t tmp;
						tmp = teams[j];
						teams[j] = teams[j+1];
						teams[j+1] = tmp;
					}
					break;
				case teamMONEY:
					if(teams[j].money > teams[j+1].money){
						team_t tmp;
						tmp = teams[j];
						teams[j] = teams[j+1];
						teams[j+1] = tmp;
					}
					break;
				case teamSCORE:
					if(teams[j].score > teams[j+1].score){
						team_t tmp;
						tmp = teams[j];
						teams[j] = teams[j+1];
						teams[j+1] = tmp;
					}
					break;
				case teamZADE:
					if(teams[j].zade > teams[j+1].zade){
						team_t tmp;
						tmp = teams[j];
						teams[j] = teams[j+1];
						teams[j+1] = tmp;
					}
					break;
				case teamKHORDE:
					if(teams[j].khorde > teams[j+1].khorde){
						team_t tmp;
						tmp = teams[j];
						teams[j] = teams[j+1];
						teams[j+1] = tmp;
					}
					break;
				case teamCOUNT:
					if(teams[j].count > teams[j+1].count){
						team_t tmp;
						tmp = teams[j];
						teams[j] = teams[j+1];
						teams[j+1] = tmp;
					}
					break;
				default:
					if(teams[j].id > teams[j+1].id){
						team_t tmp;
						tmp = teams[j];
						teams[j] = teams[j+1];
						teams[j+1] = tmp;
					}
					break;
			}
		}
	}
}
void bubbleTeamsLeague(team_t *teams, int size){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if((teams + j)->score < (teams + j + 1)->score){
				team_t tmp;
				tmp = teams[j];
				teams[j] = teams[j+1];
				teams[j+1] = tmp;
			}else if((teams + j)->score == (teams + j + 1)->score){
				if((teams + j)->zade < (teams + j + 1)->zade){
					team_t tmp;
					tmp = teams[j];
					teams[j] = teams[j+1];
					teams[j+1] = tmp;
				}else if((teams + j)->zade == (teams + j + 1)->zade){
					if((teams + j)->khorde > (teams + j + 1)->khorde){
						team_t tmp;
						tmp = teams[j];
						teams[j] = teams[j+1];
						teams[j+1] = tmp;
					}else if((teams + j)->khorde == (teams + j + 1)->khorde){
						if((teams + j)->id > (teams + j + 1)->id){
							team_t tmp;
							tmp = teams[j];
							teams[j] = teams[j+1];
							teams[j+1] = tmp;
						}
					}
				}
			}
		}
	}
}
void clearPage(){
	#ifdef __linux__ 
		printf("\033[H\033[J");
	#elif _WIN32
    	system("cls");
	#else
		printf("\033[H\033[J");
	#endif
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
			printf("\u250F");
			for(int j = 0; j + 2< w.ws_col; j++){
				printf("\u2501");		
			}
			printf("\u2513\n");
			continue;
		}else if(i == w.ws_row - 2){
			printf("\u2517");
			for(int j = 0; j + 2 < w.ws_col; j++){
				printf("\u2501");		
			}
			printf("\u251B\n");
			break;
		}
		printf("\u2503");
		if(i % 2){
			for(int j = 0; j + 2< w.ws_col; j++){
				printf("\u2059");		
			}
		}else{
			for(int j = 0; j + 2< w.ws_col; j++){
				printf(" ");		
			}
		}
		printf("\u2503");
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
	srand(time(NULL));
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
	printf(BLUE "\u250F\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2513\n" RESET);
	printf(BLUE "\u2503" RESET "%4s" BLUE "\u2503" RESET "%20s" BLUE "\u2503" RESET "%10s" BLUE "\u2503" RESET "%20s" BLUE "\u2503" RESET "%4s" BLUE "\u2503" RESET "%4s" BLUE "\u2503" RESET "%10s" BLUE "\u2503" RESET "%5s" BLUE "\u2503" RESET "%7s" BLUE "\u2503" RESET "%8s" BLUE "\u2503" RESET "%7s" BLUE "\u2503" RESET "%9s" BLUE "\u2503" RESET "\n", "id","Team", "Shomare","Name", "Sen", "goal", "position" , "skill", "amadegi", "khastegi", "rouhiye", "khoshunat");
	for(int i = 0; i < size; i++){
		printf(BLUE "\u2523\u2501\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u252B\n" RESET);
		printf(BLUE "\u2503" RESET "%4d" BLUE "\u2503" RESET "%20s" BLUE "\u2503" RESET "%10d" BLUE "\u2503" RESET "%20s" BLUE "\u2503" RESET "%4d" BLUE "\u2503" RESET "%4d" BLUE "\u2503" RESET "%10s" BLUE "\u2503" RESET "%5d" BLUE "\u2503" RESET "%7d" BLUE "\u2503" RESET "%8d" BLUE "\u2503" RESET "%7d" BLUE "\u2503" RESET "%9d" BLUE "\u2503" RESET "\n", (players + i)->id,teams[(players + i)->teamid - 1].name, (players + i)->shomare ,(players + i)->name, (players + i)->sen, (players + i)->goal, ((players + i)->position == 1) ? "Hamle" : (((players + i)->position == 2) ? "Miane" : (((players + i)->position == 3) ? "Defa" : "DarvazeBan")), (players + i)->skill, (players + i)->amadegi, (players + i)->khastegi, (players + i)->rouhiye, (players + i)->khoshunat);
	}
	printf(BLUE "\u2517\u2501\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u251B\n" RESET);
}
void printTeamPlayers(player_t *players, int size, team_t *teams, int id){
	enum playerField pf;
	pf = playerTEAMID;
	bubblePlayers(players, size, pf);
	enum teamField tf;
	tf = teamID;
	bubbleTeams(teams, 16, tf);
	int status = 0;
	printf(BLUE "\u250F\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2513\n" RESET);
	printf(BLUE "\u2503" RESET "%4s" BLUE "\u2503" RESET "%20s" BLUE "\u2503" RESET "%10s" BLUE "\u2503" RESET "%20s" BLUE "\u2503" RESET "%4s" BLUE "\u2503" RESET "%4s" BLUE "\u2503" RESET "%10s" BLUE "\u2503" RESET "%5s" BLUE "\u2503" RESET "%7s" BLUE "\u2503" RESET "%8s" BLUE "\u2503" RESET "%7s" BLUE "\u2503" RESET "%9s" BLUE "\u2503" RESET "\n", "id","Team", "Shomare","Name", "Sen", "goal", "position" , "skill", "amadegi", "khastegi", "rouhiye", "khoshunat");
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
		printf(BLUE "\u2523\u2501\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u252B\n" RESET);
		printf(BLUE "\u2503" RESET "%4d" BLUE "\u2503" RESET "%20s" BLUE "\u2503" RESET "%10d" BLUE "\u2503" RESET "%20s" BLUE "\u2503" RESET "%4d" BLUE "\u2503" RESET "%4d" BLUE "\u2503" RESET "%10s" BLUE "\u2503" RESET "%5d" BLUE "\u2503" RESET "%7d" BLUE "\u2503" RESET "%8d" BLUE "\u2503" RESET "%7d" BLUE "\u2503" RESET "%9d" BLUE "\u2503" RESET "\n", (players + i)->id,teams[(players + i)->teamid - 1].name, (players + i)->shomare ,(players + i)->name, (players + i)->sen, (players + i)->goal, ((players + i)->position == 1) ? "Hamle" : (((players + i)->position == 2) ? "Miane" : (((players + i)->position == 3) ? "Defa" : "DarvazeBan")), (players + i)->skill, (players + i)->amadegi, (players + i)->khastegi, (players + i)->rouhiye, (players + i)->khoshunat);
	}
	printf(BLUE "\u2517\u2501\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u251B\n" RESET);
}
void printAllTeamsList(team_t *teams, int size){
	enum teamField tf;
	tf = teamID;
	bubbleTeams(teams, 16, tf);
	printf(BLUE "+----+--------------------+\n" RESET);
	printf(BLUE "\u2503" RESET "%4s" BLUE "\u2503" RESET "%20s" BLUE "\u2503" RESET "\n", "id","Name");
	for(int i = 0; i < size; i++){
		printf(BLUE "+----+--------------------+\n" RESET);
		printf(BLUE "\u2503" RESET "%4d" BLUE "\u2503" RESET "%20s" BLUE "\u2503" RESET "\n", (teams + i)->id, (teams + i)->name);
	}
	printf(BLUE "+----+--------------------+\n" RESET);
}
void printLeagueData(team_t *teams, int size){
	bubbleTeamsLeague(teams, 16);
	printf(BLUE "+----+--------------------+\n" RESET);
	printf(BLUE "\u2503" RESET "%4s" BLUE "\u2503" RESET "%20s" BLUE "\u2503" RESET "\n", "id","Name");
	for(int i = 0; i < size; i++){
		printf(BLUE "+----+--------------------+\n" RESET);
		printf(BLUE "\u2503" RESET "%4d" BLUE "\u2503" RESET "%20s" BLUE "\u2503" RESET "\n", (teams + i)->id, (teams + i)->name);
	}
	printf(BLUE "+----+--------------------+\n" RESET);
}
void printGameGoals(){

}
void printWeekGames(){

}
