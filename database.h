team_t *getTeamsProfile(team_t *teams);
team_t *getTeamsDatabase(team_t *teams);
int getPlayersProfile(player_t **players);
int getPlayersDatabase(player_t **players);
int saveTeamsProfile(team_t *teams,int size);
int savePlayersProfile(player_t *players, int size);
int getGames(game_t **games);
int saveGames(game_t *games, int size);