#include <stdio.h>
#include <math.h>

#define PI 3.14

double circle_area(double radius){
	return pow(radius,2.0)*PI;  //function that calculates circle area.
}
double calc_hypotenuse(int side1,int side2){
	return sqrt(pow(side1,2.0)+pow(side2,2.0)); //sqrt and pow functions are used nested.
}
double calc_radius_of_smallest_circle(int side1,int side2){
	return calc_hypotenuse(side1,side2)/2;		//Half of the hypotenuse equals the circle diameter
}
double calc_radius_of_largest_circle(int side1,int side2){
	if(side1>=side2)			        // Half of the short edge equals the radius of the circle
		return (double)side2/2;
	else
		return (double)side1/2;
}
double calc_area_of_smallest_circle(int side1,int side2){ // using the given edges first finds the circle area after the radius
	return circle_area(calc_radius_of_smallest_circle(side1,side2));
}
double calc_area_of_largest_circle(int side1,int side2){  //  using the given edges first finds the circle area after the radiu
	return circle_area(calc_radius_of_largest_circle(side1,side2));
}
double calc_area_of_square(int side){  // finds the field with given edge information

	return pow(side,2.0);
}
double calc_area_of_largest_square(int side1,int side2){ // Assume that short edge is edge of square then calculates area
	if(side1>=side2)
		return calc_area_of_square(side2);
	else
		return calc_area_of_square(side1);
}
double calc_area_of_smallest_square(int side1,int side2){ // Assume that long edge is edge of square then calculates area
	if(side1>=side2)
		return calc_area_of_square(side1);
	else
		return calc_area_of_square(side2);
		
}
void display_results(double largest_circle,double largest_square,double smallest_circle,double smallest_square){
	printf("The area of the largest circle that fits inside your rectangle:   %.2lf \n",largest_circle);
	printf("The area of the largest square that fits inside your rectangle:   %.2lf \n",largest_square);
	printf("The area of the smallest circle that surrounds your rectangle:   %.2lf \n",smallest_circle);
	printf("The area of the smallest square that surrounds your rectangle:   %.2lf \n",smallest_square);
}

int main(void){
	
	int side1,side2;
	double largest_circle,largest_square,smallest_circle,smallest_square;
	
	printf("Enter the first side for your rectangle:   ");  // We want edge information from the user
	scanf("%d",&side1);
	printf("Enter the second side for your rectangle:  ");
	scanf("%d",&side2);
	
	largest_circle=calc_area_of_largest_circle(side1,side2);  // We find the fields of shapes and assign them to variables 
	largest_square=calc_area_of_largest_square(side1,side2);  // to use as a parameter in function.
	smallest_circle=calc_area_of_smallest_circle(side1,side2);
	smallest_square=calc_area_of_smallest_square(side1,side2);
	
	display_results(largest_circle,largest_square,smallest_circle,	smallest_square);
	
	return 0;
}
