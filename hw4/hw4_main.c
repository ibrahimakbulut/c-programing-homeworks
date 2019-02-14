/*
** main.c:
**
** The test program for the homework.
**
** Author: Yakup Genc. (c) 2018
**
** Revision: 2018.03.27.08.14
** 
*/


#include <stdio.h>
#include "hw4_lib.h"  //hocam fonksiyonların yarisini yapmadigim icin bu main fonksiyonu compiler olmuyor cünkü bu dosyadaki fonksiyonu 
#include "hw4_io.h"   //implement etmedim o yüzden benim yaptigim fonksiyonları cagiran kendi main dosyamide klasöre koydum onu compiler 			      //ederek yaptigim fonksiyonlara bakmanizi rica ediyorum.hatta ben direk kendi main dosyami make file da compiler olarak
		      // gönderiyorum.



/*
** Testing derivative calculations..
**
*/
void test_compare_derivatives() {
	double f(double x) { return x*x; }
	double d1(double x) { return 2.0*x; }
	double d2(double x) { return 2.0; }
	double e1, e2;
	int res = compare_derivatives(f, d1, d2, 1.0, 0.0001, &e1, &e2);
	printf("%f %f\n",e1,e2);
}


/*
** main function for testing the functions...
**
*/
int main(void) {
	test_compare_derivatives();
	return (0);
} /* end main */
