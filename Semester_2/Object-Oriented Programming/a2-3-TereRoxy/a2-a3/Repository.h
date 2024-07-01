#pragma once
#include "Estate.h"
#include "DynamicArray.h"
#include <stdlib.h>

typedef struct 
{
	DynamicArray* estateList;
}Repository;

Repository* createRepository();
void destroyRepository(Repository* repo);
int addEstate(Repository* repo, Estate* estate);
int addEstatePos(Repository* repo, Estate* estate, int index);
int deleteEstate(Repository* repo, int index);
void updateEstate(Repository* repo, Estate* estate, int index);
Estate* getEstate(Repository* repo, int index);
int getSize(Repository* repo);
void loadEstates(Repository* repo);
void setEstateList(Repository* repo, DynamicArray* newEstateList);
DynamicArray* getEstates(Repository* repo);