#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h> //for gettimeofday(&t,...)
#include <math.h>     //for sqrt()


struct number_node{
	int whole_part;
	char fraction_part[3];
	
	struct number_node * next;
	
};

double get_time_ms(){ //this is function to get time
	
struct timeval t;
gettimeofday(&t, NULL);
return (t.tv_sec + (t.tv_usec / 1000000.0)) * 1000.0;
}
int prime(int number){
	
	int i;
	double number1=number;
	if(number==1) //the smallest prime number is 2 so 1 is not
		return 0;
	if(number==2)	
		return 1;
	for(i=2;i<=sqrt(number1);i++){ //we control until the square root of the number
		if(number%i==0)
			return 0;
	}
	return 1;
}
int  read(FILE *fpr,int *whole_part,char* fraction_part){//this function read only one line from file and return them as pointer value
	
	
	if(fscanf(fpr,"%d,%s",whole_part,fraction_part)!=EOF){//while there is line to read
		return 1;
	}
	else //when end of file
		return 0;
}

void find_and_show(){
	
	
	struct number_node *number_arr,*head,*current;
	int size,capasity,i,j;
	double start,time_50,time_75,time_100;
	size=0;i=0;j=0;
	FILE *fpr,*fpw;
	printf("Finding prime number,then they are written to output files...");
	
	//calculation of finding and writing prime numbers can depend on your computer stuation(system)
	
	//					THIS PART FOR DYNAMİC ARRAY
	
	fpr=fopen("data.txt","r");
	fpw=fopen("output_prime_dynamic_array.txt","w");
	
	number_arr=(struct number_node*)calloc(1000,sizeof(struct number_node));//as a start we allocate memory for 1000 number_arr
	capasity=1000;
	
	start=get_time_ms();//we are recording the time when we started reading the file
	
	while(read(fpr,&number_arr[size].whole_part,number_arr[size].fraction_part)!=0){
	if(number_arr[size].whole_part==500000) //It is determined when numbers up to 500000 are checked
		time_50=get_time_ms()-start;
	else if(number_arr[size].whole_part==750000) //It is determined when numbers up to 750000 are checked
		time_75=get_time_ms()-start;
	else if(number_arr[size].whole_part==1000000) //It is determined when numbers up to 1000000 are checked
		time_100=get_time_ms()-start;
	if(prime(number_arr[size].whole_part)){
		printf("%d,%s\n",number_arr[size].whole_part,number_arr[size].fraction_part);
		size+=1;
	}
	if(size+1>=capasity){//if size reach capacity
		number_arr=(struct number_node*)realloc(number_arr,2*capasity*sizeof(struct number_node)); //the capacity is doubled meantime values are keep
	capasity*=2;
	}
	}
	fprintf(fpw,"Prime numbers up to 500,000 in %lf milliseconds were found and shown\n",time_50); //check times for prime numbers have been found previously now written to the top of the output file
	fprintf(fpw,"Prime numbers up to 750,000 in %lf milliseconds were found and shown\n",time_75);
	fprintf(fpw,"Prime numbers up to 1,000,000 in %lf milliseconds were found and shown\n",time_100);
	

	start=get_time_ms(); //we are recording the time when we started writing prime numbers to output file
	while(j<size){
		fprintf(fpw,"%d,%s\n",number_arr[j].whole_part,number_arr[j].fraction_part); //we write prime number to outputfile
		j+=1;
	}
	fprintf(fpw,"The writing time of prime numbers up to 1 million took %lf milliseconds",get_time_ms()-start);//we write the time to write prime numbers to the end of output file
	fclose(fpw);
	fclose(fpr);
	
	
	//						THIS PART FOR LİNKED_LİST
	fpr=fopen("data.txt","r");
	fpw=fopen("output_prime_linkedList.txt","w");
	
	
	current=(struct number_node*)calloc(1,sizeof(struct number_node));//We allocate 1 cell space
	head=current; //We keep it(allocated cell space) for later use as a linked list.
	
	start=get_time_ms();//we are recording the time when we started reading the file
	
	while(read(fpr,&current->whole_part,current->fraction_part)){
			
		if(current->whole_part==500000){  //It is determined when numbers up to 500000 are checked
			time_50=get_time_ms()-start;
		}
		else if(current->whole_part==750000){ //It is determined when numbers up to 750000 are checked
			time_75=get_time_ms()-start;
		}
		else if(current->whole_part==1000000){ //It is determined when numbers up to 1000000 are checked
			time_100=get_time_ms()-start;
		}
		if(prime(current->whole_part)){
			printf("%d,%s\n",current->whole_part,current->fraction_part);
			current->next=(struct number_node*)calloc(1,sizeof(struct number_node));
			current=current->next;
		}
	}
		current->next=NULL;
		
		fprintf(fpw,"Prime numbers up to 500,000 in %lf milliseconds were found and shown\n",time_50);//check times for prime numbers have been found previously now written to the top of the output file
		fprintf(fpw,"Prime numbers up to 750,000 in %lf milliseconds were found and shown\n",time_75);
		fprintf(fpw,"Prime numbers up to 1,000,000 in %lf milliseconds were found and shown\n",time_100);
		
		start=get_time_ms();//we are recording the time when we started writing prime numbers to output file
	
		while(head->next!=NULL){
			fprintf(fpw,"%d,%s\n",head->whole_part,head->fraction_part);//we write prime number to outputfile
			head=head->next;
		}
		fprintf(fpw,"The writing time of prime numbers up to 1 million took %lf milliseconds",get_time_ms()-start);//we write the time to write prime numbers to the end of output file
		
		fclose(fpr);
		fclose(fpw);
		
	free(number_arr);
	
}
int main(){
	

	find_and_show();
	
	
	return 0;
}
