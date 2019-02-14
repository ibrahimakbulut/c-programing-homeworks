/*
** hw4_io.c:
**
** The source file implementing input and output functions.
**
** Author: Yakup Genc. (c) 2018
**
** Revision: 2018.03.27.08.19
** 
*/


#include "hw4_io.h"
#include <stdio.h>



int read_polynomial3(double * a0, double * a1, double * a2, double * a3){
	
	printf("3. dereceden fonksiyonunuzun katsayilarini sirasi ile giriniz:\n");
	
	scanf("%lf",a3);
	scanf("%lf",a2);
	scanf("%lf",a1);
	scanf("%lf",a0);
	return 0;
	
}
int read_polynomial4(double * a0, double * a1, double * a2, double * a3, double * a4){
	
	printf("4. dereceden fonksiyonunuzun katsayilarini sirasi ile giriniz:\n");
	
	scanf("%lf",a4);
	scanf("%lf",a3);
	scanf("%lf",a2);
	scanf("%lf",a1);
	scanf("%lf",a0);
	
	return 0;
}
void write_polynomial3(double a0, double a1, double a2, double a3){
	
	if(a3>0){
		if((int)a3==a3)
			printf("%.0lfx^3",a3);
		else
			printf("%.1lfx^3",a3);
	}
	if(a3<0){
		if((int)a3==a3)
			printf("%.0lfx^3",a3);
		else
			printf("%.1lfx^3",a3);
	}
	if(a2>0){
		if((int)a2==a2)
			printf("+%.0lfx^2",a2);
		else
			printf("+%.1lfx^2",a2);
	}
	if(a2<0){
		if((int)a2==a2)
			printf("%.0lfx^2",a2);
		else
			printf("%.1lfx^2",a2);
	}
	if(a1>0){
		if((int)a1==a1)
			printf("+%.0lfx",a1);
		else
			printf("+%.1lfx",a1);
	}
	if(a1<0){
		if((int)a1==a1)
			printf("%.0lfx",a1);
		else
			printf("%.1lfx",a1);
	}
	if(a0>0){
		if((int)a0==a0)
			printf("+%.0lf",a0);
		else
			printf("+%.1lf",a0);
	}
	if(a0<0){
		if((int)a0==a0)
			printf("%.0lf",a0);
		else
			printf("%.1lf",a0);
	}
	printf("\n");		
}
void write_polynomial4(double a0, double a1, double a2, double a3, double a4){
	
	if(a4>0){
		if((int)a4==a4)
			printf("%.0lfx^4",a4);
		else
			printf("%.1lfx^4",a4);
	}
	if(a4<0){
		if((int)a4==a4)
			printf("%.0lfx^4",a4);
		else
			printf("%.1lfx^4",a4);
	}
	if(a3>0){
		if((int)a3==a3)
			printf("+%.0lfx^3",a3);
		else
			printf("+%.1lfx^3",a3);
	}
	if(a3<0){
		if((int)a3==a3)
			printf("%.0lfx^3",a3);
		else
			printf("%.1lfx^3",a3);
	}
	if(a2>0){
		if((int)a2==a2)
			printf("+%.0lfx^2",a2);
		else
			printf("+%.1lfx^2",a2);
	}
	if(a2<0){
		if((int)a2==a2)
			printf("%.0lfx^2",a2);
		else
			printf("%.1lfx^2",a2);
	}
	if(a1>0){
		if((int)a1==a1)
			printf("+%.0lfx",a1);
		else
			printf("+%.1lfx",a1);
	}
	if(a1<0){
		if((int)a1==a1)
			printf("%.0lfx",a1);
		else
			printf("%.1lfx",a1);
	}
	if(a0>0){
		if((int)a0==a0)
			printf("+%.0lf",a0);
		else
			printf("+%.1lf",a0);
	}
	if(a0<0){
		if((int)a0==a0)
			printf("%.0lf",a0);
		else
			printf("%.1lf",a0);
	}
	printf("\n");
}


