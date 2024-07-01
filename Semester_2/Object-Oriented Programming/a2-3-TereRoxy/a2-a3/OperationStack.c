#include "OperationStack.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

Operation* createOperation(Estate* e, int index, char* operationType)
{
	Operation* o = malloc(sizeof(Operation));
	if (o == NULL)
		return NULL;
	o->estate = copyEstate(e);

	o->index = index;
	
	if (operationType != NULL)
	{
		o->operationType = malloc(sizeof(char) * (strlen(operationType) + 1));
		if (o->operationType == NULL)
		{
			free(o);
			return NULL;
		}
		strcpy(o->operationType, operationType);
	}
	else
		o->operationType = NULL;

	return o;
}

void destroyOperation(Operation* o)
{
	if (o == NULL)
		return;

	// first destroy the estate
	destroyEstate(o->estate);
	// then the operationType
	free(o->operationType);
	// then free the operation
	free(o);
}

Operation* copyOperation(Operation* o)
{
	if (o == NULL)
		return NULL;
	Operation* copy = createOperation(getEstateOp(o), getOperationIndex(o), getOperationType(o));
	return copy;
}

char* getOperationType(Operation* o)
{
	return o->operationType;
}

Estate* getEstateOp(Operation* o)
{
	Estate* es = o->estate;
	return es;
}

// ---------------------------------------------------------------

OperationsStack* createStack()
{
	OperationsStack* s = malloc(sizeof(OperationsStack));
	if (s == NULL)
		return NULL;
	s->stack = createDynamicArray(10, &destroyOperation);
	if (s->stack == NULL)
	{
		free(s);
		return NULL;
	}

	return s;
}

void destroyStack(OperationsStack* s)
{
	if (s == NULL)
		return;

	// first deallocate the memory for the dynamic array
	destroy(s->stack);

	// then free the stack
	free(s);
}

void push(OperationsStack* s, Operation* o)
{
	if (s == NULL || o == NULL)
		return;
	add(s->stack, o);
}

Operation* pop(OperationsStack* s)
{
	if (s == NULL)
		return NULL;
	int lastPos = get_size(s->stack) - 1;
	Operation* o = (Operation*)get_elem(s->stack, lastPos); // must cast it to Operation*, as it is a void*
	// make a copy to use it for redo as well
	Operation* lastOp = copyOperation(o);
	delete_elem(s->stack, lastPos);
	return lastOp;
}

int isEmpty(OperationsStack* s)
{
	if (s == NULL)
		return 1;
	return (get_size(s->stack) == 0);
}

void clearStack(OperationsStack* s)
{
	if (s == NULL)
		return;
	destroy(s->stack);
	s->stack = createDynamicArray(10, &destroyOperation);
	if (s->stack == NULL)
	{
		free(s);
		return;
	}
}

int getOperationIndex(Operation* o)
{
	return o->index;
}
