#pragma once
#include "Controller.h"

typedef struct
{
	Controller* repoController;
}UI;

UI* createUI(Controller* ctrl);
void destroyUI(UI* service);
void print_menu();
int select_option(UI* service);
void add_estate_ui(UI* service);
void delete_estate_ui(UI* service);
void update_estate_ui(UI* service);
void display_estates_by_address(UI* service);
//void display_estates(Service* service, DynamicArray* estateList);
void display_by_type(UI* service);
void display_all_estates(UI* service);