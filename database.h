team_t *getTeamsProfile(team_t *teams);
int getPlayersProfile(player_t **players);
int saveTeamsProfile(team_t *teams,int size);
int savePlayersProfile(player_t *players, int size);
int saveGamesProfile(game_t *games, int size);
int getNatayej(natayej_t **natayej);
int saveAllNatayejProfile(natayej_t *natayej, int size);
int getGames(game_t **games);
void createProfile();