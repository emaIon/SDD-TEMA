#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

//LISTA DUBLA INLANTUITA

#define LINESIZE 128

struct Car
{
	int year;
	char* manufacturer;
	float cc;
};

typedef struct Car Car;
typedef struct Node Node;
typedef struct DoublyLinkedList DLList;

struct Node {
	Car car;
	Node* next;
	Node* prev;
};

struct DoublyLinkedList {
	Node* start;
	Node* end;
};
//delete by manufacturer
void deleteByManufacturer(DLList* list, const char* manufacturer) {

	if (list->start) {
		Node* current = list->start;
		while (current) {
			Node* toDelete = current;
			current = current->next;

			if (strcmp(toDelete->car.manufacturer, manufacturer) == 0) {
				if (toDelete->prev) {
					toDelete->prev->next = toDelete->next;
				}
				else {
					list->start = toDelete->next;
				}

				if (toDelete->next) {
					toDelete->next->prev = toDelete->prev;
				}
				else {
					list->end = toDelete->prev;
				}

				free(toDelete->car.manufacturer);
				free(toDelete);
			}
		}
	}
	else
	{
		printf("lista e goala");
	}
}


// stergere in fct de an (de la mijloc)
void deleteByYear(DLList* list, int year) {
	if (list->start)
	{
		Node* current = list->start;

		while (current) {
			Node* toDelete = current;
			current = current->next;

			if (toDelete->car.year > year) {

				if (toDelete->prev) {
					toDelete->prev->next = toDelete->next;
				}
				else {
					list->start = toDelete->next;
				}

				if (toDelete->next) {
					toDelete->next->prev = toDelete->prev;
				}
				else {
					list->end = toDelete->prev;
				}


				free(toDelete->car.manufacturer);
				free(toDelete);
			}
		}
	}
	else
	{
		printf("lista e goala");
	}
}

//inserare in fct de an
void insertInMiddleByYear(DLList* list, Car car) {
	Node* newNode = malloc(sizeof(Node));
	newNode->car = car;
	newNode->next = NULL;
	newNode->prev = NULL;

	if (!list->start) {
		list->start = newNode;
		list->end = newNode;
		return;
	}

	Node* current = list->start;

	while (current && current->car.year < car.year) {
		current = current->next;
	}

	if (!current) {
		list->end->next = newNode;
		newNode->prev = list->end;
		list->end = newNode;
		return;
	}

	if (current == list->start) {
		newNode->next = list->start;
		list->start->prev = newNode;
		list->start = newNode;
		return;
	}

	newNode->next = current;
	newNode->prev = current->prev;
	current->prev->next = newNode;
	current->prev = newNode;
}

//inserare in fc de an daca an>2020
void insertInMiddleIfYearAbove2020(DLList* list, Car car) {

	if (car.year <= 2020) {
		printf(" Masina %s din anul %d nu a fost adaugata! Doar an > 2020 este permis.\n", car.manufacturer, car.year);
		return;
	}

	Node* newNode = malloc(sizeof(Node));
	newNode->car = car;
	newNode->next = NULL;
	newNode->prev = NULL;
	if (!list->start) {
		list->start = newNode;
		list->end = newNode;
		return;
	}

	Node* current = list->start;
	while (current && current->car.year < car.year) {
		current = current->next;
	}

	if (!current) {
		list->end->next = newNode;
		newNode->prev = list->end;
		list->end = newNode;
		return;
	}

}

void printCar(Car car)
{
	printf("%s din anul %d are %.2f\n", car.manufacturer, car.year, car.cc);
}

//adaugare a inceput
void insertAtBeginning(DLList* list, Car car)
{
	Node* newNode = malloc(sizeof(Node));
	newNode->car = car;

	newNode->next = list->start;
	newNode->prev = NULL;

	if (list->start)
	{
		list->start->prev = newNode;
	}
	else
	{
		list->end = newNode;
	}

	list->start = newNode;


}

//adaugare a final
void insertAtEnd(DLList* list, Car car)
{
	Node* newNode = malloc(sizeof(Node));
	newNode->car = car;

	newNode->next = NULL;
	newNode->prev = list->end;

	if (list->end)//=! 0
	{
		list->end->next = newNode;
	}
	else
	{
		list->start = newNode;
	}
	list->end = newNode;

}

//afisare insert
void parseBtoE(DLList list)
{
	if (list.start)
	{
		while (list.start)
		{
			printCar(list.start->car);
			list.start = list.start->next;
		}
	}
	else
	{
		printf("lista e goala");
	}
}
void parseEtoB(DLList list)
{
	if (list.end)
	{
		while (list.end)
		{
			printCar(list.end->car);
			list.end = list.end->prev;
		}
	}
	else
	{
		printf("lista e goala");
	}
}


//stergere de la inceput
Car deleteFromBeginning(DLList* list)
{
	if (list->start)
	{
		Node* deleted = list->start;
		Car deletedCar = deleted->car;//=list->start->car


		if (list->start->next)
		{
			list->start = list->start->next;
			list->start->prev = NULL;
			free(deleted);
			return deletedCar;
		}
		else
		{
			list->start = NULL;
			list->end = NULL;

			free(deleted);
			return deletedCar;
		}
	}
	else
	{
		Car empty = { .manufacturer = "-", .year = 0, .cc = 0 };
		return empty;
	}
}

//stergere de la final
Car deleteAtEnd(DLList* list)
{

	if (list->end)
	{
		Node* deleted = list->end;
		Car deletedCar = deleted->car;

		if (list->end->prev)
		{
			list->end = list->end->prev;
			list->end->next = NULL;

			free(deleted);
			return deletedCar;
		}
		else
		{
			list->end = NULL;
			list->start = NULL;
			free(deleted);
			return deletedCar;
		}
	}
	else
	{
		Car empty = { .manufacturer = "-", .year = 0, .cc = 0 };
		return empty;
	}

}



//citire din fisier
Car readCarFromFile(FILE* f)
{
	char buffer[LINESIZE];
	fgets(buffer, LINESIZE, f);

	Car car;
	char* carData = NULL;

	carData = strtok(buffer, ",");
	car.year = atoi(carData);

	carData = strtok(NULL, ",");
	car.manufacturer = malloc((strlen(carData) + 1) * sizeof(char));
	strcpy(car.manufacturer, carData);

	carData = strtok(NULL, ",");
	car.cc = atof(carData);

	return car;

}

void readCarsFromFile(DLList* list, int* noCars, const char* fileName)
{
	FILE* f;
	f = fopen(fileName, "r");

	int nrCars = 0;
	while (!feof(f))
	{
		insertAtBeginning(list, readCarFromFile(f));
		nrCars++;
	}
	*noCars = nrCars;
	fclose(f);

}



int main()
{
	int nr = 0;
	DLList list;
	list.start = NULL;
	list.end = NULL;

	readCarsFromFile(&list, &nr, "cars.txt");
	parseBtoE(list);

	printf("\n-------------delete by manufacturer--------\n");
	deleteByManufacturer(&list, "BMW");
	parseBtoE(list);

	printf("\n--------inserare de la inceput la final----------------\n");
	readCarsFromFile(&list, &nr, "cars.txt");
	parseBtoE(list);

	printf("\n-------inserare de la final la inceput-----------------\n");
	parseEtoB(list);

	printf("\n-------stergere de la inceput-----------------\n");
	Car delete = deleteFromBeginning(&list);
	parseBtoE(list);
	printf("\n-------elementul sters este: ");
	printCar(delete);

	printf("\n-------stergere de la final-----------------\n");
	Car deleteCar = deleteAtEnd(&list);
	parseBtoE(list);
	printf("\n-------elementul sters este: ");
	printCar(deleteCar);

	printf("\n-------stergere in functei de an (de la mijloc)-----------\n");
	deleteByYear(&list, 2020);
	parseBtoE(list);


	printf("\n-------inserare in functei de an (de la mijloc)-----------\n");
	insertInMiddleByYear(&list, (Car) { 2024, "Logan", 1.4 });
	insertInMiddleByYear(&list, (Car) { 2005, "Logan", 1.4 });
	insertInMiddleByYear(&list, (Car) { 2020, "Logan", 1.4 });
	parseBtoE(list);

	printf("\n-------inserare in functei de an >2020 (de la mijloc)-----------\n");
	insertInMiddleIfYearAbove2020(&list, (Car) { 2015, "Renault", 1.4 });
	insertInMiddleIfYearAbove2020(&list, (Car) { 2025, "Renault", 1.4 });
	insertInMiddleIfYearAbove2020(&list, (Car) { 2005, "Renault", 1.4 });

	parseBtoE(list);
}
