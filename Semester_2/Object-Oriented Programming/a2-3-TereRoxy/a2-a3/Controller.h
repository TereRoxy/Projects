#pragma once
#include "Repository.h"
#include "OperationStack.h"

typedef struct
{
	Repository* Repo;
	OperationsStack* undoStack;
	OperationsStack* redoStack;
}Controller;

/// <summary>
/// Constructor for the repository controller. Allocates memory for the estate list
/// </summary>
/// <returns> pointer to the controller if it can be created, NULL otherwise </returns>
Controller* createRepoController(Repository* r, OperationsStack* undoS, OperationsStack* redoS);

/// <summary>
/// Destructor for the repository controller. Frees the memory allocated for the estate list
/// </summary>
/// <param name="repoController"> The controller to be freed </param>
void destroyRepoController(Controller* repoController);

/// <summary>
/// Adds an estate to the repository
/// </summary>
/// <param name="repoController"> The controller </param>
/// <param name="type"> The type of the estate </param>
/// <param name="address"> The address of the estate </param>
/// <param name="surface"> The surface of the estate </param>
/// <param name="price"> The price of the estate </param>
/// <returns> 0 if the estate list doesn't exist, 1 if the estate was added successfully, -1 if the estate already exists </returns>
int addEstateController(Controller* repoController, char* type, char* address, int surface, int price);

/// <summary>
/// Identifires and deletes an estate from the repository
/// </summary>
/// <param name="repoController"> The controller </param>
/// <param name="address"> The address of the estate to be deleted </param>
/// <returns> 0 if the estate list doesn't exist, 1 if the estate was deleted successfully, -1 if the estate doesn't exist </returns>
int deleteEstateController(Controller* repoController, char* address);


/// <summary>
/// Finds an estate with a given address in the repository
/// </summary>
/// <param name="repoController"> The controller </param>
/// <param name="address"> The address of the estate </param>
/// <returns> NULL if the estate list doesn't exist,
/// -1 if the estate doesn't exist exists, the index of the estate if it exists
///  </returns>
/// 
int searchAddress(Controller* repoController, char* address);

/// <summary>
/// Checks if an estate exists in the repository
/// </summary>
/// <param name="repoController"> The controller </param>
/// <param name="estate"> The estate to be checked </param>
/// <returns> -1 if the estate list doesn't exist, 1 if the estate exists, 0 if the estate doesn't exist </returns>
int estateExists(Controller* repoController, Estate* estate);

/// <summary>
/// Updates an estate from the repository
/// </summary>
/// <param name="repoController"> The controller </param>
/// <param name="type"> The type of the estate </param>
/// <param name="address"> The address of the estate </param>
/// <param name="surface"> The surface of the estate </param>
/// <param name="price"> The price of the estate </param>
/// <returns> 0 if the estate list doesn't exist, 1 if the estate was updated successfully, -1 if the estate doesn't exist </returns>
int updateEstateController(Controller* repoController, char* type, char* address, int surface, int price);

/// <summary>
/// Filters the estate list by partial address match
/// </summary>
/// <param name="estateList"> The list to be filtered </param>
/// <param name="address"> The string to be matched </param>
/// <returns> The filtered list </returns>
DynamicArray* filterEstateByAdress(DynamicArray* estateList, char* address);

/// <summary>
/// Filters the estate list by a given surface and comparison
/// </summary>
/// <param name="estateList"> The list to be filtered </param>
/// <param name="surface"> The filter </param>
/// <param name="cmp"> The comparison type </param>
/// <returns> The filtered list </returns>
DynamicArray* filterEstateBySurface(DynamicArray* filteredEstates, int surface, int cmp);

//void filterEstateByPrice(Controller* repoController, DynamicArray* filteredEstates, int price, int cmp);

/// <summary>
/// Filter the estate list by type
/// </summary>
/// <param name="estateList"> The list to be filtered </param>
/// <param name="type"> The filter </param>
/// <returns> The filtered list </returns>
DynamicArray* filterEstateByType(DynamicArray* estateList, char* type);

/// <summary>
/// Sorts the estate list by price
/// </summary>
/// <param name="repoController"> The controller </param>
/// <returns> NULL if the estate list doesn't exist, a list of estates sorted by price otherwise </returns>
void sortByPrice(DynamicArray* estateList);

/// <summary>
/// Gets the estate list from the controller
/// </summary>
/// <param name="repoController"> The controller </param>
/// <returns> NULL if the estate list doesn't exist, the estate list otherwise </returns>
Repository* getRepo(Controller* repoController);

/// <summary>
/// Sets the estate list from the controller
/// </summary>
/// <param name="repoController"> The controller </param>
/// <param name="newRepo"> The new estate list </param>
void setRepo(Controller* repoController, Repository* repo);

int undo(Controller* repoController);
int redo(Controller* repoController);