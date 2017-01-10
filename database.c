/*
* Author : Mahdi Alikhasi
* Description: working with database. get data and save data.
* Functions::
*		getPlayersProfile: get the list of player from saved profile and put it into struct. argument: the address of pointer that will assign to the first player. return number of player that can get.
*		getTeamsProfile : Get team list from saved Profile. return pointer to team_t (the first of array)
*		createTeamsProfile: get the team list from default database and save it to profile directory.
*		createPlayersProfile: get the default player list from default database and save it in the profile directory.
*		saveTeamsProfile: Save current Teams data into profile. return 1 if succeed and 0 if not
*		savePlayersProfile: Save current players data into profile. return 1 if succeed and 0 if not
*		getGames : get the game list. Arguman pointer to pointer. return number of games if succeed. 0 if not
*		saveGamesProfile : Save games list into profile. return 1 if succeed or 0 if not.
*		getNatayej : get the natayej list. Arguman pointer to pointer. return number of natayej if succeed. 0 if not
*		saveAllNatayejProfile : Save the Natayej list into profile. return 1 if succeed or 0 if not
*		addNatayejProfile : apppend an aaray of natayej to the end of Natayej file on profile directory
*		removeEmptyFile: Remove the 'empty' file from profile directory
*		createProfile : if there is not a profile file on profile directory, create one.
*/
#include "dataStruct.h"
#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include "utilities.h"
#include <string.h>
team_t *getTeamsProfile(team_t *teams){
	//Open file
	char destination[] = "Database/profile/teams";
	FILE *fp = NULL;
	fp = fopen(destination, "r");
	if(fp == NULL){
		return NULL;
	}
	char data[100];
	fgets(data,100,fp); //exclude first line
	for(int i = 0;fgets(data,100,fp) != NULL;i++){ //save each line in data variable
		char id[3], isPlayer[2], money[10], score[3], zade[4], khorde[4], count[3]; //some string to put data in
		sscanf(data, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", id, (teams + i)->name, isPlayer, money, score, zade, khorde, count); //scan data with : seprator
		char *ptr = NULL;
		(teams + i)->id = strtol(id,&ptr,10); //save id into struct
		(teams + i)->isPlayer = strtol(isPlayer,&ptr,10); //save isPlayer into struct
		(teams + i)->money = strtol(money,&ptr,10); //save money into struct
		(teams + i)->score = strtol(score,&ptr,10); //save score into struct
		(teams + i)->zade = strtol(zade,&ptr,10); //save goale zade into struct
		(teams + i)->khorde = strtol(khorde,&ptr,10); //save goale khorde into struct
		(teams + i)->count = strtol(count,&ptr,10); //save count into struct
	}
	fclose(fp);
	fp = NULL;
	return teams;
}
int getPlayersProfile(player_t **players){
	//Open file
	char destination[] = "Database/profile/players";
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
	rewind(fp);
	fgets(data,100,fp); //exclude first line
	for(int i = 0;fgets(data,100,fp) != NULL;i++){ //save each line in data variable
		char id[3], sen[3], shomare[3], teamid[3], goal[4], position[2], skill[4], amadegi[4], khastegi[4], rouhiye[4], khoshunat[4]; //some string to put data in
		sscanf(data, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", id, teamid, shomare, (*players + i)->name, sen, goal, position, skill, amadegi, khastegi, rouhiye, khoshunat); //scan data with : seprator
		char *ptr = NULL;
		(*players + i)->id = strtol(id,&ptr,10); //save id into struct
		(*players + i)->teamid = strtol(teamid,&ptr,10); //save teamid into struct
		(*players + i)->shomare = strtol(shomare, &ptr, 10); //save shomare into struct
		(*players + i)->sen = strtol(sen, &ptr, 10); //save sen to struct
		(*players + i)->goal = strtol(goal,&ptr,10); //save goal into struct
		(*players + i)->position = strtol(position,&ptr,10); //save position into struct
		(*players + i)->skill = strtol(skill,&ptr,10); //save skill into struct
		(*players + i)->amadegi = strtol(amadegi,&ptr,10); //save amadegi into struct
		(*players + i)->khastegi = strtol(khastegi,&ptr,10); //save khastegi into struct
		(*players + i)->rouhiye = strtol(rouhiye,&ptr,10); //save rouhiye into struct
		(*players + i)->khoshunat = strtol(khoshunat,&ptr,10); //save khoshunat into struct
	}
	fclose(fp);
	fp = NULL;
	return line;
}
int createTeamsProfile(void){
	team_t teams[16];
	//Open file
	char destination[] = "Database/teams.csv";
	FILE *fp = NULL;
	fp = fopen(destination, "r");
	if(fp == NULL){
		return 0;
	}
	char data[100];
	int i = 0;
	for(;fgets(data,100,fp) != NULL;i++){ //save each line in data variable
		sscanf(data, "%[^\n]", (teams + i)->name); //scan data
		(teams + i)->id = i + 1; //save id into struct
		(teams + i)->isPlayer = 0; //save isPlayer into struct
		(teams + i)->money = randomNo(100000,500000); //save money into struct
		(teams + i)->score = 0; //save score into struct
		(teams + i)->zade = 0; //save goale zade into struct
		(teams + i)->khorde = 0; //save goale khorde into struct
		(teams + i)->count = 0; //save count into struct
	}
	fclose(fp);
	fp = NULL;
	return (saveTeamsProfile(teams,i));
}
int createPlayersProfile(void){
	team_t teams[16];
	//Get teams from saved profile
	getTeamsProfile(teams);
	for(int i = 0; i < 16; i++){
		for(int j = 0; (teams + i)->name[j] != 0; j++){ //Remove Space
			if((teams + i)->name[j] == ' '){
				(teams + i)->name[j] = (teams + i)->name[j + 1];
				if((teams + i)->name[j + 1] != 0){
					(teams + i)->name[j + 1] = ' ';
				}
			}
		}
	}
	char data[200] = "id,teamid,shomare,name,sen,goal,position,skill,amadegi,khastegi,rouhiye,khoshunat"; //first row
	//Open file
	char destination3[] = "Database/profile/players"; //Save players
	FILE *fp = NULL;
	fp = fopen(destination3, "w");
	if(fp == NULL){
		return 0;
	}
	fprintf(fp, "%s\n", data);
	fclose(fp);
	fp = NULL;
	int player_id = 1;
	for(int i = 0;i < 16; i++, player_id++){
		//Open file
		char destination[200];
		sprintf(destination, "Database/%s.csv", (teams + i)->name);
		fp = fopen(destination, "r");
		if(fp == NULL){
			return 0;
		}
		char data[200];
		//count lines
		int line;
		for(line = 0; fgets(data,100,fp) != NULL; line++);
		player_t *players = NULL;
		players = (player_t *)(calloc(line, sizeof(player_t))); //allocate the players in ram
		rewind(fp);
		for(int j = 0;fgets(data,100,fp) != NULL;j++, player_id++){ //save each line in data variable
			char sen[3], shomare[3], position[2]; //some string to put data in
			sscanf(data, "%[^,],%[^,],%[^:]:%[^,]", shomare, (players + j)->name, sen, position); //scan data with : seprator
			char *ptr = NULL;
			(players + j)->id = player_id; //save id into struct
			(players + j)->teamid = (teams + i)->id; //save teamid into struct
			(players + j)->goal = 0; //save goal into struct
			(players + j)->position = (position[0] == 'G' ? 4 : (position[0] == 'D' ? 3 : (position[0] == 'M' ? 2 : 1))); //save position into struct
			(players + j)->skill = randomNo(40, 100); //save skill into struct
			(players + j)->amadegi = randomNo(40, 100); //save amadegi into struct
			(players + j)->khastegi = randomNo(0, 40); //save khastegi into struct
			(players + j)->rouhiye = randomNo(40, 100); //save rouhiye into struct
			(players + j)->khoshunat = randomNo(0, 50); //save khoshunat into struct
			(players + j)->shomare = strtol(shomare,&ptr,10);
			(players + j)->sen = strtol(sen,&ptr,10);
		}
		fclose(fp);
		fp = NULL;
		//Add players at the end of file
		//Open file
		fp = fopen(destination3, "a");
		if(fp == NULL){
			return 0;
		}
		for(int i = 0; i < line; i++){ //save each line in file
			sprintf(data, "%d,%d,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d", (players + i)->id, (players + i)->teamid, (players + i)->shomare, (players + i)->name, (players + i)->sen, (players + i)->goal, (players + i)->position, (players + i)->skill, (players + i)->amadegi, (players + i)->khastegi, (players + i)->rouhiye, (players + i)->khoshunat);
			fprintf(fp, "%s\n", data);
		}
		fclose(fp);
		fp = NULL;
		players = NULL;
	}
	return 1;
}
int getGames(game_t **games){
	//Open file
	FILE *fp = NULL;
	char destination[] = "Database/profile/games";
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
	rewind(fp);
	int i = 1;
	fgets(data,100,fp); //exclude first line
	while(fgets(data,100,fp) != NULL){ //save each line in data variable
		char id[3], idteam1[3], idteam2[3], week[4]; //some string to put data in
		sscanf(data, "%[^,],%[^,],%[^,],%[^,]", id, idteam1, idteam2, week); //scan data with , seprator
		char *ptr = NULL;
		(*games + i - 1)->id = strtol(id,&ptr,10); //save id into struct
		(*games + i - 1)->team1id = strtol(idteam1,&ptr,10); //save idteam1 into struct
		(*games + i - 1)->team2id = strtol(idteam2,&ptr,10); //save idteam2 into struct
		(*games + i - 1)->week = strtol(week,&ptr,10); //save week zade into struct
		i++;
	}
	fclose(fp);
	fp = NULL;
	return line;
}
int getArrangments(arrangment_t **arrangments){
	//Open file
	FILE *fp = NULL;
	char destination[] = "Database/arrangment";
	fp = fopen(destination, "r");
	if(fp == NULL){
		return 0;
	}
	char data[100];
	//count lines
	int line;
	for(line = 0; fgets(data,100,fp) != NULL; line++);
	line--;
	*arrangments = (arrangment_t *)(calloc(line, sizeof(arrangment_t))); //allocate the games in ram
	rewind(fp);
	int i = 0;
	fgets(data,100,fp); //exclude first line
	while(fgets(data,100,fp) != NULL){ //save each line in data variable
		char defa[2],miane[2],hamle[2]; //some string to put data in
		sscanf(data, "%[^,],%[^,],%[^,]", defa, miane, hamle); //scan data with , seprator
		char *ptr = NULL;
		(*arrangments + i)->defa = strtol(defa,&ptr,10);
		(*arrangments + i)->miane = strtol(miane,&ptr,10); 
		(*arrangments + i)->hamle = strtol(hamle,&ptr,10); 
		i++;
	}
	fclose(fp);
	fp = NULL;
	return line;
}
int getNatayej(natayej_t **natayej){
	//Open file
	FILE *fp = NULL;
	char destination[] = "Database/profile/natayej";
	fp = fopen(destination, "r");
	if(fp == NULL){
		return 0;
	}
	char data[100];
	//count lines
	int line;
	for(line = 0; fgets(data,100,fp) != NULL; line++);
	line--;
	*natayej = (natayej_t *)(calloc(line, sizeof(natayej_t))); //allocate the games in ram
	rewind(fp);
	int i = 1;
	fgets(data,100,fp); //exclude first line
	while(fgets(data,100,fp) != NULL){ //save each line in data variable
		char gameid[3], team1goal[3], team2goal[3]; //some string to put data in
		sscanf(data, "%[^,],%[^,],%[^,]", gameid, team1goal, team2goal); //scan data with : seprator
		char *ptr = NULL;
		(*natayej + i - 1)->gameid = strtol(gameid,&ptr,10); //save gameid into struct
		(*natayej + i - 1)->team1goal = strtol(team1goal,&ptr,10); //save team1goal into struct
		(*natayej + i - 1)->team2goal = strtol(team2goal,&ptr,10); //save team2goal into struct
		i++;
	}
	fclose(fp);
	fp = NULL;
	return line;
}
int saveAllNatayejProfile(natayej_t *natayej, int size){
	//Open file
	FILE *fp = NULL;
	char destination[] = "Database/profile/natayej";
	fp = fopen(destination, "w");
	if(fp == NULL){
		return 0;
	}
	char data[100] = "gameid,team1goal,team2goal"; //first row
	for(int i = 0; i < size; i++){ //save each line in file
		fprintf(fp, "%s\n", data);
		sprintf(data, "%d,%d,%d", (natayej + i)->gameid, (natayej + i)->team1goal, (natayej + i)->team2goal);
	}
	fprintf(fp, "%s\n", data); //save the last line
	fclose(fp);
	fp = NULL;
	return 1;
}
int saveGamesProfile(game_t *games, int size){
	//Open file
	FILE *fp = NULL;
	char destination[] = "Database/profile/games";
	fp = fopen(destination, "w");
	if(fp == NULL){
		return 0;
	}
	char data[100] = "id,team1id,team2id,week"; //first row
	for(int i = 0; i < size; i++){ //save each line in file
		fprintf(fp, "%s\n", data);
		sprintf(data, "%d,%d,%d,%d", (games + i)->id, (games + i)->team1id, (games + i)->team2id, (games + i)->week);
	}
	fprintf(fp, "%s\n", data); //save the last line
	fclose(fp);
	fp = NULL;
	return 1;
}
int saveTeamsProfile(team_t *teams,int size){
	//Open file
	FILE *fp = NULL;
	char destination[] = "Database/profile/teams";
	fp = fopen(destination, "w");
	if(fp == NULL){
		return 0;
	}
	char data[100] = "id,name,isPlayer,money,score,zade,khorde,count"; //first row
	for(int i = 0; i < size; i++){ //save each line in file
		fprintf(fp, "%s\n", data);
		sprintf(data, "%d,%s,%d,%d,%d,%d,%d,%d", (teams + i)->id, (teams + i)->name, (teams + i)->isPlayer, (teams + i)->money, (teams + i)->score, (teams + i)->zade, (teams + i)->khorde, (teams + i)->count);
	}
	fprintf(fp, "%s\n", data); //save the last line
	fclose(fp);
	fp = NULL;
	return 1;	
}
int savePlayersProfile(player_t *players, int size){
	//Open file
	FILE *fp = NULL;
	char destination[] = "Database/profile/players";
	fp = fopen(destination, "w");
	if(fp == NULL){
		return 0;
	}
	char data[100] = "id,teamid,shomare,name,sen,goal,position,skill,amadegi,khastegi,rouhiye,khoshunat"; //first row
	for(int i = 0; i < size; i++){ //save each line in file
		fprintf(fp, "%s\n", data);
		sprintf(data, "%d,%d,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d", (players + i)->id, (players + i)->teamid, (players + i)->shomare, (players + i)->name, (players + i)->sen, (players + i)->goal, (players + i)->position, (players + i)->skill, (players + i)->amadegi, (players + i)->khastegi, (players + i)->rouhiye, (players + i)->khoshunat);
	}
	fprintf(fp, "%s\n", data); //save the last line
	fclose(fp);
	fp = NULL;
	return 1;	
}
int addNatayejProfile(natayej_t *natayej, int size){
	//Open file
	FILE *fp = NULL;
	char destination[] = "Database/profile/natayej";
	fp = fopen(destination, "a");
	if(fp == NULL){
		return 0;
	}
	char data[100];
	for(int i = 0; i < size; i++){ //save each line in file
		sprintf(data, "%d,%d,%d", (natayej + i)->gameid, (natayej + i)->team1goal, (natayej + i)->team2goal);
		fprintf(fp, "%s\n", data);
	}
	fclose(fp);
	fp = NULL;
	return 1;
}
void removeEmptyFile(void){
	char destination[] = "Database/profile/empty";//remove empty file
	int ret = remove(destination);
}
void createProfile(){
	removeEmptyFile(); //remove empty file
	createTeamsProfile(); //Save team list
	createPlayersProfile(); //Save all players
	natayej_t natije;
	saveAllNatayejProfile(&natije, 0); //Create a Natayej file with the headers...
}