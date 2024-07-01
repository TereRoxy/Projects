#include "Tests.h"
#include <assert.h>
#include <string.h>

void test_all()
{
	test_estate();
	test_dynamic_array();
	test_repository();
	test_controller();
	test_operation();
}

void test_estate()
{
	printf("Test estate\n");
	Estate* estate = createEstate("house", "address", 100, 100);
	assert(strcmp(getType(estate), "house") == 0);
	assert(strcmp(getAddress(estate), "address") == 0);
	assert(getSurface(estate) == 100);
	assert(getPrice(estate) == 100);

	Estate* estate2 = copyEstate(estate);
	assert(isEqual(*estate, *estate2) == 1);
	
	destroyEstate(estate);
	destroyEstate(estate2);
}

void test_dynamic_array()
{
	printf("Test dynamic array\n");
	DynamicArray* da = createDynamicArray(2, &destroyEstate);
	Estate* estate = createEstate("house", "address", 100, 100);
	add(da, estate);
	assert(get_size(da) == 1);

	Estate* estate2 = createEstate("apartment", "address2", 200, 200);
	add(da, estate2);
	assert(get_size(da) == 2);

	Estate* estate3 = createEstate("penthouse", "address3", 300, 300);
	update(da, estate3, 0);
	Estate* es = get_elem(da, 0);
	assert(isEqual(*es, *estate3) == 1);

	delete_elem(da, 0);
	assert(get_size(da) == 1);
	delete_elem(da, 0);
	assert(get_size(da) == 0);

	destroy(da);
}

void test_repository()
{
	printf("Test repository\n");
	Repository* repo = createRepository();
	Estate* estate = createEstate("house", "address", 100, 100);
	addEstate(repo, estate);
	assert(getSize(repo) == 1);
	assert(isEqual(*getEstate(repo, 0), *estate) == 1);

	Estate* estate2 = createEstate("apartment", "address2", 200, 200);
	addEstate(repo, estate2);
	assert(getSize(repo) == 2);
	assert(isEqual(*getEstate(repo, 1), *estate2) == 1);

	char* address = "address";
	Estate* estate3 = createEstate("penthouse", address, 300, 300);
	updateEstate(repo, estate3, 0);
	assert(strcmp(getType(getEstate(repo, 0)), "penthouse") == 0);
	assert(getSurface(getEstate(repo, 0)) == 300);
	assert(getPrice(getEstate(repo, 0)) == 300);

	assert(deleteEstate(repo, 0) == 1);
	assert(getSize(repo) == 1);
	
	destroyRepository(repo);
}

void test_controller()
{
	printf("Test controller\n");
	Repository* repo = createRepository();
	OperationsStack* undoStack = createStack();
	OperationsStack* redoStack = createStack();
	Controller* ctrl = createRepoController(repo, undoStack, redoStack);

	Estate* estate = createEstate("house", "address", 100, 100);
	addEstateController(ctrl, "house", "address", 100, 100);
	assert(getSize(getRepo(ctrl)) == 1);
	assert(isEqual(*getEstate(getRepo(ctrl), 0), *estate) == 1);

	Estate* estate2 = createEstate("apartment", "address2", 200, 200);
	addEstateController(ctrl, "apartment", "address2", 200, 200);
	assert(getSize(getRepo(ctrl)) == 2);
	assert(isEqual(*getEstate(getRepo(ctrl), 1), *estate2) == 1);

	char* address = "address";
	assert(updateEstateController(ctrl, "penthouse", address, 300, 300) == 1);
	assert(strcmp(getType(getEstate(getRepo(ctrl), 0)), "penthouse") == 0);
	assert(getSurface(getEstate(getRepo(ctrl), 0)) == 300);
	assert(getPrice(getEstate(getRepo(ctrl), 0)) == 300);
	assert(updateEstateController(ctrl, "address3", "penthouse", "newAddress", 300, 300) == -1);

	assert(deleteEstateController(ctrl, address) == 1);
	assert(getSize(getRepo(ctrl)) == 1);

	assert(deleteEstateController(ctrl, address) == -1);

	destroyEstate(estate);
	destroyEstate(estate2);
	destroyRepoController(ctrl);
}

void test_operation()
{
	printf("Test operation\n");
	OperationsStack* undoStack = createStack();
	OperationsStack* redoStack = createStack();
	Controller* ctrl = createRepoController(createRepository(), undoStack, redoStack);
	Estate* estate = createEstate("house", "address", 100, 100);
	addEstateController(ctrl, "house", "address", 100, 100);
	assert(getSize(getRepo(ctrl)) == 1);
	assert(isEqual(*getEstate(getRepo(ctrl), 0), *estate) == 1);

	Estate* estate2 = createEstate("apartment", "address2", 200, 200);
	addEstateController(ctrl, "apartment", "address2", 200, 200);
	assert(getSize(getRepo(ctrl)) == 2);
	assert(isEqual(*getEstate(getRepo(ctrl), 1), *estate2) == 1);

	char* address = "address";
	assert(updateEstateController(ctrl, "penthouse", address, 300, 300) == 1);
	assert(strcmp(getType(getEstate(getRepo(ctrl), 0)), "penthouse") == 0);
	assert(getSurface(getEstate(getRepo(ctrl), 0)) == 300);
	assert(getPrice(getEstate(getRepo(ctrl), 0)) == 300);
	assert(updateEstateController(ctrl, "address3", "penthouse", "newAddress", 300, 300) == -1);

	assert(deleteEstateController(ctrl, address) == 1);
	assert(getSize(getRepo(ctrl)) == 1);

	assert(deleteEstateController(ctrl, address) == -1);

	destroyEstate(estate);
	destroyEstate(estate2);
	destroyRepoController(ctrl);
}