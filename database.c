/*
* Author : Mahdi Alikhasi
* Description: working with database. get data and save data.
* Functions::
*		getTeams: get the teams from destination (Arguman) and save it to team_t data structure. return NULL if faild. return pointer if succeed.
*		getPlayers: get the list of player from a destination and put it into struct. argument: the address of pointer that will assign to the first player. return number of player that can get.
*		getTeamsProfile : Send profile destination address to getTeams
*		getTeamsDatabase: Send Database destination address to getTeams
*		saveTeamsProfile: Save current Teams data into profile. return 1 if succeedsucceed and 0 if not
*		savePlayersProfile: Save current players data into profile. return 1 if successed and 0 if not
*		getGames : get the game list. Arguman pointer to pointer. return number of games if successed. 0 or not
*		saveGames : Save games list into profile. return 1 if succeed or 0 if not.
*/
#include "dataStruct.h"
#include <stdio.h>
#include <stdlib.h>
#include "database.h"

//make seprator base on OS
#ifdef __linux__ 
    #define DS "/"
#elif _WIN32
    #define DS "\\"
#else
	#define DS /
#endif
team_t *getTeams(team_t *teams, char *destination){
	//Open file
	FILE *fp = NULL;
	fp = fopen(destination, "r");
	if(fp == NULL){
		return NULL;
	}
	char data[100];
	int i = 1;
	fgets(data,100,fp); //exclude first line
	while(fgets(data,100,fp) != NULL){ //save each line in data variable
		char id[3], isPlayer[2], money[10], score[3], zade[4], khorde[4], count[3]; //some string to put data in
		sscanf(data, "%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]", id, (teams + i - 1)->name, isPlayer, money, score, zade, khorde, count); //scan data with : seprator
		char *ptr = NULL;
		(teams + i - 1)->id = strtol(id,&ptr,10); //save id into struct
		(teams + i - 1)->isPlayer = strtol(isPlayer,&ptr,10); //save isPlayer into struct
		(teams + i - 1)->money = strtol(money,&ptr,10); //save money into struct
		(teams + i - 1)->score = strtol(score,&ptr,10); //save score into struct
		(teams + i - 1)->zade = strtol(zade,&ptr,10); //save goale zade into struct
		(teams + i - 1)->khorde = strtol(khorde,&ptr,10); //save goale khorde into struct
		(teams + i - 1)->count = strtol(count,&ptr,10); //save count into struct
		i++;
	}
	fclose(fp);
	fp = NULL;
	return teams;
}
int getPlayers(player_t **players, char *destination){
	//Open file
	FILE *fp = NULL;
	fp = fopen(destination, "r");
	if(fp == NULL){
		return 0;
	}
	char data[200];
	//count lines
	int line;
	for(line = 0; fgets(data,100,fp) != NULL; line++);
	line--;
	*players = (player_t *)(calloc(line, sizeof(player_t))); //allocate the players in ram
	fclose(fp);
	fp = NULL;
	//reOpen file to save data in a struct
	fp = fopen(destination, "r");
	if(fp == NULL){
		return 0;
	}
	int i = 1;
	fgets(data,100,fp); //exclude first line
	while(fgets(data,100,fp) != NULL){ //save each line in data variable
		char id[3], teamid[3], goal[4], position[2], skill[4], amadegi[4], khastegi[4], rouhiye[4], khoshunat[4]; //some string to put data in
		sscanf(data, "%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]", id, teamid, (*players + i - 1)->name, (*players + i - 1)->lastname, goal, position, skill, amadegi, khastegi, rouhiye, khoshunat); //scan data with : seprator
		char *ptr = NULL;
		(*players + i - 1)->id = strtol(id,&ptr,10); //save id into struct
		(*players + i - 1)->teamid = strtol(teamid,&ptr,10); //save teamid into struct
		(*players + i - 1)->goal = strtol(goal,&ptr,10); //save goal into struct
		(*players + i - 1)->position = strtol(position,&ptr,10); //save position into struct
		(*players + i - 1)->skill = strtol(skill,&ptr,10); //save skill into struct
		(*players + i - 1)->amadegi = strtol(amadegi,&ptr,10); //save amadegi into struct
		(*players + i - 1)->khastegi = strtol(khastegi,&ptr,10); //save khastegi into struct
		(*players + i - 1)->rouhiye = strtol(rouhiye,&ptr,10); //save rouhiye into struct
		(*players + i - 1)->khoshunat = strtol(khoshunat,&ptr,10); //save khoshunat into struct
		i++;
	}
	fclose(fp);
	fp = NULL;
	return line;
}
team_t *getTeamsProfile(team_t *teams){
	char destination[] = "Database" DS "profile" DS "teams";
	return getTeams(teams, destination);
}
team_t *getTeamsDatabase(team_t *teams){
	char destination[] = "Database" DS "teams";
	return getTeams(teams, destination);
}
int getPlayersProfile(player_t **players){
	char destination[] = "Database" DS "profile" DS "players";
	return getPlayers(players, destination);
}
int getPlayersDatabase(player_t **players){
	char destination[] = "Database" DS "players";
	return getPlayers(players, destination);
}
int getGames(game_t **games){
	//Open file
	FILE *fp = NULL;
	char destination[] = "Database" DS "profile" DS "games";
	fp = fopen(destination, "r");
	if(fp == NULL){
		return 0;
	}
	char data[100];
	//count lines
	int line;
	for(line = 0; fgets(data,100,fp) != NULL; line++);
	line--;
	*games = (game_t *)(calloc(line, sizeof(game_t))); //allocate the games in ram
	int i = 1;
	fgets(data,100,fp); //exclude first line
	while(fgets(data,100,fp) != NULL){ //save each line in data variable
		char id[3], idteam1[3], idteam2[3], raftorbargasht[3], week[4]; //some string to put data in
		sscanf(data, "%[^:]:%[^:]:%[^:]:%[^:]:%[^:]", id, idteam1, idteam2, raftorbargasht, week); //scan data with : seprator
		char *ptr = NULL;
		(*games + i - 1)->id = strtol(id,&ptr,10); //save id into struct
		(*games + i - 1)->team1id = strtol(idteam1,&ptr,10); //save idteam1 into struct
		(*games + i - 1)->team2id = strtol(idteam2,&ptr,10); //save idteam2 into struct
		(*games + i - 1)->raftorbargasht = strtol(raftorbargasht,&ptr,10); //save raftorbargasht into struct
		(*games + i - 1)->week = strtol(week,&ptr,10); //save week zade into struct
		i++;
	}
	fclose(fp);
	fp = NULL;
	return line;
}
int saveGames(game_t *games, int size){
	//Open file
	FILE *fp = NULL;
	char destination[] = "Database" DS "profile" DS "games";
	fp = fopen(destination, "w");
	if(fp == NULL){
		return 0;
	}
	char data[100] = "id:team1id:team2id:raftorbargasht:week"; //first row
	for(int i = 0; i < size; i++){ //save each line in file
		fprintf(fp, "%s\n", data);
		sprintf(data, "%d:%d:%d:%d:%d", (games + i)->id, (games + i)->team1id, (games + i)->team2id, (games + i)->raftorbargasht, (games + i)->week);
	}
	fprintf(fp, "%s\n", data); //save the last line
	fclose(fp);
	fp = NULL;
	return 1;
}
int saveTeamsProfile(team_t *teams,int size){
	//Open file
	FILE *fp = NULL;
	char destination[] = "Database" DS "profile" DS "teams";
	fp = fopen(destination, "w");
	if(fp == NULL){
		return 0;
	}
	char data[100] = "id:name:isPlayer:money:score:zade:khorde:count"; //first row
	for(int i = 0; i < size; i++){ //save each line in file
		fprintf(fp, "%s\n", data);
		sprintf(data, "%d:%s:%d:%d:%d:%d:%d:%d", (teams + i)->id, (teams + i)->name, (teams + i)->isPlayer, (teams + i)->money, (teams + i)->score, (teams + i)->zade, (teams + i)->khorde, (teams + i)->count);
	}
	fprintf(fp, "%s\n", data); //save the last line
	fclose(fp);
	fp = NULL;
	return 1;	
}
int savePlayersProfile(player_t *players, int size){
	//Open file
	FILE *fp = NULL;
	char destination[] = "Database" DS "profile" DS "players";
	fp = fopen(destination, "w");
	if(fp == NULL){
		return 0;
	}
	char data[100] = "id:teamid:name:lastname:goal:position:skill:amadegi:khastegi:rouhiye:khoshunat"; //first row
	for(int i = 0; i < size; i++){ //save each line in file
		fprintf(fp, "%s\n", data);
		sprintf(data, "%d:%d:%s:%s:%d:%d:%d:%d:%d:%d:%d", (players + i)->id, (players + i)->teamid, (players + i)->name, (players + i)->lastname, (players + i)->goal, (players + i)->position, (players + i)->skill, (players + i)->amadegi, (players + i)->khastegi, (players + i)->rouhiye, (players + i)->khoshunat);
	}
	fprintf(fp, "%s\n", data); //save the last line
	fclose(fp);
	fp = NULL;
	return 1;	
}