#include <stdio.h>

char* find_operations(int arr[], int expected_val, char operations[], size_t arr_len, int cursor, int current){
	
	if(cursor-arr_len+1==cursor){  //this condition checks whether the number array comes to the end
		if(current*arr[0]==expected_val){
			operations[0]='*';
			return operations;}
		else if(current+arr[0]==expected_val){
			operations[0]='+';
			return operations;}
		else if(current-arr[0]==expected_val){
			operations[0]='-';
			return operations;}
		else 
			operations[0]=' ';
		return operations;
	}
	else{ //if number array doesn't come to end
		if(cursor-arr_len==0){  //if number array is in start of array
			current=arr[0]*arr[1]; //first two numbers are processed as desired and assigned as the current value
			if(*(find_operations(&arr[2],expected_val,&operations[1],arr_len-2,cursor,current))!=' '){//function called recursively with array that after the first two elements of the array
				operations[0]='*';
				return operations;
			}
			current=arr[0]+arr[1];//same as above
			if(*(find_operations(&arr[2],expected_val,&operations[1],arr_len-2,cursor,current))!=' '){
				operations[0]='+';
				return operations;
			}
			current=arr[0]-arr[1];//same as above
			if(*(find_operations(&arr[2],expected_val,&operations[1],arr_len-2,cursor,current))!=' '){
				operations[0]='-';
				return operations;
			}
			operations[0]=' '; //if conditions above are not provide then return as space 
			return operations;
		}
		else{	//if number array is not in start or finish.
			if(*(find_operations(&arr[1],expected_val,&operations[1],arr_len-1,cursor,current*arr[0]))!=' '){//function called recursively with array that after the first one elements of the array
				operations[0]='*';
				return operations;}
			else if(*(find_operations(&arr[1],expected_val,&operations[1],arr_len-1,cursor,current+arr[0]))!=' '){
				operations[0]='+';
					return operations;}
			else if(*(find_operations(&arr[1],expected_val,&operations[1],arr_len-1,cursor,current-arr[0]))!=' '){
				operations[0]='-';
				return operations;}
			else
				operations[0]=' '; //if conditions above are not provide then return as space
			return operations;
		}
	}
}
int main(){
	int array[6]={25,12,6,10,32,8};
	char operations[5]={' ',' ',' ',' ',' '};
	
	find_operations(array,44,operations,6,6,1); //in the first calling function the arr_len parameter and cursor parameter 
	//have to same value and have to be size of number of array.in the first calling function the current value can be set to desired 		value. 
	
	printf("%c->%c->%c->%c->%c",operations[0],operations[1],operations[2],operations[3],operations[4]);
	
	return 0;
}
