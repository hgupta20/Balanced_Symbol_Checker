#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Global Variables
int const max= 300;
int const TRUE = 1;
int const FALSE = 0;
int debugMode = 0;

//Struct Declaring
typedef struct Node{
	int size;		//size of the dynamic array
	int top;		//top of the stack
	char *arrPtr;	//pointer to the dynamic array 
}Node;

//Prototype Functions
void initializeStack(Node *stack);
int empty(Node *stack);
void push(Node *stack, int value, int debugMode);
void pop(Node *stack, int debugMode);
char accessTopElem(Node *stack);
void resetStack(Node *stack);
void printStack(Node *stack); 


int main(int argc, char** argv){
	
	char userInput[max];			//user input
	
	int i;					//for loop 
	Node stack;
	initializeStack(&stack);
	
	//sets debug mode
	for(i = 0; i < argc; i++){
		if(strcmp(argv[i], "-d") == 0){
			printf("\nDebugging Information\n");
			debugMode = TRUE;
		}
	}
	
	while(1){
		char symbol;
		char expecting;
		
		//collect the input from the User Input using fgets()
		fgets(userInput, max, stdin);
		
		int j;
		int balanced = 1;
		i = 0;		
		
		//If q or Q then exit
		if(userInput[0] == 'q' || userInput[0] == 'Q'){
			printf("\n\nExiting the Program\n\n");
			break;
		}
		//for loop to read the expression line
		for(i = 0; i < strlen(userInput) -1; i++){
			
			if(userInput[i] == '(' || userInput[i] == '{' || userInput[i] == '[' || userInput[i] == '<'){
				push(&stack, userInput[i], debugMode);
			}
		
			
			if(userInput[i] == ')' || userInput[i] == '}' || userInput[i] == ']' || userInput[i] == '>'){
				//change symbol 
				if(userInput[i] == ')')
					symbol = '(';
				else if(userInput[i] == '}')
					symbol = '{';
				else if(userInput[i] == ']')
					symbol = '[';
				else
					symbol = '<';
				
				//symbol at top
				if(accessTopElem(&stack) == symbol){
				
					pop(&stack, debugMode);
					continue;
				}
				//symbol not at the top
				if(accessTopElem(&stack) != symbol){
					if(empty(&stack) == 0){
						if(accessTopElem(&stack) == '(')
							expecting = ')';
						else if(accessTopElem(&stack) == '{')
							expecting = '}';
						else if(accessTopElem(&stack) == '[')
							expecting = ']';
						else
							expecting = '>';
						
						for(j = 0; j < i; j++)
							printf(" ");
						printf("^ expecting %c\n\n", expecting);
						balanced = 0;
						break;
					}
					else if(empty(&stack) == 1){
						for(j = 0; j < i; j++)
							printf(" ");
						printf("^ missing %c\n\n", symbol);
						balanced = 0;
						break;
					}
				}
			}
		}//end of for loop
		
		
		if(balanced == 1){
			
			if(empty(&stack) == 1){
				printf("Expression is balanced\n\n");
				continue;
			}

			//unbalanced and missing closing symbol
			if(empty(&stack) == 0){
				if(accessTopElem(&stack) == '(')
					symbol = ')';
				else if(accessTopElem(&stack) == '{')
					symbol = '}';
				else if(accessTopElem(&stack) == '[')
					symbol = ']';
				else
					symbol = '>';
				for(j = 0; j < i; j++)
					printf(" ");
				printf("^ missing %c\n\n", symbol);
			}
		}
		resetStack(&stack);
	}
	return 0;
}//end main()

//Defining Functions

//access top element in the array
char accessTopElem(Node *stack){
	return stack->arrPtr[stack->top - 1];
}//end accessTopElem()

//Checking if stack is empty
int empty(Node *stack){
	if(stack->top == 0)
		return 1;
	return 0;
}//end empty()

//initialize the stack
void initializeStack(Node *stack){
	stack->size = 2;	
	stack->top = 0;		
	char *arr = (char *) malloc(sizeof(char) * (stack->size)); //allocate space for list
	stack->arrPtr = arr;	
}//end initializeStack()

//push function
void push(Node *stack, int value, int debugMode){
	if(debugMode == TRUE)
		printf("\nDebug Mode: Push\n");
	
	if(stack->top == stack->size){
		int i;
		//grow function
		char *temp = (char *) malloc((sizeof(char) * (stack->size)) + 2);  //allocate larger array space
            for(i = 0; i < stack->size; i++)
                temp[i] = stack->arrPtr[i];
				
			if(debugMode == TRUE)
				printf("\nNumber of values copied: %d", i);

            free(stack->arrPtr);	
            stack->arrPtr = temp; 	
			
			if(debugMode == TRUE)
				printf("\nOld Size: %d", stack->size);
            stack->size += 2; 
			if(debugMode == TRUE)
				printf("\nNew Size: %d", stack->size);
	}
			
	
	stack->arrPtr[stack->top] = value;
	if(debugMode == TRUE)
		printf("\nPushed to stack: %c", stack->arrPtr[stack->top]);
	
	
	(stack->top) += 1;
	if(debugMode == TRUE)
		printf("\nNew top value: %d", stack->top);
}//end push()

//pop function
void pop(Node *stack, int debugMode){
	if(debugMode == TRUE){
		printf("\nDebug Mode: Pop\n");
		printf("\nPopped from stack: %c", stack->arrPtr[stack->top]);
	}

	(stack->top)= (stack->top)-1;
	if(debugMode == TRUE)
		printf("\nNew top value: %d", stack->top);
	
	
	stack->arrPtr[stack->top] = 0;

}//end pop()

//reset stack 
void resetStack(Node *stack){
	stack->size = 2;	
	stack->top = 0;		
	char *newArr = (char *) malloc(sizeof(char) * (stack->size)); //creates new stack 
	free(stack->arrPtr); //frees old stack
	stack->arrPtr = newArr; 
}//end resetStack()

//print stack
void printStack(Node *stack){
   int i;
   printf("Stack: ");
   for(i = 0; i < stack->size; i++)
	   printf("%c ", stack->arrPtr[i]);
   printf("\n\n");
}//end printStack()
