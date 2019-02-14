#include <stdio.h>


typedef enum {white_man, black_man, white_king, black_king, empty} piece;

typedef enum {white = 10, black = 20} player;

int check_end_of_game(piece board[][8]){
	
	int i,j;
	int white_counter=0,black_counter=0;
	int white_move=0,black_move=0;
	
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(board[i][j]==white_man || board[i][j]==white_king) //tüm haritayi tarar ve etrafi bloklanmis veya tamamen bitmis türü kaybeden ilan eder.
				white_counter+=1;
		}
	}
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(board[i][j]==black_man || board[i][j]==black_king)
				black_counter+=1;
		}
	}
	if(white_counter==0)
		return black;
	if(black_counter==0)
		return white;
		
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(board[i][j]==white_man || board[i][j]==white_king){
				if( j+1<8 &&board[i][j+1]==empty)
					white_move+=1;
				else if(j+2<8 && (board[i][j+2]==empty))
					white_move+=1;
				if(j-1>=0 && board[i][j-1]==empty)
					white_move+=1;
				else if(j-2>=0 && board[i][j-2]==empty)
					white_move+=1;
				if(i+1<8 && board[i+1][j]==empty)
					white_move+=1;
				else if(i+2<8 && board[i+2][j]==empty)
					white_move+=1;
				if(board[i][j]==white_king){
					if(i-1>=0 && board[i-1][j]==empty)
						white_move+=1;
					else if(i-2>=0 && board[i-2][j]==empty)
						white_move+=1;
				}
			}
		}
	}
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(board[i][j]==black_man || board[i][j]==black_king){
				if( j+1<8 &&board[i][j+1]==empty)
					black_move+=1;
				else if(j+2<8 && (board[i][j+2]==empty))
					black_move+=1;
				if(j-1>=0 && board[i][j-1]==empty)
					black_move+=1;
				else if(j-2>=0 && board[i][j-2]==empty)
					black_move+=1;
				if(board[i][j]==black_king){
				if(i+1<8 && board[i+1][j]==empty)
					black_move+=1;
				else if(i+2<8 && board[i+2][j]==empty)
					black_move+=1;
				}
				if(i-1>=0 && board[i-1][j]==empty)
					black_move+=1;
				else if(i-2>=0 && board[i-2][j]==empty)
					black_move+=1;
			}
		}
	}
	if(black_move==0)
		return white;
	else if(white_move==0)
		return black;
	
	else 
		return -1;
}
int man_x(player oyuncu,piece board[][8],int *from_x,int *from_y,int to_x,int to_y,int x_differ,int *captured,int *kosul_sayac){
	piece man,king;

	if(oyuncu==black){
		man=black_man;
		king=black_king;
	}
	else{
		man=white_man;
		king=white_king;
	}
	if(oyuncu==white && x_differ<=0)
		return -2;
	if(oyuncu==black && x_differ>=0)
		return -2;
	if(oyuncu==black && (x_differ==-1) && (board[to_x][to_y]!=empty))
		return -2;
	if(oyuncu==white && (x_differ==1) && (board[to_x][to_y]!=empty))
		return -2;
	if(oyuncu==white){
	if((x_differ==1) && board[to_x][to_y]==empty){
		if(to_x==7)
			board[to_x][to_y]=king;
		else
			board[to_x][to_y]=man;
		board[*from_x][*from_y]=empty;
		return *captured;
		}
	}
	if(oyuncu==black){
	if((x_differ==-1) && board[to_x][to_y]==empty){
		if(to_x==0)
			board[to_x][to_y]=king;
		else
			board[to_x][to_y]=man;
		board[*from_x][*from_y]=empty;
		return *captured;
		}
	}
	if(oyuncu==white){
		if(x_differ==2 && board[to_x][to_y]==empty && (board[*from_x+1][*from_y]!=man && board[*from_x+1][*from_y]!=king && board[*from_x+1][*from_y]!=empty)){
			*kosul_sayac+=1;
			board[*from_x+1][*from_y]=empty;
			board[*from_x+2][*from_y]=man;
			board[*from_x][*from_y]=empty;
			*captured+=1;
			*from_x=*from_x+2;
			man_recursive(oyuncu,board,from_x,from_y,captured);
			return *captured;
		}
		else if(x_differ==2 && board[to_x][to_y]!=empty)
				return -2;
		else 
			return -2;
	}
	if(oyuncu==black){
		if(x_differ==-2 && board[to_x][to_y]==empty && (board[*from_x-1][*from_y]!=man && board[*from_x-1][*from_y]!=king && board[*from_x-1][*from_y]!=empty)){
			*kosul_sayac+=1;
			board[*from_x-1][*from_y]=empty;
			board[*from_x-2][*from_y]=man;
			board[*from_x][*from_y]=empty;
			*captured+=1;
			*from_x=*from_x-2;
			man_recursive(oyuncu,board,from_x,from_y,captured);
			return *captured;
		}
		else if(x_differ==2 && board[to_x][to_y]!=empty)
				return -2;
		else 
			return -2;
	}
	else 
		return -2;
}
int man_y(player oyuncu,piece board[][8],int *from_x,int *from_y,int to_x,int to_y,int y_differ,int *captured,int *kosul_sayac){
	
	piece man;
	piece king;

	if(oyuncu==black){
		man=black_man;
		king=black_king;
	}
	else{
		man=white_man;
		king=white_king;
	}
	if((y_differ==1 || y_differ==-1) && board[to_x][to_y]==empty){
		if(y_differ==1)
			board[*from_x][*from_y+1]=man;
		else
			board[*from_x][*from_y-1]=man;
		board[*from_x][*from_y]=empty;
		return *captured;
	}
	else if((y_differ==1 || y_differ==-1) && (board[to_x][to_y]==man || board[to_x][to_y]==king))
		return -2;
		if(y_differ==2 && board[to_x][to_y]==empty && (board[*from_x][*from_y+1]!=man && board[*from_x][*from_y+1]!=king && board[*from_x][*from_y+1]!=empty)){ //pozitif yönde hareket
			*kosul_sayac+=1;//dikkat
			board[*from_x][*from_y+1]=empty;
			board[*from_x][*from_y+2]=man;
			board[*from_x][*from_y]=empty;
			*captured+=1;
			*from_y=*from_y+2;
			man_recursive(oyuncu,board,from_x,from_y,captured);
			return *captured;
		}
		if(y_differ==-2 && board[to_x][to_y]==empty && (board[*from_x][*from_y-1]!=man && board[*from_x][*from_y-1]!=king)){ //negatif yonde hareket
			board[*from_x][*from_y]=empty;
			board[*from_x][*from_y-1]=empty;
			board[*from_x][*from_y-2]=man;
			*kosul_sayac+=1;//dikkat
			*captured+=1;
			*from_y=*from_y-2;
			man_recursive(oyuncu,board,from_x,from_y,captured);
			return *captured;
		}
		else if((y_differ==2 || y_differ==-2) && (board[to_x][to_y]!=man && board[to_x][to_y]!=king && board[to_x][to_y]!=empty))
			return -2;
		else
			return -2;
	
}
int king_x(player oyuncu,piece board[][8],int *from_x,int *from_y,int to_x,int to_y,int x_differ,int *captured){
	int i,j,counter;
	piece man,king;
	counter=0;

	if(oyuncu==black){
		man=black_man;
		king=black_king;
	}
	else if(oyuncu==white){
		man=white_man;
		king=white_king;
	}
	if((to_x>7 || to_x<0) || (to_y>7 ||to_y<0))
			return -2;
	if(board[to_x][to_y]!=empty)
			return -2;
			
	if(x_differ>0){ //istenen hedefe kadarki olan engel sayisini yani tas sayisini belirler
		for(i=*from_x;i<to_x;i++){
			if(board[i][*from_y]!=man && board[i][*from_y]!=king && board[i][*from_y]!=empty)
				counter=counter+1;	
		}
	}
	else if(x_differ<0){  //hareket negatif yonde
		for(i=*from_x;i>to_x;i--){
			if(board[i][*from_y]!=man && board[i][*from_y]!=king && board[i][*from_y]!=empty)
				counter=counter+1;	
		}
	}
	
	if(counter==0){
		board[to_x][to_y]=king; //eger engel yoksa direk hamleyi yapar
		board[*from_x][*from_y]=empty;
			
		*from_x=to_x;    *from_y=to_y;
		return *captured;
	}
	else if(counter==1){
		if(x_differ>0){
			for(i=*from_x;i<to_x;i++){
				if(board[i][*from_y]!=man && board[i][*from_y]!=king && board[i][*from_y]!=empty){ // eger 1 engel varsa onu yer ve hedefe gider
					board[i][*from_y]=empty;}	//diger türlü hamleye izin verilmez
			}
			}
		else if(x_differ<0){
			for(i=*from_x;i>to_x;i--){
				if(board[i][*from_y]!=man && board[i][*from_y]!=king && board[i][*from_y]!=empty)
					board[i][*from_y]=empty;
			}
			}
			board[to_x][to_y]=king;
			board[*from_x][*from_y]=empty;
			
			*from_x=to_x;    *from_y=to_y;
			king_recursive(oyuncu,board,from_x,from_y,captured);
			return *captured;
	}
	else
		return -2;
	
}
int king_y(player oyuncu,piece board[][8],int *from_x,int *from_y,int to_x,int to_y,int y_differ,int *captured){
	
	int i,j,counter;
	piece man;
	piece king;
	counter=0;

	if(oyuncu==black){
		man=black_man;
		king=black_king;
	}
	else if(oyuncu==white){
		man=white_man;
		king=white_king;
	}
	
	
	if((to_x>7 || to_x<0) || (to_y>7 ||to_y<0))
			return -2;
		
	if(board[to_x][to_y]!=empty)
			return -2;	
			
	if(y_differ>0){ //istenen hedefe kadarki olan engel sayisini yani tas sayisini belirler
		for(i=*from_y;i<to_y;i++){
			if(board[*from_x][i]!=man && board[*from_x][i]!=king && board[*from_x][i]!=empty)
				counter=counter+1;	
		}
	}
	else if(y_differ<0){  //hareket negatif yonde
		for(i=*from_y;i>to_y;i--){
			if(board[*from_x][i]!=man && board[*from_x][i]!=king && board[*from_x][i]!=empty)
				counter=counter+1;	
		}
	}
	
		
		if(counter==0){
			board[to_x][to_y]=king; //eger engel yoksa direk hamleyi yapar
			board[*from_x][*from_y]=empty;
			
			*from_x=to_x;    *from_y=to_y;
			return *captured;
		}
		else if(counter==1){
			if(y_differ>0){
			for(i=*from_y;i<to_y;i++){
				if(board[*from_x][i]!=man && board[*from_x][i]!=king && board[*from_x][i]!=empty) // eger 1 engel varsa onu yer ve hedefe gider
					board[*from_x][i]=empty;										//diger türlü hamleye izin verilmez
			}
			}
			else if(y_differ<0){
			for(i=*from_y;i>to_y;i--){
				if(board[*from_x][i]!=man && board[*from_x][i]!=king && board[*from_x][i]!=empty)
					board[*from_x][i]=empty;	
			}
			}
			board[to_x][to_y]=king;
			board[*from_x][*from_y]=empty;
			
			*from_x=to_x;    *from_y=to_y;
			king_recursive(oyuncu,from_x,from_y,captured);
			return *captured;
		}
		else	
			return -2;
		
}
void man_recursive(player oyuncu,piece board[][8],int *from_x,int *from_y,int *captured){
	piece man;
	piece king;

	if(oyuncu==black){
		man=black_man;
		king=black_king;
	}
	else{
		man=white_man;
		king=white_king;
	}
	if(!(board[*from_x][*from_y]!=king && ((*from_y+2<8 &&(board[*from_x][*from_y+1]!=man && board[*from_x][*from_y+1]!=king && board[*from_x][*from_y+1]!=empty) && board[*from_x][*from_y+2]==empty)||(*from_x-2>=0 && (board[*from_x-1][*from_y]!=man && board[*from_x-1][*from_y]!=king && board[*from_x-1][*from_y]!=empty) && board[*from_x-2][*from_y]==empty) ||(*from_x+2<8 && (board[*from_x+1][*from_y]!=man && board[*from_x+1][*from_y]!=king && board[*from_x+1][*from_y]!=empty) && board[*from_x+2][*from_y]==empty) || (*from_y-2>=0 &&(board[*from_x][*from_y-1]!=man && board[*from_x][*from_y-1]!=king && board[*from_x][*from_y-1]!=empty) && board[*from_x][*from_y-2]==empty)))){
		*captured=*captured;
		printf("buraya girdiiiiiiiiii");
	}
	else{
		if((board[*from_x][*from_y+1]!=man && board[*from_x][*from_y+1]!=king && board[*from_x][*from_y+1]!=empty) && board[*from_x][*from_y+2]==empty && board[*from_x][*from_y]!=king){
				board[*from_x][*from_y+1]=empty;
				board[*from_x][*from_y+2]=man;
				board[*from_x][*from_y]=empty;
				display_board(board);
				*from_y=*from_y+2;
				*captured+=1;
				man_recursive(oyuncu,board,from_x,from_y,captured);
			}
			if(oyuncu==black){
			if((board[*from_x-1][*from_y]!=man && board[*from_x-1][*from_y]!=king && board[*from_x-1][*from_y]!=empty) && board[*from_x-2][*from_y]==empty && board[*from_x][*from_y]!=king){
				if(*from_x-2==0)
					board[*from_x-2][*from_y]=king;
				else
					board[*from_x-2][*from_y]=man;
				board[*from_x-1][*from_y]=empty;
				board[*from_x][*from_y]=empty;
				display_board(board);
				*from_x=*from_x-2;
				*captured+=1;																														//
				man_recursive(oyuncu,board,from_x,from_y,captured);
			}}
			else{
				if((board[*from_x+1][*from_y]!=man && board[*from_x+1][*from_y]!=king && board[*from_x+1][*from_y]!=empty) && board[*from_x+2][*from_y]==empty && board[*from_x][*from_y]!=king){
					if(*from_x+2==7)
						board[*from_x+2][*from_y]=king;
					else
						board[*from_x+2][*from_y]=man;
					board[*from_x+1][*from_y]=empty;
					board[*from_x][*from_y]=empty;
					display_board(board);
					*from_x=*from_x+2;
					*captured+=1;
					man_recursive(oyuncu,board,from_x,from_y,captured);
				}
			}
			if((board[*from_x][*from_y-1]!=man && board[*from_x][*from_y-1]!=king && board[*from_x][*from_y-1]!=empty) && board[*from_x][*from_y-2]==empty && board[*from_x][*from_y]!=king){
				board[*from_x][*from_y-1]=empty;
				board[*from_x][*from_y-2]=man;
				board[*from_x][*from_y]=empty;
				display_board(board);
				*from_y=*from_y-2;
				*captured+=1;
				man_recursive(oyuncu,board,from_x,from_y,captured);
			}
	}
}
void king_recursive(player oyuncu,piece board[][8],int *from_x,int *from_y,int *captured){
	piece man,king;
	int i,bosluk_y_sayac,bosluk_y1_sayac,bosluk_x_sayac,bosluk_x1_sayac;
	bosluk_y_sayac=0;
	bosluk_y1_sayac=0;
	bosluk_x_sayac=0;
	bosluk_x1_sayac=0;

	if(oyuncu==black){
		man=black_man;
		king=black_king;
	}
	else{
		man=white_man;
		king=white_king;
	}
	for(i=*from_y+1;i<8 && board[*from_x][i]==empty;i++){
		bosluk_y_sayac+=1;}
	for(i=*from_x+1;i<8 && board[i][*from_y]==empty;i++){
		bosluk_x_sayac+=1;}
	for(i=*from_y-1;i>=0 && board[*from_x][i]==empty;i--){
		bosluk_y1_sayac+=1;}
	for(i=*from_x-1;i>=0 && board[i][*from_y]==empty;i--){
		bosluk_x1_sayac+=1;}
	if(!((*from_y+bosluk_y_sayac+2<8 && board[*from_x][*from_y+bosluk_y_sayac+2]==empty && (board[*from_x][*from_y+bosluk_y_sayac+1]!=man && board[*from_x][*from_y+bosluk_y_sayac+1]!=king && board[*from_x][*from_y+bosluk_y_sayac+1]!=empty)) || (*from_y-bosluk_y1_sayac-2>=0 && board[*from_x][*from_y-bosluk_y1_sayac-2]==empty && (board[*from_x][*from_y-bosluk_y1_sayac-1]!=king && board[*from_x][*from_y-bosluk_y1_sayac-1]!=man && board[*from_x][*from_y-bosluk_y1_sayac-1]!=empty)) || (board[*from_x+bosluk_x_sayac+2][*from_y]==empty && (board[*from_x+bosluk_x_sayac+1][*from_y]!=king && board[*from_x+bosluk_x_sayac+1][*from_y]!=man && board[*from_x+bosluk_x_sayac+1][*from_y]!=empty)) || (*from_x-bosluk_x1_sayac-2>=0 && board[*from_x-bosluk_x1_sayac-2][*from_y]==empty && (board[*from_x-bosluk_x1_sayac-1][*from_y]!=king && board[*from_x-bosluk_x1_sayac-1][*from_y]!=man && board[*from_x-bosluk_x1_sayac-1][*from_y]!=empty))))
		*captured=*captured;
	else{
		if(*from_y+bosluk_y_sayac+2<8 && board[*from_x][*from_y+bosluk_y_sayac+2]==empty){
			board[*from_x][*from_y+bosluk_y_sayac+2]=king;
			board[*from_x][*from_y]=empty;
			*captured+=1;
			board[*from_x][*from_y+bosluk_y_sayac+1]=empty;
			display_board(board);
			*from_y=*from_y+bosluk_y_sayac+2;
			king_recursive(oyuncu,board,from_x,from_y,captured);	
		}
		else if(*from_y-bosluk_y1_sayac-2>=0 &&board[*from_x][*from_y-bosluk_y1_sayac-2]==empty){
			board[*from_x][*from_y-bosluk_y1_sayac-2]=king;
			board[*from_x][*from_y]=empty;
			*captured+=1;
			board[*from_x][*from_y-bosluk_y1_sayac-1]=empty;
			display_board(board);
			*from_y=*from_y-bosluk_y1_sayac-2;
			king_recursive(oyuncu,board,from_x,from_y,captured);
		}
		else if(*from_x+bosluk_x_sayac+2<8 && board[*from_x+bosluk_x_sayac+2][*from_y]==empty){
			board[*from_x+bosluk_x_sayac+2][*from_y]=king;
			board[*from_x][*from_y]=empty;
			*captured+=1;
			board[*from_x+bosluk_x_sayac+1][*from_y]=empty;
			display_board(board);
			*from_x=*from_x+bosluk_x_sayac+2;
			king_recursive(oyuncu,board,from_x,from_y,captured);
		}
		else if(*from_x-bosluk_x1_sayac-2>=0 && board[*from_x-bosluk_x1_sayac-2][*from_y]==empty){
			board[*from_x-bosluk_x1_sayac-2][*from_y]=king;
			board[*from_x][*from_y]=empty;
			*captured+=1;
			board[*from_x-bosluk_x1_sayac-1][*from_y]=empty;
			display_board(board);
			*from_x=*from_x-bosluk_x1_sayac-2;
			king_recursive(oyuncu,board,from_x,from_y,captured);
		}
	}
}

int move(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p){
	
	int captured,x_differ,y_differ,i,j;
	int counter=0;
	int bosluk_y_sayac=0;
	int bosluk_y1_sayac=0;
	int bosluk_x_sayac=0;
	int bosluk_x1_sayac=0;
	int kosul_sayac=0;
	int return_value;
	
	
	captured=0;
	
	x_differ=to_x-from_x;
	y_differ=to_y-from_y;
	
	
	
	if(	x_differ==0){  //yapilmak istenen hareketin y ekseninde oldugunu belirler
		
	if(p==black && (board[from_x][from_y]==white_man || board[from_x][from_y]==white_king))
		return -1;
	if(p==white && (board[from_x][from_y]==black_man || board[from_x][from_y]==black_king))
		return -1;
	if(board[from_x][from_y]==empty)
		return -2;
	
		
		
	if(p==white && board[from_x][from_y]==white_man){ //temel olarak 4 tas oldugu icin bu hareketi 4 kisimda inceleriz
		return_value=man_y(p,board,&from_x,&from_y,to_x,to_y,y_differ,&captured,&kosul_sayac); ///
		if(return_value<=0)
			return return_value;
	}
	if(p==black && board[from_x][from_y]==black_man){ //siyah taş ise 
		return_value=man_y(p,board,&from_x,&from_y,to_x,to_y,y_differ,&captured,&kosul_sayac);
		if(return_value<=0)
			return return_value;
	}
	
	if(p==white && board[from_x][from_y]==white_king && kosul_sayac==0){ //beyaz kral ise
		
		return_value=king_y(p,board,&from_x,&from_y,to_x,to_y,y_differ,&captured);
		if(return_value<=0)
			return return_value;
	}
	if(p==black && board[from_x][from_y]==black_king && kosul_sayac==0){ // siyah kral
		
		return_value=king_y(p,board,&from_x,&from_y,to_x,to_y,y_differ,&captured);
		if(return_value<=0)
			return return_value;
	}
	if(board[from_x][from_y]==black_king){ //burdaki if kosulu tasin düz tas iken kral durumuna gecmesinde hareketleri devam ettirir
		king_recursive(p,board,&from_x,&from_y,&captured);
		return captured;
	}
	if(board[from_x][from_y]==white_king){ //yukardaki ile ayni
		king_recursive(p,board,&from_x,&from_y,&captured);
		return captured;		
	}
	if(kosul_sayac>0){
		return captured;}	
	}
	else if(y_differ==0){ // hareketin x ekseninde oldugunu belirler
		if(p==black && (board[from_x][from_y]==white_man || board[from_x][from_y]==white_king))
			return -1;
		if(p==white && (board[from_x][from_y]==black_man || board[from_x][from_y]==black_king))
			return -1;
		if(board[from_x][from_y]==empty)
			return -2;
	
		
	if(p==white && board[from_x][from_y]==white_man){
			
		return_value=man_x(p,board,&from_x,&from_y,to_x,to_y,x_differ,&captured,&kosul_sayac);
		if(return_value<=0)
			return return_value;
	}
		
				
	if(p==black && board[from_x][from_y]==black_man){
			
		return_value=man_x(p,board,&from_x,&from_y,to_x,to_y,x_differ,&captured,&kosul_sayac);
		if(return_value<=0)
			return return_value;
	}
	if(p==white && board[from_x][from_y]==white_king && kosul_sayac==0){
		
		return_value=king_x(p,board,&from_x,&from_y,to_x,to_y,x_differ,&captured);
		if(return_value<=0)
			return return_value;
	}
	if(p=black && board[from_x][from_y]==black_king && kosul_sayac==0){
		return_value=king_x(p,board,&from_x,&from_y,to_x,to_y,x_differ,&captured);
		if(return_value<=0)
			return return_value;
	}
	if(board[from_x][from_y]==black_king){ //hareketin x ekseninde oldugu durumlarda normal tas iken kral tasina dönme durumlari ile basa cikan kisim
		king_recursive(p,board,&from_x,&from_y,&captured);
		return captured;
	}
	if(board[from_x][from_y]==white_king){ // yukardaki ile ayni
		king_recursive(p,board,&from_x,&from_y,&captured);
		return captured;
	}
	if(kosul_sayac>0){
		return captured;}
	}
	else   //eger hamleye izin verilmiyorsa
	return -2;
}
void sample_game_2(){
	
	piece board[8][8];
	
	player a=white;
	player b=black;
	int i,j,n;
	int initer_board[8][8]={     //gifteki tahta ile dolduruldu(ödev tahtasi)
					 {4,4,4,4,4,4,4,4},
					 {4,4,0,0,0,0,4,4},
					 {4,0,0,0,0,4,0,0},
					 {0,0,0,4,4,0,4,0},
					 {4,4,1,1,1,0,1,1},
					 {1,1,1,1,1,4,1,1},
					 {4,4,1,1,1,1,4,4},
					 {4,4,4,4,4,4,4,4}
					 };
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			board[i][j]=initer_board[i][j];
		}
	}

	n=move(board,5,1,4,1,b);
	if(n==0)
		display_board(board);
	n=move(board,3,1,5,1,a);
	if(n==0)
		display_board(board); //sirala oyun hamleleri girilir eger otonom bir tas yemem durumu varsa bunun icin ekstra bir move fonksiyonu cagrilmaz
	n=move(board,4,3,3,3,b);  //cünkü otonom sekilde yapilir
	if(n==0)
		display_board(board);
	n=move(board,4,5,4,3,a);
	if(n==0)
		display_board(board);
	n=move(board,3,3,3,1,b);
	if(n==0)
		display_board(board);
	n=move(board,1,2,1,0,a);
	if(n==0)
		display_board(board);
	n=move(board,5,3,4,3,b);
	if(n==0)
		display_board(board);
	n=move(board,5,1,5,3,a);
	if(n==0)
		display_board(board);
	n=move(board,4,3,3,3,b);
	if(n==0)
		display_board(board);
	n=move(board,2,3,4,3,a);
	if(n==0)
		display_board(board);
	n=move(board,5,6,5,5,b);
	if(n==0)
		display_board(board);
	n=move(board,7,5,4,5,a);
	if(n==0)
		display_board(board);
	n=move(board,4,6,4,4,b);
	if(n==0)
		display_board(board);
}
void init_board(piece board[][8]){
	
	int i,j;
	int initer_board[8][8]={
					 {4,4,4,4,4,4,4,4},
					 {0,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0},
					 {4,4,4,4,4,4,4,4},
					 {4,4,4,4,4,4,4,4},
					 {1,1,1,1,1,1,1,1},
					 {1,1,1,1,1,1,1,1},
					 {4,4,4,4,4,4,4,4}
					 };
			
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			board[i][j]=initer_board[i][j];
		}
	}		 
}
void display_board(piece board[][8]){ //oyun mapini bastirma fonksiyonu
	
	int i,j;
	
	printf("  ");
	for(i=0;i<8;i++)
		printf("%d",i);
	printf("\n");
	for(i=0;i<8;i++){
		printf("%d ",i);
		for(j=0;j<8;j++){
			if(board[i][j]==empty)
				printf("-");
			else if(board[i][j]==black_man)
				printf("b");
			else if(board[i][j]==black_king)
				printf("B");
			else if(board[i][j]==white_man)
				printf("w");
			else if(board[i][j]==white_king)
				printf("W");
		}
		printf("\n");
	}
}
int main(){
	
	piece board[8][8];
	
	sample_game();
	
//	sample_game_2();

	return 0;
}
void sample_game(){ //bu fonksiyon istedigimi bir oyunu tekrar oynamamiza yarar ,taklit etmemize ikili bir sekilde 
	
	piece board[8][8];
	
	init_board(board);
	int from_x,from_y,to_x,to_y;
	player sira=white;
	int kontrol=-1;
	int n=-1;
	
	while(kontrol==-1){
	while(n==-2 || n==-1){ //oyuncu gecerli hamle yapmaz ise hakki gitmez yeni bir hamle istenir
	printf("oynamak istediginiz tasi ve yeri koordinatlar arasi bosluk birakarak giriniz:");
	scanf("%d %d %d %d",&from_x,&from_y,&to_x,&to_y);
	n=move(board,from_x,from_y,to_x,to_y,sira);
	if(n==-2 || n==-1)
		printf("yanlis hamle lütfen ");
	}
	if(sira==white && n!=-2 && n!=-1){ //eger hamle gecerli ise sira degisir
		
		display_board(board);
		sira=black;}
	else if(sira==black && n!=-2 && n!=-1){ // eger hamle gecerli ise sira degisir
		
		display_board(board);
		sira=white;}
	kontrol=check_end_of_game(board);
	n=-1;
	}
	if(kontrol==10)
		printf("white wins");
	if(kontrol==20)
		printf("black wins");
}
