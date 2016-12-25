//I use include guards to avoid twice defenition and errors
#ifndef DATA_H
#define DATA_H
	#ifdef __linux__ 
	    #define BLUE "\x1b[34m"
		#define RESET "\x1b[0m"
	#elif _WIN32
	    #define BLUE ""
		#define RESET ""
	#else
		#define BLUE "\x1b[34m"
		#define RESET "\x1b[0m"
	#endif

struct team {
    int id;
    char name[100];
    int isPlayer;
    int money;
    int score;
    int zade;
    int khorde;
    int count;
};
enum teamField{
    teamID = 1,
    teamNAME,
    teamISPLAYER,
    teamMONEY,
    teamSCORE,
    teamZADE,
    teamKHORDE,
    teamCOUNT	
};
struct game {
	int id;
	int team1id;
	int team2id;
	int raftorbargasht;
	int week;
};

struct natayej{
	int gameid;
	int team1goal;
	int team2goal;
};

struct goal{
	int gameid;
	int playerid;
};

struct player{
	int id;
	int teamid;
	char name[50];
	char lastname[50];
	int goal;
	int position;
	int skill;
	int amadegi;
	int khastegi;
	int rouhiye;
	int khoshunat;
	int sum;
};
enum playerField{
	playerID = 1,
	playerTEAMID,
	playerNAME,
	playerLASTNAME,
	playerGOAL,
	playerPOSITION,
	playerSKILL,
	playerAMADEGI,
	playerKHASTEGI,
	playerROUHIYE,
	playerKHOSHUNAT,
	playerSUM
};
typedef struct team team_t;
typedef struct game game_t;
typedef struct natayej natayej_t;
typedef struct goal goal_t;
typedef struct player player_t;
#endif 