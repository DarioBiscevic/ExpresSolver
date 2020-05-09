#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BUFFER_SIZE 256


double solve(char *input, int leftLimit, int rightLimit){

	//Remove additional brackets
	char depth = 0;
	char brackets = 0;
	char isTheFirstBracketClosed = 0;
	for(int i = leftLimit+1; i < rightLimit-1; i++){
		if(input[i] != 0){
			if(input[i] == '('){ depth++; brackets++; }
			if(input[i] == ')'){ 
				depth--;
				if(brackets == 0){
					isTheFirstBracketClosed = 1;
				}
				brackets++;
			}
		}
	}
	
	if(depth == 0 && input[leftLimit] == '(' && input[rightLimit-1] == ')' && isTheFirstBracketClosed != 1){

		int j = leftLimit;
		for(int i = leftLimit+1; i < rightLimit-1; i++){
			input[j] = input[i];
			j++;
		}

		input[j] = 0;

		rightLimit-=2;
	}
	
	char temp[BUFFER_SIZE];
	for(int i = 0; i < BUFFER_SIZE; i++){
		temp[i] = 0;
	}
	int alpha = 0;
	for(int i = leftLimit; i < rightLimit; i++){
		temp[alpha] = input[i];
		alpha++;
	}
	
	/*
	printf("%s \n", temp);
	printf("Length = %d \n", rightLimit-leftLimit);
	*/


	//Check for operators
	char operator = 0;
	char operatorPlace = 0;

	depth = 0;
	for(int i = rightLimit-1; i >= leftLimit; i--){

		if(input[i] == '('){ depth++;}
		if(input[i] == ')'){ depth--;}

		if(depth == 0){

			if((input[i] == '+' || input[i] == '-' || input[i] == '*' ||
			input[i] == '/' || input[i] == '^') && operator == 0){

				//printf("First operator: %c\n", input[i]);
				operator = input[i];
				operatorPlace = i;

			}else if(operator == '^' && (input[i] == '*' || input[i] == '/')){

				//printf("Changed from %c to %c \n", operator, input[i]);
				operator = input[i];
				operatorPlace = i;

			}else if((operator == '*' || operator == '/') && (input[i] == '+' || input[i] == '-')){

				//printf("Changed from %c to %c \n", operator, input[i]);
				operator = input[i];
				operatorPlace = i;

			}
		}

	}

	//printf("============\n");

	if(operator != 0){
		switch(operator){

			case '+':
			return solve(input, leftLimit, operatorPlace)+solve(input, operatorPlace+1, rightLimit);
			break;

			case '-':
			return solve(input, leftLimit, operatorPlace)-solve(input, operatorPlace+1, rightLimit);
			break;

			case '*':
			return solve(input, leftLimit, operatorPlace)*solve(input, operatorPlace+1, rightLimit);
			break;

			case '/':
			return solve(input, leftLimit, operatorPlace)/solve(input, operatorPlace+1, rightLimit);
			break;

			case '^':
			return pow(solve(input, leftLimit, operatorPlace), solve(input, operatorPlace+1, rightLimit));
			break;

		}
	}
	
	char tempStr[BUFFER_SIZE];
	for(int i = 0; i < BUFFER_SIZE; i++){
		tempStr[i] = 0;
	}
	int j = 0;
	for(int i = leftLimit; i < rightLimit; i++){
		tempStr[j] = input[i];
		j++;
	}
	double value;
	sscanf(tempStr, "%lf", &value);

	//printf("%lf \n", value);

	return value;


}


int main(){

	char buffer[BUFFER_SIZE];
	for(int i = 0; i < BUFFER_SIZE; i++){ buffer[i] = 0; }

	printf("Input: ");
	fgets(buffer, BUFFER_SIZE, stdin);
	printf("==========\n");

	int j = 0;
	for(int i = 0; i < BUFFER_SIZE; i++){
		if(buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\t' && buffer[i] != 0){
			buffer[j] = buffer[i];
			j++;
		}
	}

	buffer[j] = 0;

	printf("Result: %lf\n", solve(buffer, 0, j));

	return 0;

}
