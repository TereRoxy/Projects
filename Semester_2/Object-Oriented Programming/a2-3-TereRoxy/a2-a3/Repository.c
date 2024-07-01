#include "Repository.h"
#include <stdlib.h>
#include <stdio.h>


Repository* createRepository()
{
	/// <summary>
	/// Constructor for the repository
	/// </summary>
	/// returns a pointer to the repository if it can be created, NULL otherwise
	Repository* repo = (Repository*)malloc(sizeof(Repository));
	if (repo == NULL)
		return NULL;
	repo->estateList = createDynamicArray(10, &destroyEstate);
	return repo;
}


void destroyRepository(Repository* repo)
{
	/// <summary>
	/// Destructor for the repository. Frees the memory allocated for the estate array
	/// </summary>
	/// <param name="repo"> The repository to be freed </param>
	if (repo == NULL)
		return;
	destroy(repo->estateList);
	free(repo);
}

int addEstate(Repository* repo, Estate* estate)
{
	/// <summary>
	/// Adds an estate to the repository
	/// </summary>
	/// <param name="repo"> The list of estates </param>
	/// <param name="estate"> The estate to be added </param>
	/// <returns> 0 if the estate list doesn't exist </returns>
	if (repo == NULL)
		return 0;
	add(repo->estateList, estate);
	return 1;
}

int addEstatePos(Repository* repo, Estate* estate, int index)
{
	/// <summary>
	/// Adds an estate to the repository at a given position
	/// </summary>
	/// <param name="repo"> The list of estates </param>
	/// <param name="estate"> The estate to be added </param>
	/// <param name="index"> The position where the estate will be added </param>
	/// <returns> 0 if the estate list doesn't exist </returns>
	if (repo == NULL)
		return 0;
	insertAtPosition(repo->estateList, estate, index);
	return 1;
}

int deleteEstate(Repository* repo, int index)
{
	/// <summary>
	/// Delets an estate from a given index from the repository
	/// </summary>
	/// <param name="repo"> The list of estates </param>
	/// <param name="estate"> The estate to be deleted </param>
	/// <returns> 1 if the estate has been deleted successfully 
	///           0 if the estate list is empty </returns>
	if (repo == NULL)
		return 0;
	delete_elem(repo->estateList, index);
	return 1;
}

void updateEstate(Repository* repo, Estate* estate, int index)
{
	/// <summary>
	/// Updates the estate at the given index with the given estate
	/// </summary>
	/// <param name="repo"> The list of estates </param>
	/// <param name="estate"> The estate to be updated </param>
	/// <param name="index"> The index of the estate to be updated </param>
	if (repo == NULL)
		return;
	update(repo->estateList, estate, index);
}

Estate* getEstate(Repository* repo, int index)
{
	/// <summary>
	/// Returns the estate from the repository at the given index
	/// </summary>
	/// <param name="repo"> The list of estates </param>
	/// <param name="index"> The index of the estate </param>
	/// <returns> The estate at the given index </returns>
	if (repo == NULL)
		return NULL;
	return get_elem(repo->estateList, index);

}

int getSize(Repository* repo)
{
	/// <summary>
	/// Returns the size of the estate list
	/// </summary>
	/// <param name="repo"> The list of estates </param>
	/// <returns> The size of the estate list </returns>
	return get_size(repo->estateList);
}


void loadEstates(Repository* repo)
{
	/// <summary>
	/// Loads the estates from the file into the repository
	/// </summary>
	FILE* file = fopen("estates.txt", "r");
	if (file == NULL)
		return;
	char* type_buffer = (char*)malloc(sizeof(char) * 20);
	char* address_buffer = (char*)malloc(sizeof(char) * 100);
	int surface, price;
	
	while (fscanf(file, "%s %s %d %d", type_buffer, address_buffer, &surface, &price) != EOF)
	{
		Estate* estate = createEstate(type_buffer, address_buffer, surface, price);
		addEstate(repo, estate);
	}
	fclose(file);
	free(type_buffer);
	free(address_buffer);
}

void setEstateList(Repository* repo, DynamicArray* newEstateList)
{
	/// <summary>
	/// Sets the estate list to a new dynamic array
	/// </summary>
	/// <param name="repo"> The repository </param>
	repo->estateList = newEstateList;
}

DynamicArray* getEstates(Repository* repo)
{
	/// <summary>
	/// Returns the estate list
	/// </summary>
	/// <param name="repo"> The repository </param>
	/// <returns> The estate list </returns>
	return repo->estateList;
}
