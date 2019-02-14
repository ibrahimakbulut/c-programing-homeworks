#include <stdio.h>

typedef enum{monday=2,tuesday=3,wednesday=4,thursday=5,friday=6,saturday=0,sunday=1}days;
typedef enum{jenuary=1,february=4,march=4,april=0,may=2,june=5,july=0,august=3,september=6,october=1,november=4,december=6}mounths;

int gun_bulucu(int day,int mounth,int year){
 
 //DC=LSTD/4+DOM+VOM-LEAP_YEAR_CODE+COC . DC is the day code.that code matched type days.
	
	
	int dc,lstd,dom,vom,coc,leap_year_code;
	
	
	if(year%4==0){
		if(year%100==0){
			if(year%400==0 && year%4000!=0 && (mounth==1 || mounth==2))
				leap_year_code=1;    //leap year_code is 1 when mounth is february or jenuary.
			else
				leap_year_code=0;
		}
		else if(mounth==1 || mounth==2)
			leap_year_code=1;
		else
			leap_year_code=0;
	}
	else				
		leap_year_code=0;	//if year is not leap year then code is alredy 0
	
	lstd=year%100;  //last two digits of year
	dom=day;       //day of mounth

	if(mounth==1)
		vom=jenuary; //every mounth have a key value that defined as mounths type
	else if(mounth==2)
		vom=february;
	else if(mounth==3)
		vom=march;
	else if(mounth==4)
		vom=april;
	else if(mounth==5)
		vom=may;
	else if(mounth==6)
		vom=june;
	else if(mounth==7)
		vom=july;
	else if(mounth==8)
		vom=august;
	else if(mounth==9)
		vom=september;
	else if(mounth==10)
		vom=october;
	else if(mounth==11)
		vom=november;
	else if(mounth==12)
		vom=december;
	
	if(year>=2100 || year<1700){ //coc is century code of year.1700s=4,1800s=2,1900s=0,2000s=6.
		if(year>=2100){
			while(year>=2100){
				year-=400;
			}
		if(year<1800 &&year>=1700)
			coc=4;
		if(year<1900 && year>=1800)
				coc=2;
		if(year<2000 && year>=1900)
			coc=0;
		if(year<2100 && year>=2000)
			coc=6;
		}
		if(year<1700){
			while(year<1700){
				year+=400;
			}
		if(year<1800 &&year>=1700)
			coc=4;
		if(year<1900 && year>=1800)
				coc=2;
		if(year<2000 && year>=1900)
			coc=0;
		if(year<2100 && year>=2000)
			coc=6;
		}
	}
	if(year<1800 &&year>=1700)
		coc=4;
	if(year<1900 && year>=1800)
			coc=2;
	if(year<2000 && year>=1900)
		coc=0;
	if(year<2100 && year>=2000)
		coc=6;
	dc=(lstd/4+dom+vom+coc-leap_year_code+lstd)%7;
	return dc;
}
void print_day_name(FILE *fp,int day_code){ //this function prints name of day depends on day_code parameter
	
	if(day_code==monday)
		fprintf(fp,"Monday");
	else if(day_code==tuesday)
		fprintf(fp,"Tuesday");
	else if(day_code==wednesday)
		fprintf(fp,"Wednesday");
	else if(day_code==thursday)
		fprintf(fp,"Thursday");
	else if(day_code==friday)
		fprintf(fp,"Friday");
	else if(day_code==saturday)
		fprintf(fp,"Saturday");
	else if(day_code==sunday)
		fprintf(fp,"Sunday");		
}
void print_mounth(FILE *fp,int mounth){ //this function prints name of mounth depends on mounth parameter
	
	
	if(mounth==1)
		fprintf(fp,"January");
	else if(mounth==2)
		fprintf(fp,"February");
	else if(mounth==3)
		fprintf(fp,"March");
	else if(mounth==4)
		fprintf(fp,"April");
	else if(mounth==5)
		fprintf(fp,"May");
	else if(mounth==6)
		fprintf(fp,"June");
	else if(mounth==7)
		fprintf(fp,"July");
	else if(mounth==8)
		fprintf(fp,"August");
	else if(mounth==9)
		fprintf(fp,"September");
	else if(mounth==10)
		fprintf(fp,"October");
	else if(mounth==11)
		fprintf(fp,"November");
	else if(mounth==12)
		fprintf(fp,"December");
}
int gun_sinir(int start_mounth,int start_year){ // this function determines how many days a month
	int kosul_day;

	if(start_mounth==1)
		kosul_day=31;
	else if(start_mounth==2){ //if mounth is february and year is a leap year then it includes 29 day.else 28 day.
		if(start_year%4==0){
			if(start_year%100==0){
				if(start_year%400==0 && start_year%4000!=0)
					kosul_day=29;
				else
					kosul_day=28;
			}
			else
				kosul_day=29;
		}
		else
			kosul_day=28;
	}
	else if(start_mounth==3)
		kosul_day=31;
	else if(start_mounth==4)
		kosul_day=30;
	else if(start_mounth==5)
		kosul_day=31;
	else if(start_mounth==6)
		kosul_day=30;
	else if(start_mounth==7)
		kosul_day=31;
	else if(start_mounth==8)
		kosul_day=31;
	else if(start_mounth==9)
		kosul_day=30;
	else if(start_mounth==10)
		kosul_day=31;
	else if(start_mounth==11)
		kosul_day=30;
	else if(start_mounth==12)
		kosul_day=31;	
	
	return kosul_day;
	
}
void read_write_new_days(){
	
	int day,mounth,year,gun_adi;
	char c1,c2,c3;
	char line[1000];
	FILE *fpr,*fpw;
	
	fpr=fopen("input_date.txt","r");
	fpw=fopen("new_date.txt","w");
	
	while(fgets(line,1000,fpr)!=NULL){ //read while there is character
		sscanf(line,"%d %c %d %c %d",&day,&c1,&mounth,&c2,&year); //line includes a string dd / MM / YYYY.Then divide 5 part./ parts will not be used.
		gun_adi=gun_bulucu(day,mounth,year);//name of day(code of day) is found in this step
		print_day_name(fpw,gun_adi);
		fprintf(fpw," , %d ",day);
		print_mounth(fpw,mounth);
		fprintf(fpw," , %d\n",year);
	}
	
	fclose(fpr);
	fclose(fpw);
}
void write_dates(int start_day,int start_mounth,int start_year,int finish_day,int finish_mounth,int finish_year){
	int i,j,k,kosul_day;
	
	FILE *fp;
	
	fp=fopen("input_date.txt","w");
	
	
	if(start_year!=finish_year){ // if start and finish years are not equal
	kosul_day=gun_sinir(start_mounth,start_year);
	for(j=start_day;j<=kosul_day;j++){ //first mounth is completed mean printed
		if(j<=9)
			fprintf(fp,"0%d / %d / %d \n",j,(int)start_mounth,start_year);
		else
			fprintf(fp,"%d / %d / %d \n",j,(int)start_mounth,start_year);
	}
	for(i=start_mounth+1;i<=12;i++){ //then the year that include start mounth is completed mean printed
		
		kosul_day=gun_sinir(i,start_year);
		for(j=1;j<=kosul_day;j++){
			if(j<=9)
				fprintf(fp,"0%d / %d / %d \n",j,i,start_year);
			else
				fprintf(fp,"%d / %d / %d \n",j,i,start_year);
		}
	}
	for(i=start_year+1;i<finish_year;i++){ //if there are years that is not start or finish year,they are completed mean printed in this function
		for(j=1;j<=12;j++){
			kosul_day=gun_sinir(j,i);
			for(k=1;k<=kosul_day;k++){
				if(k<=9)
					fprintf(fp,"0%d / %d / %d \n",k,j,i);
				else
					fprintf(fp,"%d / %d / %d \n",k,j,i);
					
			}
		}
	}
	for(j=1;j<finish_mounth;j++){ 
		kosul_day=gun_sinir(j,finish_year);
		for(k=1;k<=kosul_day;k++){
			if(k<=9)
				fprintf(fp,"0%d / %d / %d\n",k,j,finish_year);
			else
				fprintf(fp,"%d / %d / %d \n",k,j,finish_year);
		}
	}
	kosul_day=gun_sinir(finish_mounth,finish_year);
	for(k=1;k<=finish_day;k++){
		if(k<=9)
			fprintf(fp,"0%d / %d / %d \n",k,finish_mounth,finish_year);
		else
			fprintf(fp,"%d / %d / %d \n",k,finish_mounth,finish_year);
	}	
	}
	if(start_year==finish_year && (start_mounth!=finish_mounth)){//if start and finish years equal and mounths are not.
	kosul_day=gun_sinir(start_mounth,start_year);
	for(j=start_day;j<=kosul_day;j++){
		if(j<=9)
			fprintf(fp,"0%d / %d / %d \n",j,(int)start_mounth,start_year);
		else
			fprintf(fp,"%d / %d / %d \n",j,(int)start_mounth,start_year);
	}
	for(i=start_mounth+1;i<finish_mounth;i++){
		
		kosul_day=gun_sinir(i,start_year);
		for(j=1;j<=kosul_day;j++){
			if(j<=9)
				fprintf(fp,"0%d / %d / %d \n",j,i,start_year);
			else
				fprintf(fp,"%d / %d / %d \n",j,i,start_year);
		}
	}
	kosul_day=gun_sinir(finish_mounth,finish_year);
	for(j=1;j<=finish_day;j++){
		if(j<=9)
			fprintf(fp,"0%d / %d / %d \n",j,(int)finish_mounth,finish_year);
		else
			fprintf(fp,"%d / %d / %d \n",j,(int)finish_mounth,finish_year);
	}
			
	}
	if(start_year==finish_year && start_mounth==finish_mounth){
	kosul_day=gun_sinir(start_mounth,start_year);
	for(j=start_day;j<=finish_day;j++){
		if(j<=9)
			fprintf(fp,"0%d / %d / %d \n",j,(int)finish_mounth,start_year);
		else
			fprintf(fp,"%d / %d / %d \n",j,(int)finish_mounth,start_year);
	}		
	}
	fclose(fp);
}
int main(){
	int s_day,s_mounth,s_year,f_day,f_mounth,f_year;
	printf("sirasi ile bosluk birakarak baslangic tarihini gun,ay,yil ornegin; 28 04(4) 2018 olarak giriniz:");
	scanf("%d%d%d",&s_day,&s_mounth,&s_year);
	printf("sirasi ile bosluk birakarak bitis tarihini gun,ay,yil ornegin; 28 04(4) 2018 olarak giriniz:");
	scanf("%d%d%d",&f_day,&f_mounth,&f_year);
	write_dates(s_day,s_mounth,s_year,f_day,f_mounth,f_year);
	//write_dates(22,2,2016,18,3,2016);
	read_write_new_days();
	

	return 0;
}
