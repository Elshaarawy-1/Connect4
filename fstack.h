#ifndef F_STACK_H
#define F_STACK_H
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>


typedef struct Stack {
	int top;
	unsigned long capacity;
	int* array;
}Stack;


Stack* createStack(unsigned long capacity);

int isFull(Stack* stack);

int isEmpty(Stack* stack);

void push(Stack* stack, int item);

int pop(Stack* stack);

int peek(Stack* stack);




#endif