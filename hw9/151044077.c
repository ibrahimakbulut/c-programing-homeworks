/*                                                              İBRAHİM AKBULUT
                                                                  151044077  
																                                                      
	when in the init.txt the water level is below 1500 milliliters, it usually does not reach the flower, 
	so changing the water level in the txt file from 1500 to higher will increase your chances of reaching the rare flower            */

#include <stdio.h>
#include <stdlib.h> //just for rand() and calloc() functions
#include <time.h>   //just for srand() functions

typedef struct{     
	char** map;
	int width;
	int height;
	int flower_x;
	int flower_y;
	
}Forest;
typedef struct{
	
	int botanist_x;
	int botanist_y;
	int water_bottle_size;
}Botanist;

void print_map(Forest forest){
	int i,j;
	
	for(i=0;i<forest.height;i++){
		for(j=0;j<forest.width;j++){
			printf("%c ",forest.map[i][j]);
		}
		printf("\n");
	}
	
}
void init_game (Forest* forest, Botanist* botanist){
	
	int volume_of_water;
	int height1,width1,i,j,k;
	char map_size[10];
	char height[5],width[5];
	char *line;
	char bos[6];
	
	FILE *fpr;
	
	fpr=fopen("init.txt","r");
	fscanf(fpr,"%d",&botanist->water_bottle_size);
	
	fscanf(fpr,"%s",map_size); //this reads 2th row as NN,NN
	
	for(i=0;map_size[i]!=',';i++){
		height[i]=map_size[i];
	}
	height[i]='\0';       //these two for loop are divide 2th row to 2 that mean as a height and width
	
	for(j=i+1;map_size[j]!='\0';j++){
		width[j-i-1]=map_size[j];
	}
	sscanf(height,"%d",&height1); //height and width are keep as string so that we cover them integer to use.
	sscanf(width,"%d",&width1);
	
	forest->width=width1;  //now height and width are can be written to forest as integer.
	forest->height=height1;//after they(height and with) were written, map is read and initilized to forest line by line.
	line=(char *)calloc((2*width1+1),sizeof(char));//to allocate memory dynamically for line(row of map).we allocate 2*width+1 because,
	//number of elemet of a line with comma in the txt file is 2*width.and there is two character in the end of line as '\n' and '\0' 
	forest->map=(char**)calloc(height1,sizeof(char*));//to allocate memory dynamically for whole map
	
	for(i=0;i<height1;i++){
		forest->map[i]=(char*)calloc(width1,sizeof(char));//to allocate memory dynamically for a row of map
	}
	fgets(bos,10,fpr);
	j=0;
	while(fgets(line,2*width1+1,fpr)!=NULL){ //loop continues as long as file is not in the end.
		for(i=0,k=0;(i<2*width1+1 && line[i]!='\n');i++){//this loop assign every element of line  except for comma,'\n','\0' to row of map
			if(line[i]!=','){
					forest->map[j][k]=line[i];
					k+=1;
			}
			if(line[i]=='B'){ //thih is where that coordinate of botanist is found
				botanist->botanist_x=j;
				botanist->botanist_y=k-1;
			}
			if(line[i]=='F'){ //this is where that coordinate of rare flower is found
				forest->flower_x=j;
				forest->flower_y=k-1;
			}
		}
		j++;
	}
	fclose(fpr);
}

int coordinate_permission(Forest forest,int x_coordinate,int y_coordinate){//this function checks coordinate that want to go is legal or not.
	if((x_coordinate<forest.height && x_coordinate>=0) && (y_coordinate<forest.width && y_coordinate>=0))
		if(forest.map[x_coordinate][y_coordinate]!='#')
			return 1;
		else 
			return 0;
	else
		return 0;
}
void updater(Forest* forest,Botanist* botanist,int update_x_coordinate,int update_y_coordinate){//this function apply changes that occurs while travelling
	forest->map[botanist->botanist_x][botanist->botanist_y]=' ';
	if(forest->map[update_x_coordinate][update_y_coordinate]!='F')//if new coordinates are not coordinate of rare flower
		forest->map[update_x_coordinate][update_y_coordinate]='B';
	botanist->botanist_x=update_x_coordinate;
	botanist->botanist_y=update_y_coordinate;
	botanist->water_bottle_size-=1; //water is reduced by 1 milliliter per step
}
void search(Forest* forest,Botanist* botanist){
	int random;

	if(botanist->water_bottle_size<=0){//if water of botanist is run out 
		print_map(*forest);
		printf("Help! I am on (%d,%d) !\n",botanist->botanist_x,botanist->botanist_y);

	}
	else{
		random=rand()%4; //to determine a random motion.
		if(random==0){//move downm
			if(coordinate_permission(*forest,botanist->botanist_x+1,botanist->botanist_y)){//if new coordinate is legal
				updater(forest,botanist,botanist->botanist_x+1,botanist->botanist_y);
				if(forest->map[botanist->botanist_x][botanist->botanist_y]=='F'){//if new coordinate is coordinate of rare flower
					print_map(*forest);
					printf("I have fount it (%d,%d) !\n",botanist->botanist_x,botanist->botanist_y);
				}
				else{//if new coordinate is not coordinate of rare flower then search function is called again
					search(forest,botanist);}
			}
			else//if new coordinate is not legal then search functiın is called again
				search(forest,botanist);
			}
		 else if(random==1){//move up
			if(coordinate_permission(*forest,botanist->botanist_x-1,botanist->botanist_y)){
				updater(forest,botanist,botanist->botanist_x-1,botanist->botanist_y);
				if(forest->map[botanist->botanist_x][botanist->botanist_y]=='F'){
					print_map(*forest);
					printf("I have fount it (%d,%d) !\n",botanist->botanist_x,botanist->botanist_y);
				}
				else{
					search(forest,botanist);}
			}
			else
				search(forest,botanist);
		}
		 else if(random==2){//move right
			if(coordinate_permission(*forest,botanist->botanist_x,botanist->botanist_y+1)){
				updater(forest,botanist,botanist->botanist_x,botanist->botanist_y+1);
				if(forest->map[botanist->botanist_x][botanist->botanist_y]=='F'){
					print_map(*forest);
					printf("I have fount it (%d,%d) !\n",botanist->botanist_x,botanist->botanist_y);
				}
				else{
					search(forest,botanist);}
			}
			else
				search(forest,botanist);
		}
		else if(random==3){//move left
			if(coordinate_permission(*forest,botanist->botanist_x,botanist->botanist_y-1)){
				updater(forest,botanist,botanist->botanist_x,botanist->botanist_y-1);
				if(forest->map[botanist->botanist_x][botanist->botanist_y]=='F'){
					print_map(*forest);
					printf("I have fount it (%d,%d) !\n",botanist->botanist_x,botanist->botanist_y);
				}
				else{
					search(forest,botanist);}
			}
			else
				search(forest,botanist);
		}
	}
}



int main(){
	
	srand(time(NULL));

	Botanist botanist;
	Forest forest;

	init_game(&forest,&botanist);
	
	print_map(forest);
	printf("searching...\n");
	
	search(&forest,&botanist);
	
	return 0;
}
