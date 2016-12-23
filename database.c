/*
* Author : Mahdi Alikhasi
* Description: working with database. get data and save data.
* Functions::
*	getTeams: get the default teams from database and save it to team_t data structure. return NULL if faild. return pointer if successed.
*/
#include "dataStruct.h"
#include <stdio.h>
#include <stdlib.h>

//make seprator base on OS
#ifdef __linux__ 
    #define DS "/"
#elif _WIN32
    #define DS "\\"
#else
	#define DS /
#endif
team_t *getTeams(team_t *teams){
	//Open file
	FILE *fp = NULL;
	char destination[] = "Database" DS "teams";
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
	return teams;
}