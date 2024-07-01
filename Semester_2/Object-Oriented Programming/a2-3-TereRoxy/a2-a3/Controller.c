#include "Controller.h"
#include <stdlib.h>
#include <string.h>

Controller* createRepoController(Repository* r, OperationsStack* undoS, OperationsStack* redoS)
{
	Controller* c = (Controller*)malloc(sizeof(Controller));
	if (c == NULL)
		return NULL;
	c->Repo = r;
	c->undoStack = undoS;
	c->redoStack = redoS;
	return c;
}

void destroyRepoController(Controller* repoController)
{
	if (repoController == NULL)
		return;
	destroyRepository(repoController->Repo);
	destroyStack(repoController->undoStack);
	destroyStack(repoController->redoStack);
	free(repoController);
}

int addEstateController(Controller* repoController, char* type, char* address, int surface, int price)
{
	if (repoController == NULL)
		return 0;
	if (searchAddress(repoController, address) >= 0)
		return -1;
	Estate* estate = createEstate(type, address, surface, price);
	addEstate(repoController->Repo, estate);
	
	//Estate* estCpy = copyEstate(estate);
	Operation* operation = createOperation(estate, getSize(repoController->Repo)-1, "add");
	push(repoController->undoStack, operation);
	//clear redo stack
	clearStack(repoController->redoStack);
	
	return 1;
}

int deleteEstateController(Controller* repoController, char* address)
{
	if (repoController == NULL)
		return 0;
	int index = searchAddress(repoController, address);
	if (index < 0)
		return -1;
	
	Estate* estate = getEstate(repoController->Repo, index);
	
	Operation* operation = createOperation(estate, index, "delete");
	push(repoController->undoStack, operation);
	
	int return_value = deleteEstate(repoController->Repo, index);
	//clear redo stack
	clearStack(repoController->redoStack);
	
	return return_value;
}

int updateEstateController(Controller* repoController, char* type, char* address, int surface, int price)
{
	if (repoController == NULL)
		return 0;
	int index = searchAddress(repoController, address);
	if (index < 0)
		return -1;
	Estate* estate = getEstate(repoController->Repo, index);
	Operation* operation = createOperation(estate, index, "update");
	push(repoController->undoStack, operation);
	//clear redo stack
	clearStack(repoController->redoStack);
	
	Estate* newEstate = createEstate(type, address, surface, price);
	updateEstate(repoController->Repo, newEstate, index);
	return 1;
}

int undo(Controller* repoController)
{
	if (isEmpty(repoController->undoStack))
		return 0;
	Operation* operation = pop(repoController->undoStack);
	if (strcmp(getOperationType(operation), "add") == 0)
	{
		Estate* estate = getEstateOp(operation);
		int pos = getOperationIndex(operation);
		
		//record for redo
		Operation* redoOperation = createOperation(estate, pos, "add");
		push(repoController->redoStack, redoOperation);

		deleteEstate(repoController->Repo, pos);
	}
	else if (strcmp(getOperationType(operation), "delete") == 0)
	{
		Estate* estate = getEstateOp(operation);
		Estate* copy = copyEstate(estate);
		int pos = getOperationIndex(operation);
		
		//record for redo
		Operation* redoOperation = createOperation(estate, pos, "delete");
		push(repoController->redoStack, redoOperation);

		addEstatePos(repoController->Repo, copy, pos);
	}
	else if (strcmp(getOperationType(operation), "update") == 0)
	{
		Estate* estate = getEstateOp(operation);
		Estate* copy = copyEstate(estate);
		int pos = getOperationIndex(operation);
		Estate* oldEstate = getEstate(repoController->Repo, pos);
		
		//record for redo
		Operation* redoOperation = createOperation(oldEstate, pos, "update");
		push(repoController->redoStack, redoOperation);
		
		updateEstate(repoController->Repo, copy, pos);
	}
	destroyOperation(operation);
	return 1;
}

int redo(Controller* repoController)
{
	if (isEmpty(repoController->redoStack))
		return 0;
	Operation* operation = pop(repoController->redoStack);
	if (strcmp(getOperationType(operation), "add") == 0)
	{
		Estate* estate = getEstateOp(operation);
		Estate* copy = copyEstate(estate);
		int pos = getOperationIndex(operation);
		
		//record for undo
		Operation* undoOperation = createOperation(estate, pos, "add");
		push(repoController->undoStack, undoOperation);
		
		addEstate(repoController->Repo, copy);
	}
	else if (strcmp(getOperationType(operation), "delete") == 0)
	{
		Estate* estate = getEstateOp(operation);
		int pos = getOperationIndex(operation);
		
		//record for undo
		Operation* undoOperation = createOperation(estate, pos, "delete");
		push(repoController->undoStack, undoOperation);
		
		deleteEstate(repoController->Repo, pos);
	}
	else if (strcmp(getOperationType(operation), "update") == 0)
	{
		Estate* estate = getEstateOp(operation);
		Estate* copy = copyEstate(estate);

		int pos = getOperationIndex(operation);
		Estate* oldEstate = getEstate(repoController->Repo, pos);
		
		//record for undo
		Operation* undoOperation = createOperation(oldEstate, pos, "update");
		push(repoController->undoStack, undoOperation);
		
		updateEstate(repoController->Repo, copy, pos);
	}
	destroyOperation(operation);
	return 1;
}

int searchAddress(Controller* repoController, char* address)
{
	if (repoController == NULL)
		return 0;
	for (int i = 0; i < getSize(repoController->Repo); i++)
	{
		Estate* estate = getEstate(repoController->Repo, i);
		char* current_adr = getAddress(estate);
		if (strcmp(current_adr, address) == 0)
		{
			return i;
		}
	}
	return -1;
}

int estateExists(Controller* repoController, Estate* estate)
{
	if (repoController == NULL)
		return -1;
	for (int i = 0; i < getSize(repoController->Repo); i++)
	{
		Estate* current_estate = getEstate(repoController->Repo, i);
		if (isEqual(*current_estate, *estate))
			return 1;
	}
	return 0;
}

DynamicArray* filterEstateByAdress(DynamicArray* estateList, char* address)
{
	if (estateList == NULL)
		return NULL;

	DynamicArray* filteredEstates = createDynamicArray(10, &destroyEstate);
	
	int len = get_size(estateList);
	for (int i = 0; i < len; i++)
	{
		Estate* es = get_elem(estateList, i);
		if (strstr(getAddress(es), address) != NULL || address[0] == '$')
			add(filteredEstates, es);
	}
	return filteredEstates;
}

DynamicArray* filterEstateByType(DynamicArray* estateList, char* type)
{
	DynamicArray* filteredEstates = createDynamicArray(10, &destroyEstate);

	int len = get_size(estateList);
	for (int i = 0; i < len; i++)
	{
		Estate* es = get_elem(estateList, i);
		if (strcmp(getType(es), type) == 0 || type[0] == '$')
			add(filteredEstates, es);
	}
	return filteredEstates;
}

DynamicArray* filterEstateBySurface(DynamicArray* estateList, int surface, int cmp)
{
	if (estateList == NULL)
		return NULL;
	
	DynamicArray* filteredEstates = createDynamicArray(10, &destroyEstate);

	int len = get_size(estateList);
	for (int i = 0; i < len; i++)
	{
		Estate* es = get_elem(estateList, i);
		if ((cmp == 1 && getSurface(es) > surface) || (cmp == 0 && getSurface(es) == surface) || (cmp == -1 && getSurface(es) < surface))
			add(filteredEstates, es);
	}
	return filteredEstates;
}

/// <summary>
/// Compares the price of two estates
/// </summary>
/// <param name="estate1"> The first estate </param>
/// <param name="estate2"> The second estate </param>
/// <returns> 1 if the price of the first estate is greater than the price of the second estate, 0 otherwise </returns>
int comparePrice(Estate* estate1, Estate* estate2)
{
	
	if (estate1->price > estate2->price)
		return 1;
	if (estate1->price == estate2->price)
		return 0;
	return -1;
}

int compareEstatesByPrice(const void* a, const void* b) {
	Estate* estate1 = *(Estate**)a;
	Estate* estate2 = *(Estate**)b;
	return comparePrice(estate1, estate2);
}

void sortByPrice(DynamicArray* List)
{
	int len = get_size(List);

	/*for (int i = 0; i < len - 1; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			Estate* estate1 = get_elem(List, i);
			Estate* estate2 = get_elem(List, j);
			if (comparePrice(estate1, estate2) == 1)
			{
				Estate* aux = estate1;
				estate1 = estate2;
				estate2 = estate1;
			}

		}
	}*/
	qsort(List->elems, len, sizeof(Estate*), compareEstatesByPrice);
}

Repository* getRepo(Controller* repoController)
{
	if (repoController == NULL)
		return NULL;
	return repoController->Repo;
}

void setRepo(Controller* repoController, Repository* newRepo)
{
	if (repoController == NULL)
		return;
	repoController->Repo = newRepo;
}