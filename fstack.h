#ifndef F_STACK_H
#define F_STACK_H
#include <stdlib.h>
#include <stdio.h>


struct Stack {
	int top;
	unsigned capacity;
	int* array;
};


struct Stack* createStack(unsigned capacity);

int isFull(struct Stack* stack);

int isEmpty(struct Stack* stack);

void push(struct Stack* stack, int item);

int pop(struct Stack* stack);

int peek(struct Stack* stack);




#endif