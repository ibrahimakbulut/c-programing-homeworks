/*
** hw4_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018
**
** Revision: 2018.03.27.08.19
** 
*/

#include "hw4_lib.h"
#include <stdio.h>
#include "hw4_io.h"


double integral(double f(double x), double xs, double xe, double delta){
	
	double integral1=0;
	double a4,a3,a2,a1,a0;
	int derece;
	
	
	do{
	printf("kacinci dereceden bir fonksiyon gireceksiniz:"); //kullanici 3 yada 4 dereceli fonksiyon girmeye zorlaniyor
	scanf("%d",&derece);
	}while(derece!=3 && derece!=4);
	
	if(derece==3){
	
	read_polynomial3(&a3,&a2,&a1,&a0);
	write_polynomial3(a3,a2,a1,a0);
	while(xs<=xe){
		
		integral1=integral1+(a3*f(xs)*(xs)+a2*f(xs)+a1*f(xs)/xs+a0)*delta; //alan hesabi mantigiyla x nin y eksenine düsen degeriyle
		xs=xs+delta;							   //carpilip alanlarin toplanmasiyla integral bulunur
	}
	}
	else if(derece==4){
	
	read_polynomial4(&a4,&a3,&a2,&a1,&a0);
	write_polynomial4(a4,a3,a2,a1,a0);	
	while(xs<=xe){
		
		integral1=integral1+(a4*f(xs)*f(xs)+a3*f(xs)*(xs)+a2*f(xs)+a1*f(xs)/xs+a0)*delta;
		xs=xs+delta;
	}
	}	
	return integral1;
	
}
int derivatives(double f(double a), double x, double eps, double * d1, double * d2){ //bu fonksiyon her cagrildiginda kullanicidan
	
	int derece;								      //fonksiyonun katsayılarını alıyor
	double a4,a3,a2,a1,a0; 
	double turev1,turev2;
	
	
	do{
	printf("kacinci dereceden bir fonksiyon gireceksiniz:"); //verilen cevaba göre dogru read ve write fonksiyonlari cagiriliyor
	scanf("%d",&derece);
	}while(derece!=3 && derece!=4);
	
	if(derece==3){
	if(eps==0)
		return 0; //eps 0 olmasi gibi bir durumda direk programi bitirir
	read_polynomial3(&a0,&a1,&a2,&a3);
	write_polynomial3(a3,a2,a1,a0);
	turev1=((a3*f(x+eps)*(x+eps)+a2*f(x+eps)+a1*f(x+eps)/(x+eps)+a0)-(a3*f(x-eps)*(x-eps)+a2*f(x-eps)+a1*f(x-eps)/(x-eps)+a0))/(2*eps);
	*d1=turev1;
	//f fonksiyonunu surekli x^2 dusunup polinom parametrelerini gerekli sekilde carparak istedigimiz y degerini bulup formulde gerektigi gibi kullaniyoruz
	turev2=((a3*f(x+eps)*(x+eps)+a2*f(x+eps)+a1*f(x+eps)/(x+eps)+a0)+(a3*f(x-eps)*(x-eps)+a2*f(x-eps)+a1*f(x-eps)/(x-eps)+a0)-2*(a3*f(x)*(2*x)+a2*f(x)+a1*f(x)/x+a0))/(eps*eps);
	*d2=turev2;
	}
	else if(derece==4){
		
	if(eps==0)
		return 0;
	read_polynomial4(&a4,&a3,&a2,&a1,&a0);
	write_polynomial4(a4,a3,a2,a1,a0);
	turev1=((a4*f(x+eps)*f(x+eps)+a3*f(x+eps)*(x+eps)+a2*f(x+eps)+a1*f(x+eps)/(x+eps)+a0)-(a4*f(x-eps)*f(x-eps)+a3*f(x-eps)*(x-eps)+a2*f(x-eps)+a1*f(x-eps)/(x-eps)+a0))/(2*eps);
	*d1=turev1;
	
	turev2=((a4*f(x+eps)*f(x+eps)+a3*f(x+eps)*(x+eps)+a2*f(x+eps)+a1*f(x+eps)/(x+eps)+a0)+(a4*f(x-eps)*f(x-eps)+a3*f(x-eps)*(x-eps)+a2*f(x-eps)+a1*f(x-eps)/(x-eps)+a0)-2*(a3*f(x)*(x)+a2*f(x)+a1*f(x)/x+a0))/(eps*eps);
	*d2=turev2;
	}
	return 1;
}

