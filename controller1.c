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
#include "controller2.h"
#include "utilities.h"
#include <string.h>
#include "profile.h"
#define CTE 100

extern int index_p[2][11];

void selectProfileTeam(){
	clearPage();
	printf("azizm ye team Ntekhab kon\n");
	team_t teams[16];
	getTeamsProfile(teams);
	printAllTeamsList(teams,16);
	printf("azizm id ye team ro vared kon\n");
	int teamNo = 18;
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
	//welcomeFootball();		
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
				lineup();
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
				lineup();
				break;
			}else if( strcmp(input , "resume")==0){
				getIndex(index_p);
				break;
			} else {
				printf("azizm ya fght 'new' ro bezn ya 'resume'\n");	
			}
		}
	}	
}

void playGameCC ( team_t *team1 , team_t *team2 , int *goal1 , int *goal2 , player_t *players1 ,int size1, player_t *players2 , int size2 ) {
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

	int defa1= arrangments[team1_arrangment].defa; //tedad defa ra moshakhas mikond
	int miane1= arrangments[team1_arrangment].miane;
	int hamle1= arrangments[team1_arrangment].hamle;  
	
	int index_team1[2][11]; //araye ye 2*11 ke id va positione bazikona ye tu ye zamin tushe
	int counter2 = 0; //vase shomare khuna ha ye index_team1
	int darvazeban1 = 1; //mikhaym bedunim hatmn darvazeban darim ya na
	// for ha ro vase neveshtm ke khune haye index_team1 ro por kone va mshakhas kone ke shomare ye khune ha ye position ha ye mokhtalef chian

	for ( int k = size1 - 1 ; k >= 0 && counter2 == 0; k-- ){
		if ( players1[k].position == 4){
			index_team1[0][counter2] = k;
			index_team1[1][counter2] = 4;
			counter2++;
		}
	}
	if (counter2 == 0 ){
		darvazeban1=0 ;
	} 
	  
	
	for ( int k=size1-1 ; k >= 0 && defa1 > 0; k-- ){
		if (players1[k].position==3 ){
			index_team1[0][counter2] = k;
			index_team1[1][counter2] = 3;
			counter2++;
			defa1--;
		}
	}
	
	
	for ( int k=size1-1; k>=0 && hamle1 > 0; k-- ){
		if (players1[k].position==1 ){
			index_team1[0][counter2] = k;
			index_team1[1][counter2] = 1;
			counter2++;
			hamle1--;
		}
	}
	
	
	for ( int k=size1-1 ; k>=0 && miane1>0 ; k-- ){
		if (players1[k].position==2 ){
			index_team1[0][counter2] = k;
			index_team1[1][counter2] = 2;
			counter2++;
			miane1--;
		}
	}

	if ( defa1 !=0 ) {
		for (  int k=size1-1 ; k >= 0 && defa1 > 0; k-- ){
			for ( int i=0 ; i < counter2 ; i++){
				if ( k == index_team1 [0][i] )
					break;
				else if (i == counter2 -1 ){
					index_team1[0][counter2]=k;
					index_team1[1][counter2]=3;
					counter2++;
					defa1--;
				}
			}
		}
	}
	
	if ( hamle1 !=0 ) {
		for (  int k=size1-1 ; k >= 0 && hamle1 > 0; k-- ){
			for ( int i=0 ; i < counter2 ; i++){
				if ( k == index_team1 [0][i] )
					break;
				else if (i == counter2 -1 ){
					index_team1[0][counter2]=k;
					index_team1[1][counter2]=1;
					counter2++;
					hamle1--;
				}
			}
		}
	}	
	
	if ( miane1 !=0 ) {
		for (  int k=size1-1 ; k >= 0 && miane1 > 0; k-- ){
			for ( int i=0 ; i < counter2 ; i++){
				if ( k == index_team1 [0][i] )
					break;
				else if (i == counter2 -1 ){
					index_team1[0][counter2]=k;
					index_team1[1][counter2]=2;
					counter2++;
					miane1--;
				}
			}
		}
	}	

	if ( darvazeban1==0 ) {
		for (  int k=size1-1 ; k >= 0 && darvazeban1!=0 ; k-- ){
			for ( int i=0 ; i < counter2 ; i++){
				if ( k == index_team1 [0][i] )
					break;
				else if (i == counter2 -1 ){
					index_team1[0][counter2]=k;
					index_team1[1][counter2]=4;
					counter2++;
					darvazeban1++;
				}
			}
		}
	}
	//if darvazeban == 0 ==> darvazeban nadarim. if defa1 != 0 == > be defa bishtar niaz darim and so on	
	
	// hamin karo vase team2 anjam midm
	int defa2= arrangments[team2_arrangment].defa;
	int miane2= arrangments[team2_arrangment].miane;
	int hamle2= arrangments[team2_arrangment].hamle;  
	
	int index_team2[2][11];                 
	int counter3 = 0;
	int darvazeban2 = 1;
	
	for ( int k=size2-1 ; k >= 0 && counter3 == 0; k-- ){
		if ( players2[k].position == 4){
			index_team2[0][counter3] = k;
			index_team2[1][counter3] = 4;
			counter3++;
		}
	}
	if (counter3 == 0 ){
		darvazeban2 = 0 ;
	} 
	    
	    
	for ( int k=size2-1 ; k>=0 && defa2>0 ; k-- ){
		if (players2[k].position==3 ){
			index_team2[0][counter3] = k;
			index_team2[1][counter3] = 3;
			counter3++;
			defa2--;
		}
	}
	
	for ( int k=size2-1 ; k>=0 && hamle2>0 ; k-- ){
		if (players2[k].position==1 ){
			index_team2[0][counter3] = k;
			index_team2[1][counter3] = 1;
			counter3++;
			hamle2--;
		}
	}
	
	

	for ( int k=size2-1 ; k>=0 && miane2>0 ; k-- ){
		if (players2[k].position==2 ){
			index_team2[0][counter3] = k;
			index_team2[1][counter3] = 2;
			counter3++;
			miane2--;
		}
	}


	if ( defa2 !=0 ) {
		for (  int k=size2-1 ; k >= 0 && defa2 > 0; k-- ){
			for ( int i=0 ; i < counter3 ; i++){
				if ( k == index_team2 [0][i] )
					break;
				else if (i == counter3 -1 ){
					index_team2[0][counter3]=k;
					index_team2[1][counter3]=3;
					counter3++;
					defa2--;
				}
			}
		}
	}
	
	
	if ( hamle2 !=0 ) {
		for (  int k=size2-1 ; k >= 0 && hamle2 > 0; k-- ){
			for ( int i=0 ; i < counter3 ; i++){
				if ( k == index_team2 [0][i] )
					break;
				else if (i == counter3 -1 ){
					index_team2[0][counter3]=k;
					index_team2[1][counter3]=1;
					counter3++;
					hamle2--;
				}
			}
		}
	}	
	
	
	if ( miane2 !=0 ) {
		for (  int k=size2-1 ; k >= 0 && miane2 > 0; k-- ){
			for ( int i=0 ; i < counter3 ; i++){
				if ( k == index_team2 [0][i] )
					break;
				else if (i == counter2 -1 ){
					index_team2[0][counter3]=k;
					index_team2[1][counter3]=2;
					counter3++;
					miane2--;
				}
			}
		}
	}	


	if ( darvazeban2==0 ) {
		for (  int k=size2-1 ; k >= 0 && darvazeban2!=0 ; k-- ){
			for ( int i=0 ; i < counter3 ; i++){
				if ( k == index_team2 [0][i] )
					break;
				else if (i == counter3 -1 ){
					index_team2[0][counter3]=k;
					index_team2[1][counter3]=4;
					counter3++;
					darvazeban2++;
				}
			}
		}
	}
	
	int sumDefaTeam1 = 0;
	int sumMianeTeam1 = 0;
	int sumHamleTeam1 = 0;
	for ( int i=0 ; i < 11 ; i++){
		if ( index_team1[1][i]==3 ){
			if ( players1[index_team1[0][i]].position==3)
				sumDefaTeam1 += players1[index_team1[0][i]].sum;
			else if(players1[index_team1[0][i]].position==1)
				sumDefaTeam1 += players1[index_team1[0][i]].sum * 7 /10 ;
			else if(players1[index_team1[0][i]].position==2)
				sumDefaTeam1 += players1[index_team1[0][i]].sum * 9 / 10;
			else if(players1[index_team1[0][i]].position==4)
				sumDefaTeam1 += players1[index_team1[0][i]].sum /2;//in else if ha bara ye vaghtian ke bazikon dar mogheEyataesh gharar nagire
							
		}else if ( index_team1[1][i]==4 ) {  //in else if ha bara ye position ha ye bazikon haye tu ye zamine
			if ( players1[index_team1[0][i]].position==4)
				sumDefaTeam1 += players1[index_team1[0][i]].sum * 2;
			else
				sumDefaTeam1 += players1[index_team1[0][i]].sum;
			
		}else if ( index_team1[1][i]==2 ){
			if ( players1[index_team1[0][i]].position==2)
				sumMianeTeam1 += players1[index_team1[0][i]].sum;
			else if(players1[index_team1[0][i]].position==1)
				sumDefaTeam1 += players1[index_team1[0][i]].sum * 9 /10 ;
			else if(players1[index_team1[0][i]].position==3)
				sumDefaTeam1 += players1[index_team1[0][i]].sum * 9 / 10;
			else if(players1[index_team1[0][i]].position==4)
				sumDefaTeam1 += players1[index_team1[0][i]].sum /2;                     
		}else if ( index_team1[1][i]==1 ){
			if ( players1[index_team1[0][i]].position==1)
				sumHamleTeam1 += players1[index_team1[0][i]].sum;
			else if(players1[index_team1[0][i]].position==2)
				sumHamleTeam1 += players1[index_team1[0][i]].sum * 9 /10 ;
			else if(players1[index_team1[0][i]].position==3)
				sumHamleTeam1 += players1[index_team1[0][i]].sum * 7 / 10;
			else if(players1[index_team1[0][i]].position==4)
				sumHamleTeam1 += players1[index_team1[0][i]].sum /2;                     
		}		
	}
	sumDefaTeam1 +=sumMianeTeam1/2; //chon miane hich ahamiati tu goal nadare khodesh be tanhayi bhsh moteghayere sum  nemidim
	sumHamleTeam1 +=sumMianeTeam1/2;
	int team1ZaribKhata=randomNo(0,100);
	
	//tabe random ro farakhani kon ye adade random beyne 0 ta 100 bara ye ar team dar nazar migiri bad defa o hamle ye har teamo dar random/100 zarb mikoni ta ehtemale borde hame ye team ha vujud dashte bashe
	sumHamleTeam1 =sumHamleTeam1 * team1ZaribKhata / 100;
	sumDefaTeam1 = sumDefaTeam1 * team1ZaribKhata / 100;
	
	for ( int i = 0 ; i < 11 ; i++){
		players1[index_team1[0][i]].khastegi+=7;
		if (players1[index_team1[0][i]].khastegi >100)
			players1[index_team1[0][i]].khastegi=100;
	}	
	//mikham bedum ke aya ye bazikon tu ye index hast ya na, hast=1 bud yani yani bazikn tu ye index hast age 0 bud yaani tu bazi nabude pas amadgish ka mishe
	for ( int k = 0 ; k < size1 ; k++){
		int hast = 0;
		for (int j = 0 ; j < 11 ; j++){
			if(k == index_team1[0][j]){
				hast = 1;
				break;
			}
		}
		
		if (hast == 0){
			players1[k].amadegi-=7;
			players1[k].skill-=7;
		}
		if(players1[k].amadegi < 0)
			players1[k].amadegi = 0;
		if(players1[k].skill < 0 )
			players1[k].skill = 0;
	}
	
	int sumDefaTeam2=0;
	int sumMianeTeam2=0;
	int sumHamleTeam2=0;
	for ( int i=0 ; i < 11 ; i++){
		if ( index_team2[1][i]==3 ){
			if ( players2[index_team2[0][i]].position==3)
				sumDefaTeam2 += players2[index_team2[0][i]].sum;
			else if(players2[index_team2[0][i]].position==1)
				sumDefaTeam2 += players2[index_team2[0][i]].sum * 7 /10 ;
			else if(players2[index_team2[0][i]].position==2)
				sumDefaTeam2 += players2[index_team2[0][i]].sum * 9 / 10;
			else if(players2[index_team2[0][i]].position==4)
				sumDefaTeam2 += players2[index_team2[0][i]].sum /2;
				
		}else if ( index_team2[1][i]==4 ) { 
			if ( players2[index_team2[0][i]].position==4)
				sumDefaTeam2 += players2[index_team2[0][i]].sum * 2;
			else
				sumDefaTeam2 += players2[index_team2[0][i]].sum;
		
		}else if ( index_team2[1][i]==2 ){
			if ( players2[index_team2[0][i]].position==2)
				sumMianeTeam2 += players2[index_team2[0][i]].sum;
			else if(players2[index_team2[0][i]].position==1)
				sumDefaTeam2 += players2[index_team2[0][i]].sum * 9 /10 ;
			else if(players2[index_team2[0][i]].position==3)
				sumDefaTeam2 += players2[index_team2[0][i]].sum * 9 / 10;
			else if(players2[index_team2[0][i]].position==4)
				sumDefaTeam2 += players2[index_team2[0][i]].sum /2;                     
		}else if ( index_team2[1][i]==1 ){
			if ( players2[index_team2[0][i]].position==1)
				sumHamleTeam2 += players2[index_team2[0][i]].sum;
			else if(players2[index_team2[0][i]].position==2)
				sumHamleTeam2 += players2[index_team2[0][i]].sum * 9 /10 ;
			else if(players2[index_team2[0][i]].position==3)
				sumHamleTeam2 += players2[index_team2[0][i]].sum * 7 / 10;
			else if(players2[index_team2[0][i]].position==4)
				sumHamleTeam2 += players2[index_team2[0][i]].sum /2;                     
		}		
	}
	
	sumDefaTeam2 +=sumMianeTeam2/2;
	sumHamleTeam2 +=sumMianeTeam2/2;
	int team2ZaribKhata = randomNo(0,100);
	sumHamleTeam2 = sumHamleTeam2 * team2ZaribKhata / 100;
	sumDefaTeam2 = sumDefaTeam2 * team2ZaribKhata / 100;

	for ( int i=0 ; i < 11 ; i++){
		players2[index_team2[0][i]].khastegi+=7;
		if (players2[index_team2[0][i]].khastegi >100)
			players2[index_team2[0][i]].khastegi=100;
	}	
	
	for ( int k=0 ; k < size2 ; k++){
		int hast=0;
		for (int j=0 ; j < 11 ; j++){
			if(k==index_team2[0][j]){
				hast = 1;
				break;
			}
		}
		if(hast == 0){
			players2[k].amadegi-=7;
			players2[k].skill-=7;	
		}
		if(players2[k].amadegi < 0)
			players2[k].amadegi=0;
		if(players2[k].skill < 0 )
			players2[k].skill=0;		
	}
	if ( sumHamleTeam1 > sumDefaTeam2){ 
		*goal1=(sumHamleTeam1 - sumDefaTeam2) / CTE ;
		for ( int i=0 ; i < *goal1 ; i++){
			goalAssign(players1, index_team1,size1);
		}
	}
	if ( sumHamleTeam2 > sumDefaTeam1) {
		*goal2 = (sumHamleTeam2 - sumDefaTeam1) / CTE ;
		for ( int i = 0 ; i < *goal2 ; i++){
			goalAssign(players2, index_team2,size2);
		}
	}
	

	if ( *goal1 > *goal2 ) {
		for ( int i=0 ; i < size1 ; i++){
			players1[i].rouhiye+=10;
			if(players1[i].rouhiye > 100)
				players1[i].rouhiye=100;			
		}
	} else{
		for ( int i=0 ; i < size2 ; i++){
			players2[i].rouhiye+=10;
			if(players2[i].rouhiye > 100)
				players2[i].rouhiye=100;			
		}		
		
	}
	
	team1-> zade += *goal1;
	team1->khorde += *goal2;
	team1->count++ ;
	if ( *goal1 > *goal2 ) {
		team1 ->score += 3;
	}
	
	team2->zade +=*goal2;
	team2->khorde +=*goal1;
	team2->count++ ;
	if (*goal2 > *goal1 ) {
		team2->score += 3;
	}
	
	
	if (*goal1 == *goal2){
		team2->score += 1;
		team2->score += 1;	
	}
	//345 345 update kone 3 emtiaz ezafe kone be teame bbarande tedad goala ye zade va khorde hm update kon va tedad bazia hm update kone

}



// p: karbar c:compuer
//team_p : teami ke karbar bazi mikond
//team_c : teami ke comuter bazi mikond
void playGameCP ( team_t *team_c , team_t *team_p , int *goal_c , int *goal_p , player_t *players_c ,int size_c, player_t *players_p , int size_p ) {
	
	for (int i=0 ;  i < size_c ; i++ ){
		players_c[i].sum= players_c[i].amadegi + players_c[i].rouhiye/2 -players_c[i].khastegi*2 + players_c[i].skill;
	}
	for (int j=0 ; j<size_p ; j++){
		players_p[j].sum=players_p[j].amadegi + players_p[j].rouhiye/2 -players_p[j].khastegi*2 + players_p[j].skill;
	}
	
	arrangment_t *arrangments;
	int counter= getArrangments(&arrangments);
	int team_c_arrangment = randomNo(0 , counter-1);
	
	
	bubblePlayers( players_c, size_c,playerSUM);
	bubblePlayers( players_p, size_p,playerID);

	int defa_c= arrangments[team_c_arrangment].defa; //tedad defa ra moshakhas mikond
	int miane_c= arrangments[team_c_arrangment].miane;
	int hamle_c= arrangments[team_c_arrangment].hamle;  
	
		
	int index_c[2][11]; //araye ye 2*11 ke id va positione bazikona ye tu ye zamin tushe
	int counter2 = 0; //vase shomare khuna ha ye index_team1
	int darvazeban_c = 1; //mikhaym bedunim hatmn darvazeban darim ya na
	
	// for ha ro vase neveshtm ke khune haye index_team1 ro por kone va mshakhas kone ke shomare ye khune ha ye position ha ye mokhtalef chian
	for ( int k=size_c-1 ; k>=0 && counter2==0 ; k--  ){
		if ( players_c[k].position == 4){
			index_c[0][counter2] = k;
			index_c[1][counter2] = 4;
			counter2++;
		}
	}
	
	if (counter2 == 0 ){
		darvazeban_c=0 ;
	} 
	  
	
	for ( int k=size_c-1 ; k >= 0 && defa_c > 0; k-- ){
		if (players_c[k].position==3 ){
			index_c[0][counter2] = k;
			index_c[1][counter2] = 3;
			counter2++;
			defa_c--;
		}
	}
	
	
	for ( int k=size_c-1; k>=0 && hamle_c > 0; k-- ){
		if (players_c[k].position==1 ){
			index_c[0][counter2] = k;
			index_c[1][counter2] = 1;
			counter2++;
			hamle_c--;
		}
	}
	
	
	for ( int k=size_c-1 ; k>=0 && miane_c>0 ; k-- ){
		if (players_c[k].position==2 ){
			index_c[0][counter2] = k;
			index_c[1][counter2] = 2;
			counter2++;
			miane_c--;
		}
	}
	
	
	if ( defa_c !=0 ) {
		for (  int k=size_c-1 ; k >= 0 && defa_c > 0; k-- ){
			for ( int i=0 ; i < counter2 ; i++){
				if ( k == index_c [0][i] )
					break;
				else if (i == counter2 -1 ){
					index_c[0][counter2]=k;
					index_c[1][counter2]=3;
					counter2++;
					defa_c--;
				}
			}
		}
	}
	
	
	if ( hamle_c !=0 ) {
		for (  int k=size_c-1 ; k >= 0 && hamle_c > 0; k-- ){
			for ( int i=0 ; i < counter2 ; i++){
				if ( k == index_c [0][i] )
					break;
				else if (i == counter2 -1 ){
					index_c[0][counter2]=k;
					index_c[1][counter2]=1;
					counter2++;
					hamle_c--;
				}
			}
		}
	}	
	
	if ( miane_c !=0 ) {
		for (  int k=size_c-1 ; k >= 0 && miane_c > 0; k-- ){
			for ( int i=0 ; i < counter2 ; i++){
				if ( k == index_c [0][i] )
					break;
				else if (i == counter2 -1 ){
					index_c[0][counter2]=k;
					index_c[1][counter2]=2;
					counter2++;
					miane_c--;
				}
			}
		}
	}	

	if ( darvazeban_c==0 ) {
		for (  int k=size_c-1 ; k >= 0 && darvazeban_c!=0 ; k-- ){
			for ( int i=0 ; i < counter2 ; i++){
				if ( k == index_c [0][i] )
					break;
				else if (i == counter2 -1 ){
					index_c[0][counter2]=k;
					index_c[1][counter2]=4;
					counter2++;
					darvazeban_c++;
				}
			}
		}
	}



	int sumDefaTeam_c=0;
	int sumMianeTeam_c=0;
	int sumHamleTeam_c=0;
	for ( int i=0 ; i<11 ; i++){
		if ( index_c[1][i]==3 ){
			if ( players_c[index_c[0][i]].position==3)
				sumDefaTeam_c += players_c[index_c[0][i]].sum;
			else if(players_c[index_c[0][i]].position==1)
				sumDefaTeam_c += players_c[index_c[0][i]].sum * 7 /10 ;
			else if(players_c[index_c[0][i]].position==2)
				sumDefaTeam_c += players_c[index_c[0][i]].sum * 9 / 10;
			else if(players_c[index_c[0][i]].position==4)
				sumDefaTeam_c += players_c[index_c[0][i]].sum /2;//in else if ha bara ye vaghtian ke bazikon dar mogheEyataesh gharar nagire
							
		}else if ( index_c[1][i]==4 ) {  //in else if ha bara ye position ha ye bazikon haye tu ye zamine
			if ( players_c[index_c[0][i]].position==4)
				sumDefaTeam_c += players_c[index_c[0][i]].sum * 2;
			else
				sumDefaTeam_c += players_c[index_c[0][i]].sum;
			
		}else if ( index_c[1][i]==2 ){
			if ( players_c[index_c[0][i]].position==2)
				sumMianeTeam_c += players_c[index_c[0][i]].sum;
			else if(players_c[index_c[0][i]].position==1)
				sumDefaTeam_c += players_c[index_c[0][i]].sum * 9 /10 ;
			else if(players_c[index_c[0][i]].position==3)
				sumDefaTeam_c += players_c[index_c[0][i]].sum * 9 / 10;
			else if(players_c[index_c[0][i]].position==4)
				sumDefaTeam_c += players_c[index_c[0][i]].sum /2;                     
		}else if ( index_c[1][i]==1 ){
			if ( players_c[index_c[0][i]].position==1)
				sumHamleTeam_c += players_c[index_c[0][i]].sum;
			else if(players_c[index_c[0][i]].position==2)
				sumHamleTeam_c += players_c[index_c[0][i]].sum * 9 /10 ;
			else if(players_c[index_c[0][i]].position==3)
				sumHamleTeam_c += players_c[index_c[0][i]].sum * 7 / 10;
			else if(players_c[index_c[0][i]].position==4)
				sumHamleTeam_c += players_c[index_c[0][i]].sum /2;                     
		}		
	}
	
	sumDefaTeam_c+=sumMianeTeam_c/2; //chon miane hich ahamiati tu goal nadare khodesh be tanhayi bhsh moteghayere sum  nemidim
	sumHamleTeam_c+=sumMianeTeam_c/2;
	int team_cZaribKhata=randomNo(0,100);
	
	//tabe random ro farakhani kon ye adade random beyne 0 ta 100 bara ye ar team dar nazar migiri bad defa o hamle ye har teamo dar random/100 zarb mikoni ta ehtemale borde hame ye team ha vujud dashte bashe
	sumHamleTeam_c *=team_cZaribKhata/100;
	sumDefaTeam_c *=team_cZaribKhata/100;
	
	for ( int i=0 ; i<11 ; i++){
		players_c[index_c[0][i]].khastegi+=7;
		if (players_c[index_c[0][i]].khastegi >100)
			players_c[index_c[0][i]].khastegi=100;
	}	
	
	//mikham bedum ke aya ye bazikon tu ye index hast ya na, hast=1 bud yani yani bazikn tu ye index hast age 0 bud yaani tu bazi nabude pas amadgish kam mishe
	for ( int k=0 ; k<size_c ; k++){
		int hast=0;
		for (int j=0 ; j<11 ; j++){
			if(k==index_c[0][j]){
				hast=1;
				break;
			}
		}
		if (hast==0){
			players_c[k].amadegi-=7;
			players_c[k].skill-=7;
		}
		if(players_c[k].amadegi < 0)
			players_c[k].amadegi=0;
		if(players_c[k].skill < 0 )
			players_c[k].skill=0;		
	}


	int sumDefaTeam_p=0;
	int sumMianeTeam_p=0;
	int sumHamleTeam_p=0;
		
	for ( int i=0 ; i<11 ; i++){
		if ( index_p[1][i]==3 ){
			if ( players_p[index_p[0][i]].position==3)
				sumDefaTeam_p += players_p[index_p[0][i] - players_p[0].id].sum;
			else if(players_p[index_p[0][i]].position==1)
				sumDefaTeam_p +=players_p[index_p[0][i] - players_p[0].id].sum * 7 /10 ;
			else if(players_p[index_p[0][i]].position==2)
				sumDefaTeam_p +=players_p[index_p[0][i] - players_p[0].id].sum * 9 / 10;
			else if(players_p[index_p[0][i]].position==4)
				sumDefaTeam_p +=players_p[index_p[0][i] - players_p[0].id].sum /2;			
		}else if ( index_p[1][i]==4 ){
			if ( players_p[index_p[0][i]].position==4)
				sumDefaTeam_p += players_p[index_p[0][i] - players_p[0].id].sum * 2;
			else
				sumDefaTeam_p += players_p[index_p[0][i] - players_p[0].id].sum;			
		}else if ( index_p[1][i]==2 ){
			if ( players_p[index_p[0][i]].position==2)
				sumMianeTeam_p += players_p[index_p[0][i] - players_p[0].id].sum;
			else if(players_p[index_p[0][i]].position==1)
				sumDefaTeam_p += players_p[index_p[0][i] - players_p[0].id].sum * 9 /10 ;
			else if(players_p[index_p[0][i]].position==3)
				sumDefaTeam_p += players_p[index_p[0][i] - players_p[0].id].sum * 9 / 10;
			else if(players_p[index_p[0][i]].position==4)
				sumDefaTeam_p += players_p[index_p[0][i] - players_p[0].id].sum /2;			
		}else if ( index_p[1][i]==1 ) {
			if ( players_p[index_p[0][i]].position==1)
				sumHamleTeam_p += players_p[index_p[0][i] - players_p[0].id].sum;
			else if(players_p[index_p[0][i]].position==2)
				sumHamleTeam_p += players_p[index_p[0][i] - players_p[0].id].sum * 9 /10 ;
			else if(players_p[index_p[0][i]].position==3)
				sumHamleTeam_p += players_p[index_p[0][i] - players_p[0].id].sum * 7 / 10;
			else if(players_p[index_p[0][i]].position==4)
				sumHamleTeam_p += players_p[index_p[0][i] - players_p[0].id].sum /2;			
		}	
	}
	
	sumDefaTeam_p+=sumMianeTeam_p/2; //chon miane hich ahamiati tu goal nadare khodesh be tanhayi bhsh moteghayere sum  nemidim
	sumHamleTeam_p+=sumMianeTeam_p/2;
	int team_pZaribKhata=randomNo(0,100);	

	sumHamleTeam_p = sumHamleTeam_p * team_pZaribKhata/100;
	sumDefaTeam_p = sumDefaTeam_p * team_pZaribKhata/100;
	
	//updating....

	for ( int i=0 ; i<11 ; i++){
		players_p[index_p[0][i] - players_p[0].id].khastegi+=7;
		if (players_p[index_p[0][i] - players_p[0].id].khastegi >100)
			players_p[index_p[0][i] - players_p[0].id].khastegi=100;
	}



	for ( int k=0 ; k<size_p ; k++){
		int hast=0;
		for (int j=0 ; j<11 ; j++){
			if(players_p[k].id==index_p[0][j]){
				hast=1;
				break;
			}
		}
		if (hast==0){
			players_p[index_p[0][k] - players_p[0].id].amadegi-=7;
			players_p[index_p[0][k] - players_p[0].id].skill-=7;
		}
		if(players_p[index_p[0][k] - players_p[0].id].amadegi < 0)
			players_p[index_p[0][k] - players_p[0].id].amadegi=0;
		if(players_p[index_p[0][k] - players_p[0].id].skill < 0 )
			players_p[index_p[0][k] - players_p[0].id].skill=0;		
	}



	if ( sumHamleTeam_c > sumDefaTeam_p){ 
		*goal_c=(sumHamleTeam_c - sumDefaTeam_p) / CTE ;
		for ( int i=0 ; i<*goal_c ; i++){
			goalAssign(players_c, index_c,size_c);
		}
	}

	if ( sumHamleTeam_p > sumDefaTeam_c) {
		*goal_p=(sumHamleTeam_p - sumDefaTeam_c) / CTE ;
		for ( int i=0 ; i<*goal_p ; i++){
			goalAssign(players_p, index_p,size_p);
		}		
	}
	

	if ( *goal_c > *goal_p ) {
		for ( int i=0 ; i<size_c ; i++){
			players_c[i].rouhiye+=10;
			if(players_c[i].rouhiye > 100)
				players_c[i].rouhiye=100;			
		}
	} else{
		for ( int i=0 ; i<size_p ; i++){
			players_p[i].rouhiye+=10;
			if(players_p[i].rouhiye > 100)
				players_p[i].rouhiye=100;			
		}		
		
	}
	
	team_c-> zade += *goal_c;
	team_c->khorde += *goal_p;
	team_c->count++ ;
	if ( *goal_c > *goal_p ) {
		team_c ->score += 3;
	}
	
	team_p-> zade+= *goal_p;
	team_p->khorde+= *goal_c;
	team_p->count++ ;
	if (*goal_p > *goal_c ) {
		team_p->score += 3;
	}
	
	
	if (*goal_c == *goal_p){
		team_p->score += 1;
		team_p->score += 1;	
	}


}
