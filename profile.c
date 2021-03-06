/*
* Author : Mahdi Alikhasi
* Description: working with profiles
* Functions::
*		checkProfile: 
*		removeAllFileOfDirectory: 
*		clearProfile: 
*		saveProfile: 
*/

#include "dataStruct.h"
#include "database.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "profile.h"


int checkProfile(void){
	FILE *fp = NULL;
	char destination[] = "Database/profile/empty"; //if there is empty file in the directory, that means the directory is empty and there is not any profile saved on computer 
	fp = fopen(destination, "r");
	if(fp == NULL){ //if there is not empty file, it means the profile is saved on directory
		return 1;
	}else{
		fclose(fp);
		fp = NULL;
		return 0;
	}
}
int removeAllFileOfDirectory(char const* directory){
	DIR *theFolder = opendir(directory); //get the directory that we want to remove files
    struct dirent *next_file;
    char filepath[256];
    while ( (next_file = readdir(theFolder)) != NULL ){
        // build the path for each file in the folder
        if(strcmp(next_file->d_name , ".") == 0 || strcmp(next_file->d_name , "..") == 0){ //exclude . and .. directory in linux
        	continue;
        }
        sprintf(filepath, "%s/%s", directory, next_file->d_name);
        int ret = remove(filepath);
        if(ret != 0){
        	return 0;
        }
    }
    closedir(theFolder);
    return 1;
}
int clearProfile(void){
	FILE *fp = NULL;
	char destination[] = "Database/profile";
	int status = removeAllFileOfDirectory(destination); //clear all data and profile
	if(status == 0){
		return 0;
	}
	char destination2[] = "Database/profile/empty";
	fp = fopen(destination2, "w"); //create empty file
	if(fp == NULL){
		return 0;
	}
	fprintf(fp, "%s", "There is no Profile here");
	fclose(fp);
	fp = NULL;
	return 1;
}

int saveProfile(team_t *teams, int team_size, player_t *players, int player_size, game_t *games, int game_size, natayej_t *natayej, int natayej_size){
	char destination[] = "Database/profile/empty";//remove empty file
	int ret = remove(destination);
    if(ret != 0){
       	return 0;
    }
	if(saveTeamsProfile(teams,team_size) == 0){ //Save teams
		return 0;
	}
	if(savePlayersProfile(players, player_size) == 0){ //save players
		return 0;
	}
	if(saveGamesProfile(games, game_size) == 0){ //save players
		return 0;
	}
	if(saveAllNatayejProfile(natayej, natayej_size) == 0){
		return 0;
	}
	return 1;
}