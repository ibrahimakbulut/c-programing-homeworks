#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

int getint(int mini,int maxi){
	
	int right_int;
	
	do{
		scanf("%d",&right_int);
	}while(right_int<mini || right_int>maxi); //sinirlar icinde bir deger alana kadar dongu devam eder.
	
	return right_int;
}
int numberGeneratorBetweenRange(int min,int max){
	int numbers_difference,number;
	
	numbers_difference=max-min; //iki sayi farki 
	number=rand()%numbers_difference; //iki sayinin farkinin modundan rastgele deger üretiyoruz
	if(number==0){
		number=rand()%numbers_difference; //minimum iki degeri burada elde edebiliyoruz
		number=number+min;
	}
	else 
		number=min+number+1; //burada ise minimum iki deger disinda maximum degere kadar tüm degerleri elde ediyoruz
	return number;
}
void countOccurrence(){
	int big_number,search_number,search_digit_counter,occurence_count,i,a;
	printf("Big Number:");
	scanf("%d",&big_number);
	printf("Search Number:");
	scanf("%d",&search_number);
	
	for(i=search_number,search_digit_counter=0;i>0;search_digit_counter++){ //search sayimizin kac basamakli oldugunu buluruz
		i=i/10;
	}
	occurence_count=0;
	i=big_number;
	a=pow(10,(double)search_digit_counter); //search sayimiz 111 ise a 1000 olacaktir
	while(i>0){
		if(i%a==search_number)   //ornegin big number 1111 ise 1111%1000==111 olacaktir yani big numberi elde etmis oluruz
			occurence_count+=1;
		i=i/10;	
	}
	printf("Occurence: %d\n",occurence_count);
}
void horseRacingGame(){
	
	int horse_number,horse_running_time,best_time,best_time_index,user_choice,i,j;
	
	horse_number=numberGeneratorBetweenRange(3,5); //kac at oldugu belirlenir
	printf("Number of Horse: %d\n",horse_number);
	printf("Horse Number: ");
	user_choice=getint(1,horse_number); //kullanicidan 1 ile at sayisi arasinda sayi girmesi yani atini secmesi istenir
	horse_running_time=numberGeneratorBetweenRange(10,20); //birinci at'in derecesi belirlenir
	best_time=horse_running_time; //default olarak birinci at'in zamani en iyi secilir
	best_time_index=1;
	printf("Horse 1:");
	for(i=1;i<=horse_running_time;i++){
		printf("-");
	}
	printf("\n");
	
	for(i=2;i<=horse_number;i++){
		horse_running_time=numberGeneratorBetweenRange(10,20);//yeni atin derecesi belirlenir
		if(horse_running_time==best_time && i>user_choice){
			best_time=horse_running_time;
		}
		else if(horse_running_time<=best_time){
			best_time_index=i;
			best_time=horse_running_time;
		}
		printf("Horse %d:",i);
		for(j=1;j<=horse_running_time;j++){
			printf("-");
		}
		printf("\n");
	}
	if(best_time_index==user_choice)
		printf("You win! Winner is Horse %d.\n",best_time_index);
	else
		printf("You lose! Winner is Horse %d.\n",best_time_index);
}
void triangleOfSequences(){
	
	int i,j,size,before_last_number,last_number;
	
	size=numberGeneratorBetweenRange(2,10);// ücgenin kenar uzunlugu belirlenir
	
	for(i=1;i<=size;i++){
		printf("%d ",i);
		before_last_number=i;
		for(j=1;j<i;j++){
			last_number=before_last_number+i; //i.satirdaki ekrana bastirilan sayi ve o satirdaki ilk sayi son sayi olur ve
			printf("%d ",last_number);	  //bir sonraki dongüde son sayi ekrana bastirilir
			before_last_number=last_number;
		}
		printf("\n");
	}
}
void menu(){
	
	int menu_option;
	
	do{
		printf("1. Horse Racing Game\n");
		printf("2. Occurrence Counter\n");
		printf("3. Triangle Of Sequences\n");
		printf("0. Exit\n");
		
		scanf("%d",&menu_option);
		
		switch(menu_option){
			
			case 1:
				horseRacingGame();
				break;
			case 2:
				countOccurrence();
				break;
			case 3:
				triangleOfSequences();
				break;
			default:
				break;
		}
	}while(menu_option!=0); //kullanici 0 girmedigi sürece menü gosterilmeye devam eder
}
int main(){
	
	srand(time(NULL));
	
	menu();
	
	return 0;
}
