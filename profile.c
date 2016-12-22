/*
* Author : Mahdi Alikhasi
* Description: working with profiles
* Functions::
*		checkProfile: check if there is any profile on computer or not. Return value 0 if there is not any profile and 1 if there is a profile
*		removeAllFileOfDirectory: get a directory and remove all file in that directory. return 1 if successfully deleted. 0 if not
*		clearProfile: Clear all saved data. Return 1 if successfully cleared. Return 0 if not.
*/
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#ifdef __linux__ 
    #define DS "/"
#elif _WIN32
    #define DS "\\"
#else
	#define DS /
#endif

int checkProfile(void){
	FILE *fp = NULL;
	char destination[] = "Database" DS "profile" DS "empty";
	fp = fopen(destination, "r");
	if(fp == NULL){
		return 1;
	}else{
		fclose(fp);
		fp = NULL;
		return 0;
	}
}
int removeAllFileOfDirectory(char const* directory){
	DIR *theFolder = opendir(directory);
    struct dirent *next_file;
    char filepath[256];
    while ( (next_file = readdir(theFolder)) != NULL ){
        // build the path for each file in the folder
        if(strcmp(next_file->d_name , ".") == 0 || strcmp(next_file->d_name , "..") == 0){
        	continue;
        }
        sprintf(filepath, "%s" DS "%s", directory, next_file->d_name);
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
	char destination[] = "Database" DS "profile";
	int status = removeAllFileOfDirectory(destination);
	if(status == 0){
		return 0;
	}
	char destination2[] = "Database" DS "profile" DS "empty";
	fp = fopen(destination2, "w");
	if(fp == NULL){
		return 0;
	}
	fprintf(fp, "%s", "There is no Profile here");
	fclose(fp);
	fp = NULL;
	return 1;
}