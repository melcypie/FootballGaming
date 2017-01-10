/*
* Author : Pegah Khorasani
* Description: 
* Functions:: 
		start: 2 halt bara ye bazi vujud dard, bazi az avval shuru shavd ya kheyr! in tabe shuru e bazi ra az 2 halat Ntekhab mikond
		selectProfileTeam: karbar az 16 ta teame mujud yeki ra be delkhah Ntekhab miknd
		
*		
*/
#include "dataStruct.h"
#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include "controller1.h"
#include "utilities.h"
#include <string.h>
#include "profile.h"

#define CTE 10



void selectProfileTeam(){
	clearPage();
	printf("azizm ye team Ntekhab kon\n");
	team_t teams[16];
	getTeamsProfile(teams);
	printAllTeamsList(teams,16);
	printf("azizm id ye team ro vared kon");
	int teamNo=18;
	while(1){
		scanf("%d" , &teamNo);
		flushBuffer();
		if ( teamNo>16 || teamNo<1 ) {
			printf("faght adade 1 ta 16 ra mishe vared krd\n");
		}else
		break;	
	}
	teams[teamNo - 1].isPlayer=1; //Ntekhabe teame karbar
	saveTeamsProfile(teams ,16);
	
}




void start(){ //sakhte profile
	welcomeFootball();		
	if ( checkProfile()==0){
		printf("azizm inja hich profili vujud nadare! :3\n");
		printf("bara ye sakhte profile kalame ye 'new' ra vared namayid\n");
		char input[10];
		while(1) {
			scanf("%4s" , input);
			flushBuffer();
			if ( strcmp ( input , "new")==0 ){
				createProfile();
				selectProfileTeam();
				break;	
			} else {
				printf("azizm fght mituni 'new' ro vared koni\n");
			}
		}
	}else {
		printf("azizm inja ye profile dari ^__^\n");
		printf("mikhay ye profile jadid dashte bashi ya na?\n");
		printf("bara ye shuru e league jadid kalame ye 'new' ra vared namayin ya bara ye edame ye league ghabli kalame ye 'resume' ra vared namayin\n");
		char input[10];
		while(1){
			scanf("%7s" , input);
			flushBuffer();
			if ( strcmp(input , "new") ==0 ){
				clearProfile();
				createProfile();
				selectProfileTeam();
				break;
			}else if( strcmp(input , "resume")==0){
				break;
			} else {
				printf("azizm ya fght 'new' ro bezn ya 'resume'\n");	
			}
		}
	}	
}




void playGameCC ( int id1 , int id2 , int *goal1 , int *goal2 , player_t *players1 ,int size1, player_t *players2 , int size2 ) {
	
	for (int i=0 ;  i < size1 ; i++ ){
		players1[i].sum= players1[i].amadegi + players1[i].rouhiye/2 -players1[i].khastegi*2 + players1[i].skill;
	}
	for (int j=0 ; j<size2 ; j++){
		players2[j].sum=players2[j].amadegi + players2[j].rouhiye/2 -players2[j].khastegi*2 + players2[j].skill;
	}
	arrangment_t *arrangments;
	int counter= getArrangments(&arrangments);
	int team1_arrangment = randomNo(0 , counter-1);
	int team2_arrangment = randomNo(0 , counter-1);
	
	bubblePlayers( players1, size1,playerSUM);
	bubblePlayers( players2, size2,playerSUM);

	int defa1= arrangments[team1_arrangment].defa;
	int miane1= arrangments[team1_arrangment].miane;
	int hamle1= arrangments[team1_arrangment].hamle;  //123 123 fght pega midune cp
	
	int index_team1[2][11];                 //araye ye 2*11 ke id va positione bazikona ye tu ye zamin tushe
	int counter2 = 0;
	
	for ( int k=0 ; k<size1 ; k++ ){
		if ( players1[k].position == 4){
			index_team1[0][counter2] = k;
			index_team1[1][counter2] = 4;
			counter2++;
		}
	}
	    //123 123 vase hamle o miane ham benevis hamino (fght pega midune)
	for ( ; defa1>0 ; defa1-- ){
		for ( int k=0 ; k<size1 ; k++ ){
			if (players1[k].position==3 ){
				index_team1[0][counter2] = k;
				index_team1[1][counter2] = 3;
				counter2++;
			}
		}
	}
	
	// 123 123 vase teame 2 hamina ro benevis ( fght pega midune)
	// 123 123 halati ke bazikon kam darim neveshte nashode  ( pega va mahdi know)
	
	
	
	int sumDefaTeam1=0;
	int sumMianeTeam1=0;
	for ( int i=0 ; i<11 ; i++){
		if ( index_team1[1][i]==3 ){
			if ( players1[index_team1[0][i]].position==3)
				sumDefaTeam1 += players1[index_team1[0][i]].sum;
			else if(players1[index_team1[0][i]].position==1)
				sumDefaTeam1 += players1[index_team1[0][i]].sum * 7 /10 ;
			else if(players1[index_team1[0][i]].position==2)
				sumDefaTeam1 += players1[index_team1[0][i]].sum * 9 / 10;
			else if(players1[index_team1[0][i]].position==4)
				sumDefaTeam1 += players1[index_team1[0][i]].sum /2;//in else if ha baa ye vaghtian ke bazikon dar mogheEyataesh gharar nagire
				
		}else if ( index_team1[1][i]==4 ) {  //in else if ha bara ye position ha ye bazikon haye tu ye zamine
			sumDefaTeam1 += players1[index_team1[0][i]].sum * 2;
		}else if(index_team1[1][i]==2){
			sumMianeTeam1 += players1[index_team1[0][i]].sum;
		}else if // 123 123 hamle miane
		
	}
	sumDefaTeam1+=sumMianeTeam1/2;
	sumHamleTeam1+=sumMianeTeam1/2;
	//123 123 tabe random ro farakhani kon ye adade random beyne 0 ta 100 bara ye ar team dar nazar migiri bad defa o hamle ye har teamo dar random/100 zarb mikoni
	
	
	// 123 123 in kara ro vase hamle o  teame 2 benevis ( pegah midune)
	
	
	if ( sumHamleTeam1 > sumDefaTeam2){ //123 123 farz kon ye tabe neveshte goalAssign alan farahani mikoni
		goalAssign((sumHamleTeam1 - sumDefaTeam2) / CTE);
		*goal1=(sumHamleTeam1 - sumDefaTeam2) / CTE ;
	}

	if ( sumHamleTeam2 > sumDefaTeam1) {
		goalAssign((sumHamleTeam2 - sumDefaTeam1) / CTE);
		*goal1=(sumHamleTeam2 - sumDefaTeam1) / CTE ;		
	}
	
	// 123 123 updatae kon niro ye playera ro ( chon tulanian badn minevisi)
	//123 123 update kone 3 emtiaz ezafe kone be teame bbarande tedad goala ye zade va khorde hm update kon va tedad bazia hm update kone
	
	
}












