#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

#define SIZELINE 128

struct Car {
	int year;
	char* manufacturer;
	float cc;

};

typedef struct Car Car;
typedef struct Node Node;

struct Node {
	Car car;
	Node* next;
};


//inserare la inceput si la final
void insertAtBeginning(Node** start, Car car)
{
	Node* newNode = malloc(sizeof(Node));
	
	newNode->car = car;
	newNode->next = *start;
	*start = newNode;
}

void insertAtEnd(Node** start, Car car)
{  //E bine?
	Node* newNode = malloc(sizeof(Node));
	newNode->car = car;
	newNode->next = NULL;

	if (*start) {
		Node* aux = *start;
		while (aux->next)
		{
			aux = aux->next;
			
		}
		aux->next = newNode;
	}
	else
	{
		*start = newNode;
	}
}


//stergrele la inceput si la final
Car deleteAtBeginning(Node** start)
{
	Node* deleted = *start;
	 *start=(*start)->next;
	
		Car deletedCar = deleted->car;
		free(deleted);
		return deletedCar;
}

//stergere la final
Car deleteAtEnd(Node** start)
{
	if (*start)
	{
		Node* temp = *start;
		Node* prev = NULL;
		while (temp->next)// =! 0
		{
			prev = temp;
			temp = temp->next;
		}

		Car deletedCar = temp->car;
		prev->next = NULL;
		free(temp);
		return deletedCar;

	}
	else
	{
		printf("Lista este goala");
	}
}


//INSERARE LA MIJLOC
void insertAtMiddle(Node** start, Car car, int position) {
	Node* newNode = malloc(sizeof(Node));
	newNode->car = car;

	if (*start == NULL || position <= 1) {
		newNode->next = *start;
		*start = newNode;
		return;
	}

	Node* aux = *start;
	int count = 1;

	while (aux->next != NULL && count < position - 1) {
		aux = aux->next;
		count++;
	}

	newNode->next = aux->next;
	aux->next = newNode;
}

//STERGERE DE LA MIJLOC
void deleteAtMiddle(Node** start, int position)
{
	if (*start == NULL || position <= 0)
		return; // Lista este goală sau poziția nu este validă

	Node* temp = *start;

	// Dacă trebuie să ștergem primul nod
	if (position == 1)
	{
		*start = temp->next;
		free(temp);
		return;
	}

	Node* prev = NULL;
	int count = 1;

	while (temp != NULL && count < position)
	{
		prev = temp;
		temp = temp->next;
		count++;
	}

	// Dacă poziția este mai mare decât lungimea listei
	if (temp == NULL)
		return;

	// Scoatem nodul din listă
	prev->next = temp->next;
	free(temp);
}




void printCar(Car car)
{
	printf("%s din anul %d are %.2f\n ", car.manufacturer, car.year, car.cc);
}
void parseListAndPrint(Node* start)
{
	while (start)
	{
		printCar(start->car);
		start = start->next;
	}
}

// citire din fisier
Car readCarFromFile(FILE* f)
{
	char buffer[SIZELINE];
	fgets(buffer, SIZELINE, f);

	Car car;

	char* carData = NULL;
	
	carData = strtok(buffer, ",");
	car.year = atoi(carData);

	carData=strtok(NULL, ",");
	car.manufacturer = malloc(strlen(carData+1) * sizeof(char));
	strcpy(car.manufacturer, carData);

	carData = strtok(NULL, ",");
	car.cc = atof(carData);

	return car;
}


void readCarsFromFile(Node** start, int* noCar, const char* fileName)
{
	FILE* f;
	f = fopen(fileName, "r");

	char buffer[SIZELINE];
	fgets(buffer, SIZELINE, f);

	*noCar = (int)atol(buffer, NULL, 10);
	

	for (int i = 0; i < *noCar; i++)
	{
		insertAtBeginning(start, readCarFromFile(f));
	}
	fclose(f);

}

void readCARSFromFile(Node** start, int* noCar, const char* fileName)
{
	FILE* f;
	f = fopen(fileName, "r");

	char buffer[SIZELINE];
	fgets(buffer, SIZELINE, f);

	*noCar = (int)atol(buffer, NULL, 10);


	for (int i = 0; i < *noCar; i++)
	{
		insertAtEnd(start, readCarFromFile(f));
	}
	fclose(f);

}


void readCARSFromFileMIDDLE(Node** start, int* noCar, const char* fileName)
{
	FILE* f;
	f = fopen(fileName, "r");

	char buffer[SIZELINE];
	fgets(buffer, SIZELINE, f);

	*noCar = (int)atol(buffer, NULL, 10);


	for (int i = 0; i < *noCar; i++)
	{
		insertAtMiddle(start,readCarFromFile(f), 2);
	}
	fclose(f);

}


int main()
{
	Node* list = NULL;
	int nr = 0;

	//inserare la inceput 
	printf("\n----------------inserare la inceput ----------------------------------\n");
	readCarsFromFile(&list, &nr, "Cars.txt");
	parseListAndPrint(list);


	//inserare la final
	printf("\n-------------------inserare la final-------------------------------\n");
	readCARSFromFile(&list, &nr, "Cars.txt");
	parseListAndPrint(list);

	//stergere
	printf("\n----------------stergere de la inceput----------------------------------\n");
	Car delete = deleteAtBeginning(&list);
	parseListAndPrint(list);
	printf("\n----a fost sters---------: ");
	printCar(delete);


	printf("\n----------------stergere de la final----------------------------------\n");
	Car deleted = deleteAtEnd(&list);
	parseListAndPrint(list);
	printf("\n----a fost sters---------: ");
	printCar(deleted);


	Car car1 = { 2009,"FORD FOCUS", 3.4 };
	printf("\n----------------inserare la mijloc----------------------------------\n");
	insertAtMiddle(&list, car1, 5);
	parseListAndPrint(list);


}
	//printf("\n----------------stergere la mijloc----------------------------------\n");
	//deleteAtMiddle(&list, 4);
	//parseListAndPrint(&list);


	
