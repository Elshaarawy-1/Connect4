#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "fstack.h"

Stack* createStack(unsigned long capacity)
{
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->capacity = capacity;
	stack->top = -1;
	stack->array = (int*)malloc(stack->capacity * sizeof(int));
	return stack;
}

int isFull(Stack* stack)
{
	return stack->top == stack->capacity - 1;
}

int isEmpty(Stack* stack)
{
	return stack->top == -1;
}

void push(Stack* stack, int item)
{
	if (isFull(stack))
		return;
	stack->array[++stack->top] = item;
}

int pop(Stack* stack)
{
	if (isEmpty(stack))
		return INT_MIN;
	return stack->array[stack->top--];
}

int peek(Stack* stack)
{
	if (isEmpty(stack))
		return INT_MIN;
	return stack->array[stack->top];
}
