#include "Estate.h"
#include <stdlib.h>

Estate* createEstate(char* type, char* address, int surface, int price)
{
	/// <summary>
	/// Creates an estate with the given parameters
	/// </summary>
	/// <param name="type"> The type of the estate: house, apartment, penthouse (arrays of char)</param>
	/// <param name="address"> The address of the estate (unique id) </param>
	/// <param name="surface"> The surface of the estate </param>
	/// <param name="price">The price of the estate </param>
	/// <returns> The created estate </returns>
	Estate* estate = (Estate*)malloc(sizeof(Estate));
	if (estate == NULL)
		return NULL;
	estate->type = malloc(sizeof(char) * (strlen(type) + 1));
	if (estate->type == NULL)
	{
		free(estate);
		return NULL;
	}
	strcpy(estate->type, type);
	estate->address = malloc(sizeof(char) * (strlen(address) + 1));
	if (estate->address == NULL)
	{
		free(estate->type);
		free(estate);
		return NULL;
	}
	strcpy(estate->address, address);
	estate->surface = surface;
	estate->price = price;

	return estate;
}

void destroyEstate(Estate* estate)
{
	/// <summary>
	/// Frees the memory allocated for an estate
	/// </summary>
	/// <param name="estate"> The estate to be deallocated </param>
	if (estate == NULL)
		return;
	free(estate->type);
	free(estate->address);
	free(estate);
}

int isEqual(Estate estate1, Estate estate2)
{
	/// <summary>
	/// Checks if 2 estates have a unique identifier (address)
	/// </summary>
	/// <param name="estate1"></param>
	/// <param name="estate2"></param>
	/// <returns> 1 if they are equal 
	///	          0 otherwise </returns>
	return strcmp(estate1.address, estate2.address) == 0;
}

void printEstate(Estate* es)
{
	/// <summary>
	/// Prints an estate to the console
	/// </summary>
	/// <param name="estate"> The estate to be printed </param>
	printf("Type: %s| Address: %s| Surface: %d| Price: %d\n", es->type, es->address, es->surface, es->price);
}

char* getType(Estate* estate)
{
	/// <summary>
	/// Getter for the type of an estate
	/// </summary>
	/// <param name="estate"> The estate </param>
	/// <returns> The type of the estate </returns>
	return estate->type;
}

char* getAddress(Estate* estate)
{
	/// <summary>
	/// Getter for the address of an estate
	/// </summary>
	/// <param name="estate"> The estate </param>
	/// <returns> The address of the estate </returns>
	return estate->address;
}

int getSurface(Estate* estate)
{
	/// <summary>
	/// Getter for the surface of an estate
	/// </summary>
	/// <param name="estate"> The estate </param>
	/// <returns> The surface of the estate </returns>
	return estate->surface;
}

int getPrice(Estate* estate)
{
	/// <summary>
	/// Getter for the price of an estate
	/// </summary>
	/// <param name="estate"> The estate </param>
	/// <returns> The price of the estate </returns>
	return estate->price;
}

void setType(Estate* estate, char* type)
{
	/// <summary>
	/// Setter for the type of an estate
	/// </summary>
	/// <param name="estate"> The estate </param>
	/// <param name="type"> The new type </param>
	free(estate->type);
	estate->type = malloc(sizeof(char) * (strlen(type) + 1));
	strcpy(estate->type, type);
}

void setAddress(Estate* estate, char* address)
{
	/// <summary>
	/// Setter for the address of an estate
	/// </summary>
	/// <param name="estate"> The estate </param>
	/// <param name="address"> The new address </param>
	free(estate->address);
	estate->address = malloc(sizeof(char) * (strlen(address) + 1));
	strcpy(estate->address, address);
}

void setSurface(Estate* estate, int surface)
{
	/// <summary>
	/// Setter for the surface of an estate
	/// </summary>
	/// <param name="estate"> The estate </param>
	/// <param name="surface"> The new surface </param>
	estate->surface = surface;
}

void setPrice(Estate* estate, int price)
{
	/// <summary>
	/// Setter for the price of an estate
	/// </summary>
	/// <param name="estate"> The estate </param>
	/// <param name="price"> The new price </param>
	estate->price = price;
}

Estate* copyEstate(Estate* e)
{
	/// <summary>
	/// Creates a copy of an estate
	/// </summary>
	/// <param name="estate"> The estate to be copied </param>
	/// <returns> The copy of the estate </returns>
	Estate* newEstate = createEstate(e->type, e->address, e->surface, e->price);
	return newEstate;
}