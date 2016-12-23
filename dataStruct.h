//I use include guards to avoid twice defenition and errors
#ifndef DATA_H
#define DATA_H

struct team {
    int id;
    char name[100];
    int isPlayer;
    int money;
};

typedef struct team team_t;

#endif 