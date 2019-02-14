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

#include <stdio.h>
#include "hw4_lib.h"
#include "hw4_io.h"


double f(double a){
	
	return a*a;
	
}

int main(void){
	
		
	double integral2,turev1,turev2;

	
	derivatives(f,6,0.0001,&turev1,&turev2);
	printf("1.türev:%lf     2.türev:%lf\n",turev1,turev2);
	
	
	integral2=integral(f,3,4,0.0001);
	printf("verilen aralık için(mainde verildi)hesaplanan integral:%lf\n",integral2);
	

	return 0;
	
}



