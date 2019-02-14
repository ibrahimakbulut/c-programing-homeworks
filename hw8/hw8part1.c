#include <stdio.h>
#include <time.h>   //for srand() function
#include <stdlib.h>	//for rand() function
typedef enum{P=0,S=1,M=2,T=3,B=4,N=5}types;  // N is type that if blocks type is not P,S,M,T or B.

typedef struct{
	char *text;
	int data;
	types type;
	int pos_x;
	int pos_y;
	int jump_x;
	int jump_y;
}block;

void initialize_boards(block board[][10]){
	
	int i,j;
	block copy_board[10][10]={{{"91",91,N,0,0,0,0},{"92",92,N,0,1,0,1},{"T",93,T,0,2,5,7},{"94",94,N,0,3,0,3},{"95",95,N,0,4,0,4},{"96",96,N,0,5,0,5},{"97",97,N,0,6,0,6},{"S",98,S,0,7,2,1},{"S",99,S,0,8,4,5},{"100",100,N,0,9,0,9}},
			{{"90",90,N,1,0,1,0},{"M",89,M,1,1,0,3},{"88",88,N,1,2,1,2},{"87",87,N,1,3,1,3},{"86",86,N,1,4,1,4},{"P",85,P,1,5,1,5},{"84",83,N,1,6,1,6},{"83",83,N,1,7,1,7},{"B",82,B,1,8,0,9},{"81",81,N,1,9,1,9}},
			{{"71",71,N,2,0,2,0},{"72",72,N,2,1,2,1},{"S",73,S,2,2,3,2},{"74",74,N,2,3,2,3},{"75",75,N,2,4,2,4},{"M",76,M,2,5,1,7},{"77",77,N,2,6,2,6},{"78",78,N,2,7,2,7},{"T",79,T,2,8,7,8},{"80",80,N,2,9,2,9}},
			{{"70",70,N,3,0,3,0},{"M",69,M,3,1,2,6},{"68",68,N,3,2,3,2},{"67",67,N,3,3,3,3},{"B",66,B,3,4,0,9},{"65",65,N,3,5,3,5},{"64",67,N,3,6,3,6},{"S",63,S,3,7,4,1},{"62",62,N,3,8,3,8},{"61",61,N,3,9,3,9}},
			{{"51",51,N,4,0,4,0},{"52",52,N,4,1,4,1},{"53",53,N,4,2,4,2},{"T",54,T,4,3,9,6},{"55",55,N,4,4,4,4},{"56",56,N,4,5,4,5},{"M",57,M,4,6,2,6},{"58",58,N,4,7,4,7},{"59",59,N,4,8,4,8},{"S",60,S,4,9,5,6}},
			{{"B",50,B,5,0,0,9},{"49",49,N,5,1,5,1},{"P",48,P,5,2,5,2},{"47",47,N,5,3,5,3},{"46",46,N,5,4,5,4},{"S",45,S,5,5,7,8},{"44",44,N,5,6,5,6},{"43",43,N,5,7,5,7},{"42",42,N,5,8,5,8},{"41",41,N,5,9,5,9}},
			{{"31",31,N,6,0,6,0},{"M",32,M,6,1,4,1},{"33",33,N,6,2,6,2},{"34",34,N,6,3,6,3},{"35",35,N,6,4,6,4},{"B",36,B,6,5,1,4},{"37",37,N,6,6,6,6},{"38",38,N,6,7,6,7},{"39",39,N,6,8,6,8},{"T",40,T,6,9,9,9}},
			{{"30",30,N,7,0,7,0},{"B",29,B,7,1,2,8},{"28",28,N,7,2,7,2},{"27",27,N,7,3,7,3},{"26",26,N,7,4,7,4},{"S",25,S,7,5,8,1},{"24",24,N,7,6,7,6},{"23",23,N,7,7,7,7},{"22",22,N,7,8,7,8},{"21",21,N,7,9,7,9}},
			{{"11",11,N,8,0,8,0},{"12",12,N,8,1,8,1},{"P",13,P,8,2,8,2},{"14",14,N,8,3,8,3},{"15",15,N,8,4,7,4},{"16",16,N,8,5,8,5},{"M",17,M,8,6,7,2},{"18",18,N,8,7,8,7},{"19",19,N,8,8,8,8},{"20",20,N,8,9,8,9}},
			{{"10",10,N,9,0,9,0},{"9",9,N,9,1,9,1},{"8",8,N,9,2,9,2},{"M",7,M,9,3,8,0},{"S",6,S,9,4,9,9},{"5",5,N,9,5,9,5},{"4",4,N,9,6,9,6},{"3",3,N,9,7,9,7},{"2",2,N,9,8,9,8},{"1",1,N,9,9,9,9}}
			};
	
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			board[i][j]=copy_board[i][j];
		}
	}	
}
void index_founder(int *x,int *y,int value,block board[][10]){ //this function return the pos_x and pos_y of given value.
	
	int i,j;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			if(board[i][j].data==value){
				*x=board[i][j].pos_x;*y=board[i][j].pos_y;
			}
		}
	}
	return ;
}
int roll_dice(void){ //this function roll the dice and return a number between 1-6
	int value;
	value=rand()%7;
	if(value==0)
		value+=1;
	return value;
}
int single_game(block board[][10],int current_x,int current_y){
	
	int dice,old_x,old_y,counter;
	old_x=current_x;  //we keep current_x and current_y because they will be changed by index_founder function.
	old_y=current_y;
	counter=0;
	
	dice=roll_dice();
	if(board[current_x][current_y].data==100) //if game is already 100
		return counter;
	if((board[current_x][current_y].data+dice<100)){ //if current block with dice is less than 100
		counter+=1;  //move counter is increased
		index_founder(&current_x,&current_y,board[current_x][current_y].data+dice,board); //current_x and current_y are updated.
		if(board[current_x][current_y].type==M || board[current_x][current_y].type==S || board[current_x][current_y].type==B || board[current_x][current_y].type==P || board[current_x][current_y].type==T){
			if(board[current_x][current_y].type==P){
				counter+=1;}
			counter+=single_game(board,board[current_x][current_y].jump_x,board[current_x][current_y].jump_y);
			printf("move from %d to %d (%s)\n",board[current_x][current_y].data,board[board[current_x][current_y].jump_x][board[current_x][current_y].jump_y].data,board[current_x][current_y].text);
			printf("dice rolled as %d and move from %d to %d\n",dice,board[old_x][old_y].data,board[current_x][current_y].data);
		}
		else{
			counter+=single_game(board,current_x,current_y);
			printf("dice rolled as %d and move from %d to %d\n",dice,board[old_x][old_y].data,board[current_x][current_y].data);
		}
	}
	else if(board[current_x][current_y].data+dice==100){ //if current block with dice is equal 100 calling function is stopped
		counter+=1;
		index_founder(&current_x,&current_y,board[current_x][current_y].data+dice,board);
		printf("dice rolled as %d and move from %d to %d\n",dice,board[old_x][old_y].data,board[current_x][current_y].data);
	}
	else if((board[current_x][current_y].data+dice)>100){ //if current block with dice is more than 100 ,dont move but move_counter is increased
		counter+=1;
		counter+=single_game(board,current_x,current_y);
		printf("dice rolled as %d and move from %d to %d\n",dice,board[old_x][old_y].data,board[current_x][current_y].data);	
	}
	return counter;
}
void print_board(block board[][10]){
	int i,j;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			if(board[i][j].type==M || board[i][j].type==S)
			printf("%s{%d}  ",board[i][j].text,board[board[i][j].jump_x][board[i][j].jump_y].data);
			else{
				if(board[i][j].type==T || board[i][j].type==P || board[i][j].type==B)
					printf("%s      ",board[i][j].text);
				else{
				if(j-1>=0 &&board[i][j].data/10<=0 &&(board[i][j-1].type==M || board[i][j-1].type==S) )
				printf(" %s      ",board[i][j].text);
				else if(board[i][j].data/10<=0)
				printf("%s      ",board[i][j].text);
				else if(board[i][j].data/10<10)
				printf("%s     ",board[i][j].text);
				else
					printf("%s     ",board[i][j].text);
				}
		}
	}
	printf("\n\n");
	}
}
void multiplayer_game(){
	
	int player1_move_count,player2_move_count;
	block board[10][10];
	
	initialize_boards(board);
	
	print_board(board);
	
	printf("PLAYER 1's  MOVES\n\n");
	player1_move_count=single_game(board,9,9); //play for player 1
	
	printf("\n-----------------------------------------\n\n");
	
	printf("PLAYER 2's  MOVES\n\n");
	player2_move_count=single_game(board,9,9); //play for player 2
	printf("\n\n");
	
	if(player1_move_count>player2_move_count)
		printf("PLAYER 2 WON THE GAME\n");
	else if(player2_move_count>player1_move_count)
		printf("PLAYER 1 WON THE GAME\n");
	else
		printf("GAME ENDED IN DRAW");
}

int main(){
	
	srand(time(NULL));
	
	//block board[10][10];  //this is required just for single_game function if you call that.
	
	//initialize_boards(board);  //this is required just for single_game function if you call that.
	
	//single_game(board,9,9);
	
	multiplayer_game();

	return 0;
}
