#include <stdio.h>
#include <stdlib.h>

int student_score(int number_of_students){
	int i,index,score,max_score,min_score,max_score_index,min_score_index;
	int A_grades,B_grades,C_grades,D_grades,F_grades;
	int option;
	char max_score_latter,min_score_latter;
	double total_grades=0;
	double average;
	A_grades=0;B_grades=0;C_grades=0;D_grades=0;F_grades=0;
	
	srand(40);
	score=rand()%100+1;
	printf("%d ",score);
	total_grades+=score;
	max_score=score;
	max_score_index=1;
	min_score=score;
	min_score_index=1;
	if(score>=90 && score<=100){
		A_grades+=1;
		max_score_latter='A';
		min_score_latter='A';
	}	
	else if(score>=80 && score<=89){ //increase counters according to notes and maximum and minimum letter grades that provide a conditional default value 
		B_grades+=1;
		max_score_latter='B';
		min_score_latter='B';
	}
	else if(score>=70 && score<=79){
		C_grades+=1;
		max_score_latter='C';
		min_score_latter='C';
	}
	else if(score>=60 && score<=69){
		D_grades+=1;
		max_score_latter='D';
		min_score_latter='D';
	}
	else{
		F_grades+=1;
		max_score_latter='F';
		min_score_latter='F';
	}
	for(i=0,index=2;i<number_of_students-1;i++,index++){ //Loop,it will repeat as many as the number of students-1 because we did already assigment to score above
		score=rand()%100+1;
		if(score>max_score){ //every new score is check to find maximum score
			max_score=score;
			max_score_index=index;
			if(score>=90 && score<=100){
				A_grades+=1;
				max_score_latter='A';  //the letter note of the specified maximum score is recorded
			}
			else if(score>=80 && score<=89){
				B_grades+=1;
				max_score_latter='B';
			}
			else if(score>=70 && score<=79){
				C_grades+=1;
				max_score_latter='C';
			}
			else if(score>=60 && score<=69){
				D_grades+=1;
				max_score_latter='D';
			}
			else{
				F_grades+=1;
				max_score_latter='F';
			}
		}
		else if(score<min_score){ //every new score is check to find maximum score
			min_score=score;
			min_score_index=index;
			if(score>=90 && score<=100){
				A_grades+=1;
				min_score_latter='A';
			}
			else if(score>=80 && score<=89){
				B_grades+=1;
				min_score_latter='B'; //the letter note of the specified minimum score is recorded
			}
			else if(score>=70 && score<=79){
				C_grades+=1;
				min_score_latter='C';
			}
			else if(score>=60 && score<=69){
				D_grades+=1;
				min_score_latter='D';
			}
			else{
				F_grades+=1;
				min_score_latter='F';
			}
		}
		else{   //if score is not maximum or minimum then it just will be simple statisticc
		if(score>=90 && score<=100)
			A_grades+=1;
		else if(score>=80 && score<=89)
			B_grades+=1;
		else if(score>=70 && score<=79)
			C_grades+=1;
		else if(score>=60 && score<=69)
			D_grades+=1;
		else
			F_grades+=1;
		}
		printf("%d ",score); 
		if(index%10==0 && index>=10) // this condition is necessary to ensure column order
			printf("\n");
		total_grades+=score; //every score is summed
	}
	if(index%10!=0)
		printf("\n");
	average=total_grades/number_of_students;
	
	while(1){
		printf("-------------------------------------\n");
		printf("Student Score Calculator Menu For %d \n\n",number_of_students);
		printf("1) Most Successful Student\n");
		printf("2) Most Unsuccessful Student\n");
		printf("3) Letter Grade Statistics\n");
		printf("4) Calculate Average\n");
		printf("5) Show All Data\n");
		printf("                               Make Selection: ");
		scanf("%d",&option);
		
		switch(option){
			
			case 1:
				printf("Most successfully Student :\n");
				printf("Index :%d\nScore : %d\nLetter grade : %c\n",max_score_index,max_score,max_score_latter);
				break;
			case 2:
				printf("Most Unsuccessfully StudenT: \nIndex :%d\nScore :%d\nLetter grade :%c\n",min_score_index,min_score,min_score_latter);
				break;
			case 3:
				printf("%d Student got Letter grade 'A'\n%d Student got Letter grade 'B'\n%d Student got Letter grade 'C'\n",A_grades,B_grades,C_grades);
				printf("%d Student got Letter grade 'D'\n%d Student got Letter grade 'F'\n",D_grades,F_grades);
				break;
			case 4:
				printf("The Average Score of %d Student is %.2lf \n",number_of_students,average);
				break;
			case 5:
				printf("Most successfully Student :\n");
				printf("Index :%d\nScore : %d\nLetter grade : %c\n\n\n",max_score_index,max_score,max_score_latter);
				printf("Most Unsuccessfully StudenT: \nIndex :%d\nScore :%d\nLetter grade :%c\n\n\n",min_score_index,min_score,min_score_latter);
				printf("%d Student got Letter grade 'A'\n%d Student got Letter grade 'B'\n%d Student got Letter grade 'C'\n",A_grades,B_grades,C_grades);
				printf("%d Student got Letter grade 'D'\n%d Student got Letter grade 'F'\n\n\n",D_grades,F_grades);
				printf("The Average Score of %d Student is %.2lf \n",number_of_students,average);
				break;
			case -1:
				return 0; // if the user enter -1 program will close
				break;
			default:
				printf("False Selection!!!\n");		
		}
	}
	return 1; // the loop will continue as long as the user does not enter -1,the program will never reach the last row, but it is  semantically required
 
}
int main(void){
	
	int number_of_students;
	
	do{
		printf("Enter Number Of Students: ");
		scanf("%d",&number_of_students);
		printf("\n");
		if(number_of_students<3 || number_of_students>50)
			printf("Not in range!\n");
	}while(number_of_students<3 || number_of_students>50); // this loop forces the user to enter a number between 3 and 53 
	student_score(number_of_students);
	
	return 0;
}
