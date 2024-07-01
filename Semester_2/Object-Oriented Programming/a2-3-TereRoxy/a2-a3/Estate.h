#pragma once
//#define nullEstate createEstate("", "", 0, 0)
//#define TElem Estate

typedef struct{
	char* type;	//house, apartment, penthouse
	char* address; //unique
	int surface;
	int price;
}Estate;

Estate* createEstate(char* type, char* address, int surface, int price);
void destroyEstate(Estate* estate);
Estate* copyEstate(Estate* e);

int isEqual(Estate estate1, Estate estate2);
void printEstate(Estate* es);
char* getType(Estate* estate);
char* getAddress(Estate* estate);
int getSurface(Estate* estate);
int getPrice(Estate* estate);
void setType(Estate* estate, char* type);
void setAddress(Estate* estate, char* address);
void setSurface(Estate* estate, int surface);
void setPrice(Estate* estate, int price);
Estate* copyEstate(Estate* e);