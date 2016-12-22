/*
* Author : Mahdi Alikhasi
* Description: working with profiles
* Functions::
*		checkProfile: check if there is any profile on computer or not. Return value 0 if there is not any profile and 1 if there is a profile
*/
#include <stdio.h>

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
	printf("%s\n", destination);
	if(fp == NULL){
		return 1;
	}else{
		return 0;
	}
}