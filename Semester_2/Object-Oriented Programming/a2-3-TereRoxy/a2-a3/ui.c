#include "ui.h"
#include <stdio.h>

UI* createUI(Controller* ctrl)
{
	UI* service = (UI*)malloc(sizeof(UI));
	if (service == NULL)
		return NULL;
	service->repoController = ctrl;
	return service;
}

void destroyUI(UI* service)
{
	destroyRepoController(service->repoController);
	free(service);
}

void print_menu()
{
	printf("\nReal Estate Manager \n");
	printf("1. Add an estate \n");
	printf("2. Delete an estate \n");
	printf("3. Update an estate \n");
	printf("4. List all estates \n");
	printf("5. Display all estates whose address contains a given string sorted by ascending price \n");
	printf("6. See all estates of a given type, having the surface greater than a user provided value \n");
	printf("7. Undo \n");
	printf("8. Redo \n");
	printf("0. Exit \n");
}

int select_option(UI* service)
{
	int option = -1;
	printf("Please enter your option: ");
	int succesful = scanf("%d", &option);
	if (succesful == 0)
		printf("Unsuccesful read. Invalid option. Try again \n");
	//printf("%d", option);

	switch (option)
	{
		case 1:
		{
			add_estate_ui(service);
			break;
		}
		case 2:
		{
			delete_estate_ui(service);
			break;
		}
		case 3:
		{
			update_estate_ui(service);
			break;
		}
		case 4:
		{
			display_all_estates(service);
			break;
		}
		case 5:
		{
			display_estates_by_address(service);
			break;
		}
		case 6:
		{
			display_by_type(service);
			break;
		}
		case 7:
		{
			if (undo(service->repoController))
				printf("Undo was successful \n");
			else
				printf("No more undos available \n");
			break;
		}
		case 8:
		{
			if (redo(service->repoController))
				printf("Redo was successful \n");
			else
				printf("No more redos available \n");
			break;
		}
		case 0:
		{
			return 0;
			break;
		}
		default:
			printf("Invalid option. Please try again \n");
	}
	return 1;
}

void add_estate_ui(UI* service)
{
	char type_buffer[20], address_buffer[256];
	int surface, price;
	printf("Type (house, apartment, penthouse): ");
	int ok_type = scanf("%16s", type_buffer);
	
	printf("Address: ");
	int ok_adr = scanf("%255s", address_buffer);
	//printf("%s", address_buffer);
	
	printf("Surface: ");
	int ok_surface = scanf("%d", &surface);
	printf("Price: ");
	int ok_price = scanf("%d", &price);
	
	if (strcmp(type_buffer, "house") != 0 && strcmp(type_buffer, "apartment") != 0 && strcmp(type_buffer, "penthouse") != 0)
	{
		printf("Invalid type \n");
		return;
	}
	if (surface < 0)
	{
		printf("Invalid surface \n");
		return;
	}
	if (price < 0)
	{
		printf("Invalid price \n");
		return;
	}
	
	int result = addEstateController(service->repoController, type_buffer, address_buffer, surface, price);
	if (result == 1)
		printf("Estate added successfully \n");
	else if (result == 0)
		printf("Repository error \n");
	else
		printf("Estate already exists \n");
}

void delete_estate_ui(UI* service)
{
	char address_buffer[256];
	printf("Address: ");
	scanf("%255s", address_buffer);

	int result = deleteEstateController(service->repoController, address_buffer);
	if (result == 1)
		printf("Estate deleted successfully \n");
	else if (result == 0)
		printf("Repository error \n");
	else
		printf("Estate does not exist \n");
}

void update_estate_ui(UI* service)
{
	char type_buffer[20], address_buffer[256];
	int surface, price;
	printf("Please enter the address of the estate to be updated: ");
	scanf("%255s", address_buffer);
	printf("Type (house, apartment, penthouse): ");
	scanf("%16s", type_buffer);
	printf("Surface: ");
	scanf("%d", &surface);
	printf("Price: ");
	scanf("%d", &price);

	if (strcmp(type_buffer, "house") != 0 && strcmp(type_buffer, "apartment") != 0 && strcmp(type_buffer, "penthouse") != 0)
	{
		printf("Invalid type \n");
		return;
	}
	if (surface < 0)
	{
		printf("Invalid surface \n");
		return;
	}
	if (price < 0)
	{
		printf("Invalid price \n");
		return;
	}

	int result = updateEstateController(service->repoController, type_buffer, address_buffer, surface, price);
	if (result == 1)
		printf("Estate updated successfully \n");
	else if (result == 0)
		printf("Repository error \n");
	else
		printf("Estate does not exist \n");
}

void display_estates_by_address(UI* service)
{
	char address_buffer[256];
	printf("String to be filtered by ('$' to display all): ");
	scanf("%255s", address_buffer);
	
	DynamicArray* estateList = getEstates(getRepo(service->repoController));

	if (estateList == NULL)
	{
		printf("Repository error \n");
		return;
	}
	
	DynamicArray* filteredEstates = filterEstateByAdress(estateList, address_buffer);

	if (filteredEstates->size == 0)
	{
		printf("No estates found \n");
		return;
	}
	
	sortByPrice(filteredEstates);

	print_array(filteredEstates);

	free(filteredEstates->elems);
	free(filteredEstates);
}

void display_by_type(UI* service)
{
	char type_buffer[20];
	printf("Type to be filtered by ('$' to display all types): ");
	scanf("%16s", type_buffer);
	if (strcmp(type_buffer, "house") != 0 && strcmp(type_buffer, "apartment") != 0 && strcmp(type_buffer, "penthouse") != 0 && strcmp(type_buffer, "$") != 0)
	{
		printf("Invalid type \n");
		return;
	}
	
	printf("Minimum surface: ");
	int min_surface;
	scanf("%d", &min_surface);

	DynamicArray* estateList = getEstates(getRepo(service->repoController));

	if (estateList == NULL)
	{
		printf("Repository error \n");
		return;
	}
 
	DynamicArray* filteredEstates = filterEstateByType(estateList, type_buffer);
	
	if (filteredEstates->size == 0)
	{
		printf("No estates of the given type found \n");
		return;
	}

	DynamicArray* newfilteredEstates = filterEstateBySurface(estateList, min_surface, 1);
	if (newfilteredEstates->size == 0)
	{
		printf("No estates with required surface found \n");
		return;
	}
	
	print_array(newfilteredEstates);
	free(filteredEstates->elems);
	free(filteredEstates);

	free(newfilteredEstates->elems);
	free(newfilteredEstates);
}

void display_all_estates(UI* service)
{
	DynamicArray* estateList = getEstates(getRepo(service->repoController));

	if (estateList == NULL)
	{
		printf("Repository error \n");
		return;
	}
	print_array(estateList);
}