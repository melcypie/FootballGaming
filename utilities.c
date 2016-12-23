/*
* Author : Mahdi Alikhasi
* Description: some utilities that will need in the program like clearing page, printing data and so on
* Functions::
*		clearPage: clear the entire page using shell built in functions
*/
#include "dataStruct.h"
#include <stdlib.h>
#include "utilities.h"

void clearPage(){
	#ifdef __linux__ 
    	system("clear");
	#elif _WIN32
    	system("cls");
	#else
		system("clear")
	#endif
}