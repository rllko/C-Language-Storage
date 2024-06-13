#include <stdio.h>
#include <stdlib.h>

void print_variables(int* a, int* b){
	printf("first variable: %d\nsecond variable: %d\n",*a,*b);
}

void substraction_method(int* a,int* b){
	*a = *a+*b;
	*b = *a-*b;
	*a = *a-*b;
}

void xor_method(int* a, int* b){
	*a = *a^*b;
	*b = *b^*a;
	*a = *b^*a;
}

int main(){
	int a;
	int b;

	printf("Introduce two variables to replace: \n");
	scanf("%d",&a);
	printf("now write a second one: \n");
	scanf("%d",&b);

	int temp_a = a;
	int temp_b = b;

	// i couldve really just copied the variable 
	substraction_method(&temp_a,&temp_b);
	print_variables(&temp_a,&temp_b);

	xor_method(&a,&b);
	print_variables(&a,&b);

	getchar();
}
