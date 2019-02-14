#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 struct customer{
	
	char surname[100];
	char name[100];
	char gender[10];
	int age;
	
	struct customer *next;
};

struct room{
	
	int room_number,capacity,floor_number,size;
	
	struct  customer * customer;
	struct room *next;
};
void remove_room(struct room** room_head,int room_for_remove){
	
	struct room *last,*head;
	int flag=0;
	
	last=*room_head;
	head=*room_head;
	while((*room_head)->room_number!=room_for_remove){
		last=*room_head;
		*room_head=(*room_head)->next;
		flag+=1;
	}
	if(flag!=0){

		last->next=(*room_head)->next;
		*room_head=head;
	}
	else{
		*room_head=(*room_head)->next;}
}
void add_room_to_end(struct room* room_head,int room_number,int capacity,int floor_number){
	
	struct room* new_room;
	new_room=room_head;
	
	while(new_room->next!=NULL){ //comes to the end of the connected list
		new_room=new_room->next;
	}
	new_room->next=(struct room*)calloc(1,sizeof(struct room));   //reserved for list end
	new_room=new_room->next;
	new_room->room_number=room_number;    
	new_room->capacity=capacity;
	new_room->floor_number=floor_number;
	new_room->customer=NULL;
	new_room->next=NULL;	
}
void add_room_after_room_number(struct room* customer_head,int room_number,int capacity,int floor_number,int after_room){
	struct room* new_room,*temp;
	new_room=customer_head;
	int flag=0;
	
	while(new_room->next!=NULL){  
		if(new_room->room_number==after_room){  //if there is a given room number, place the new room after this number
			temp=new_room->next;
			new_room->next=(struct room*)calloc(1,sizeof(struct room));
			new_room=new_room->next;
			new_room->room_number=room_number;
			new_room->capacity=capacity;
			new_room->floor_number=floor_number;
			new_room->customer=NULL;
			new_room->next=temp;
			flag=1;
			break;
		}

		new_room=new_room->next;
	}
	if(flag==0)    //if there is no room at the given number, it adds the room to the end of the list
	add_room_to_end(new_room,room_number,capacity,floor_number);
	
}
void show_vacancy(struct room* rooms){          //show all empty rooms
	
	while(rooms!=NULL){
		if(rooms->customer==NULL)
			printf("-Room %d is vacancy\n",rooms->room_number);
		
		rooms=rooms->next;
	}
}
void get_by_floor(struct room* rooms,int floor_number){    //       show rooms on the given floor
	
	while(rooms!=NULL){          
		if(rooms->floor_number==floor_number)
			printf("Room %d is on %d'th floor\n",rooms->room_number,rooms->floor_number);
		
		rooms=rooms->next;
	}
}
void printf_list(struct room * rooms){
	struct customer* customers;
	while(rooms!=NULL){
		printf("Room %d(Floor %d-capacity %dx):\n",rooms->room_number,rooms->floor_number,rooms->capacity);
		
		if(rooms->customer!=NULL){
		if(rooms->customer->next==NULL){
			printf("->%s %s (%d-%s)\n",rooms->customer->name,rooms->customer->surname,rooms->customer->age,rooms->customer->gender);
	}
		else{
			customers=rooms->customer;
		while(rooms->customer->next!=NULL){
			printf("->%s %s (%d-%s)\n",rooms->customer->name,rooms->customer->surname,rooms->customer->age,rooms->customer->gender);
			rooms->customer=rooms->customer->next;
		}
		printf("->%s %s (%d-%s)\n",rooms->customer->name,rooms->customer->surname,rooms->customer->age,rooms->customer->gender);
		printf("\n");
		rooms->customer=customers;
		}
		}
		else
			printf("->Empty\n");
		rooms=rooms->next;
	}
}
void add_customer_to_end(struct customer* customers,int age,char name[],char surname[],char gender[]){

		strcpy(customers->name,name);
		strcpy(customers->surname,surname);  //this function adds the information of the customer at the end of the partial list
		strcpy(customers->gender,gender);
		customers->age=age;
	
}
void link_customers_to_room(struct room *rooms,struct customer *customers){
	
	rooms->customer=customers;  //this function links the partial list given to the desired room
}
void read_and_construct(struct room *rooms){
	
	FILE *fpw,*fpw1;
	
	struct room *linked_head,*current;
	struct customer *head,*head1,*link_head;
	
	linked_head=rooms->next;
	current=rooms;
	
	int room_number,capacity,floor,i;
	char customer_line[100],name[100],surname[100],gender[10];
	int flag=0;
	int age;
	
	fpw=fopen("rooms.txt","r");
	
	while(fscanf(fpw,"%d,%d,%d",&room_number,&capacity,&floor)!=EOF){
	
		rooms=rooms->next;
		rooms->room_number=room_number;
		rooms->capacity=capacity;
		rooms->floor_number=floor;
		head=(struct customer*)calloc(1,sizeof(struct customer));
		head->next=(struct customer*)calloc(1,sizeof(struct customer));
		head1=head->next;

		fpw1=fopen("customers.txt","r");
		rooms->size=0;
		
		while(fscanf(fpw1,"%d,%s %s",&room_number,name,surname)!=EOF){
		
			if(room_number==rooms->room_number){//reads the customer file and processes for the room number match
				head=head->next;
				rooms->size+=1;
				flag+=1;
				i=0;
				while(surname[i]!=','){
					i++;
				}
		
				sscanf(&surname[i+1],"%d,%s",&age,gender);
				surname[i]='\0';
				add_customer_to_end(head,age,name,surname,gender); //partial list addition

				if(flag==1){
				head1=head;
				}
				head->next=(struct customer*)calloc(1,sizeof(struct customer));
			}
		}
		if(flag==0)
			head=NULL;
		else
			head->next=NULL;
	
		fclose(fpw1);
		link_customers_to_room(rooms,head1);
		if(flag!=0)
			link_customers_to_room(rooms,head1); //partial list added to the room
		else
			link_customers_to_room(rooms,NULL);
	
			
		flag=0;
		
		rooms->next=(struct room *)calloc(1,sizeof(struct room));
		
	}
	rooms->next=NULL;
	
	fclose(fpw);
}

int main(){
	
	struct room * rooms;
	struct customer *partial_list;
	
	rooms=(struct room*)calloc(1,sizeof(struct room));			//this code part  can not be changed, if you change it  the functions does not work correctly
	rooms->next=(struct room*)calloc(1,sizeof(struct room));

	read_and_construct(rooms);  //this function reads room.txt and construct the list of rooms and others
	rooms=rooms->next;
//-------------------------------------------------------------------------------------	
	
	
	remove_room(&rooms,101); 			//in this part ,you can call all desired function in this part as you like and add or substract room to list.
	add_room_after_room_number(rooms,199,4,9,105);  // The "room" parameter is common to all functions and represents the list head
	add_room_to_end(rooms,10,5,6);
	printf_list(rooms);

	add_room_after_room_number(rooms,199,4,9,101); //Adds new room to the end because 101 rooms are deleted

	remove_room(&rooms,10);
	show_vacancy(rooms);
	get_by_floor(rooms,6);

	printf_list(rooms);
	
	return 0;
}
