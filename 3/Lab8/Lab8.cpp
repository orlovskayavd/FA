#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct	s_pessenger
{
	char number[20];
	char departure_airport[20];
	char departure_city[20];
	char arrival_airport[20];
	char arrival_city[20];
	char departure_time[20];
	char arrival_time[20];
}Pessenger;

int	push_struct(Pessenger** pess, FILE* f1)
{
	int flag = 0;
	char c;
	char* ptr_number;
	char* ptr_depar_airport;
	char* ptr_depar_city;
	char* ptr_depar_time;
	char* ptr_arrival_city;
	char* ptr_arrival_airport;
	char* ptr_arrival_time;
	char* ptr_namber;
	int i = 0;
	int size = 10;

	*pess = (Pessenger*)malloc(sizeof(Pessenger) * (size + 1));
	ptr_number = (*pess)[i].number;
	ptr_depar_airport = (*pess)[i].departure_airport;
	ptr_depar_city = (*pess)[i].departure_city;
	ptr_depar_time = (*pess)[i].departure_time;
	ptr_arrival_airport = (*pess)[i].arrival_airport;
	ptr_arrival_city = (*pess)[i].arrival_city;
	ptr_arrival_time = (*pess)[i].arrival_time;
	while ((c = fgetc(f1)) != EOF)
	{
		if (c == ' ')
		{
			flag++;
			continue;
		}
		if (c == '\n')
		{
			i++;
			*ptr_number = 0;
			*ptr_arrival_city = 0;
			*ptr_arrival_time = 0;
			*ptr_arrival_airport = 0;
			*ptr_depar_airport = 0;
			*ptr_depar_city = 0;
			*ptr_depar_time = 0;
			if (i >= size)
			{
				size += 10;
				*pess = (Pessenger*)realloc((*pess), sizeof(Pessenger) * size);
			}
			flag = 0;
			ptr_number = (*pess)[i].number;
			ptr_depar_airport = (*pess)[i].departure_airport;
			ptr_depar_city = (*pess)[i].departure_city;
			ptr_depar_time = (*pess)[i].departure_time;
			ptr_arrival_airport = (*pess)[i].arrival_airport;
			ptr_arrival_city = (*pess)[i].arrival_city;
			ptr_arrival_time = (*pess)[i].arrival_time;
			continue;
		}
		switch (flag)
		{
		case (0):
			*ptr_number++ = c;
			break;
		case (1):
			*ptr_depar_city++ = c;
			break;
		case (2):
			*ptr_depar_airport++ = c;
			break;
		case (3):
			*ptr_depar_time++ = c;
			break;
		case (4):
			*ptr_arrival_city++ = c;
			break;
		case (5):
			*ptr_arrival_airport++ = c;
			break;
		case (6):
			*ptr_arrival_time++ = c;
			break;
		default:
			break;
		}
	}
	*pess = (Pessenger*)realloc((*pess), sizeof(Pessenger) * i);
	return (i);
}

void print_struct(Pessenger* pess, int size)
{
	for (int i = 0; i < size; i++)
		printf("number: %s\ndeparture_city: %s\ndeparture_airport: %s\ndeprture_time: %s\narrival_city: %s\narrival_airport: %s\narrival_time: %s\n\n",
			pess[i].number, pess[i].departure_city, pess[i].departure_airport, pess[i].departure_time,
			pess[i].arrival_city, pess[i].arrival_airport, pess[i].arrival_time);
}

void del(Pessenger** pess, int* size, const char* number)
{
	int i;

	for (i = 0; i < *size; i++)
		if (!(strcmp(number, (*pess)[i].number)))
			break;
	for (int j = i; j < (*size - 1); j++)
		(*pess)[i] = (*pess)[i + 1];
	(*size)--;
	*pess = (Pessenger*)realloc((*pess), sizeof(Pessenger) * *size);
}

void add(Pessenger** pess, int* size)
{
	(*size)++;
	*pess = (Pessenger*)realloc((*pess), sizeof(Pessenger) * *size);
	printf("write number:\n");
	scanf("%s", (*pess)[*size - 1].number);
	printf("write departure_city:\n");
	scanf("%s", (*pess)[*size - 1].departure_city);
	printf("write departure_airport:\n");
	scanf("%s", (*pess)[*size - 1].departure_airport);
	printf("write departure_time:\n");
	scanf("%s", (*pess)[*size - 1].departure_time);
	printf("write arrival_city:\n");
	scanf("%s", (*pess)[*size - 1].arrival_city);
	printf("write arrival_airport:\n");
	scanf("%s", (*pess)[*size - 1].arrival_airport);
	printf("write arrival_time:\n");
	scanf("%s", (*pess)[*size - 1].arrival_time);

}

int	main(int argc, char** argv)
{
	Pessenger* pess;
	FILE* f1;
	int			size = 0;

	if (argc != 2)
	{
		printf("ERROR\n");
		return (0);
	}
	if (!(f1 = fopen(argv[1], "r")))
	{
		printf("No file\n");
		return (0);
	}
	size = push_struct(&pess, f1);
	print_struct(pess, size);
	del(&pess, &size, "1WRTF23");
	print_struct(pess, size);
	// add(&pess, &size);
	print_struct(pess, size);
	free(pess);
}