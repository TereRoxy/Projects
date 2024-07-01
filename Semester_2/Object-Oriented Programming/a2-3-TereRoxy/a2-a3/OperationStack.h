#pragma once
#include "Estate.h"
#include "DynamicArray.h"
#include <string.h>

typedef struct
{
	Estate* estate;
	int index;
	char* operationType;
} Operation;

Operation* createOperation(Estate* e, int index, char* operationType);
void destroyOperation(Operation* o);
Operation* copyOperation(Operation* o);
char* getOperationType(Operation* o);
Estate* getEstateOp(Operation* o);
int getOperationIndex(Operation* o);

// ---------------------------------------------------------------
typedef struct
{
	DynamicArray* stack;
} OperationsStack;

OperationsStack* createStack();
void destroyStack(OperationsStack* s);
void push(OperationsStack* s, Operation* o);
Operation* pop(OperationsStack* s);
int isEmpty(OperationsStack* s);
void clearStack(OperationsStack* s);