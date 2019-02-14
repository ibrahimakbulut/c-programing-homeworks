#include <stdio.h>

void basamak_goster(int sayi){
	int i,basamak_sayac;
	
	for(i=sayi,basamak_sayac=0;i>0;basamak_sayac++){    //find out how many digits the number is
		i=i/10;
	}
	i=sayi;
	while(basamak_sayac>0){  //loop,it will rotate by the number of digits

		if(basamak_sayac==5){
			printf("The fifth digit is %d \n",i/10000); //we divide the number by the largest digit to find the leftmost digit
			i=i%10000;
		}
		else if(basamak_sayac==4){
			printf("The fourth digit is %d \n",i/1000);
			i=i%1000;	//this process keeps number(i)getting smaller
		}
		else if(basamak_sayac==3){
			printf("The third digit is %d \n",i/100);
			i=i%100;
		}
		else if(basamak_sayac==2){
			printf("The second digit is %d \n",i/10);
			i=i%10;
		}
		else
			printf("The firs digit is %d \n",i);
		
		basamak_sayac--; //Of course,while number is getting smaller digit number should be get smaller
	}	
}
int main(void){
	
	int sayi;
	
	do{
	printf("Enter the number:");
	scanf("%d",&sayi);
	}while(sayi<23 || sayi>98760);
	basamak_goster(sayi);
	return 0;
}
