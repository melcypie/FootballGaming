/*
* Author : Mahdi Alikhasi
* Description: working with database. get data and save data.
* Functions::
*		getTeams: get the teams from destination (Arguman) and save it to team_t data structure. return NULL if faild. return pointer if successed.
*		getTeamsProfile : Send profile destination address to getTeams
*		getTeamsDatabase: Send Database destination address to getTeams
*		saveTeamsProfile: Save current Teams data into profile. return 1 if successed and 0 if not
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
		char id[3], isPlayer[2], money[10]; //some string to put data in
		sscanf(data, "%[^:]:%[^:]:%[^:]:%[^:]", id, (teams + i - 1)->name, isPlayer, money); //scan data with : seprator
		char *ptr = NULL;
		(teams + i - 1)->id = strtol(id,&ptr,10); //save id into struct
		(teams + i - 1)->isPlayer = strtol(isPlayer,&ptr,10); //save isPlayer into struct
		(teams + i - 1)->money = strtol(money,&ptr,10); //save money into struct
		i++;
	}
	fclose(fp);
	fp = NULL;
	return teams;
}
team_t *getTeamsProfile(team_t *teams){
	char destination[] = "Database" DS "profile" DS "teams";
	return getTeams(teams, destination);
}
team_t *getTeamsDatabase(team_t *teams){
	char destination[] = "Database" DS "teams";
	return getTeams(teams, destination);
}
int saveTeamsProfile(team_t *teams,int size){
	//Open file
	FILE *fp = NULL;
	char destination[] = "Database" DS "profile" DS "teams";
	fp = fopen(destination, "w");
	if(fp == NULL){
		return 0;
	}
	char data[100] = "id:name:isPlayer:money"; //first row
	for(int i = 0; i < size; i++){ //save each line in file
		fprintf(fp, "%s\n", data);
		sprintf(data, "%d:%s:%d:%d", (teams + i)->id, (teams + i)->name, (teams + i)->isPlayer, (teams + i)->money);
	}
	fprintf(fp, "%s\n", data); //save the last line
	fclose(fp);
	fp = NULL;
	return 1;	
}