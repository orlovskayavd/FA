#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define WOLF 4
#define GOAT 2
#define CABBAGE 1

int	take(FILE* f1, char* first_coast, char* second_coast, char* boat)
{
	char c;
	char word[10];
	char* ptr = word;
	const char* object[3] = { "cabbage", "goat", "wolf" };
	int i;

	while ((c = getc(f1)) != '\n')
		*ptr++ = c;
	*ptr = 0;
	for (i = 0; i < 3; i++)
	{
		if (!(strcmp(word, object[i])))
		{
			if (!(*boat & 7))
			{
				*boat |= 1 << i;
				if ((*boat & 8))
				{
					if ((*second_coast & (1 << i)))
						*second_coast ^= 1 << i;
					else
					{
						printf("Command: <take> ERROR!!! No %s\n", word);
						return (0);
					}
				}
				else
				{
					if ((*first_coast & (1 << i)))
						*first_coast ^= 1 << i;
					else
					{
						printf("Command: <take> ERROR!!! No %s\n", word);
						return (0);
					}
				}
				break;
			}
			else
			{
				printf("Command: <take> ERROR!!! Boat is full\n");
				return (0);
			}
		}
	}
	return ((i != 3));
}

int	put(FILE* f1, char* first_coast, char* second_coast, char* boat)
{
	if (!boat)
	{
		printf("ERROR!!! Boat is empty\n");
		return (0);
	}
	else
	{
		if ((*boat & 8))
		{
			*second_coast |= *boat & 7;
			*boat &= 8;
		}
		else
		{
			*first_coast |= *boat & 7;
			*boat &= 8;
		}
	}
}

int	move(FILE* f1, char* first_coast, char* second_coast, char* boat)
{
	if ((*boat & 8))
	{
		if (*second_coast == 3 || *second_coast == 6 || *second_coast == 7)
		{
			printf("Command: <Move> Game over!!!\n");
			return (0);
		}
		else
			*boat ^= 8;
	}
	else
	{
		if (*first_coast == 3 || *first_coast == 6 || *first_coast == 7)
		{
			printf("Command: <Move> Game over!!!\n");
			return (0);
		}
		else
			*boat ^= 8;
	}
}

int	check(FILE* f1, char* str, char* first_coast, char* second_coast, char* boat)
{
	const char* array[3] = { "take", "put;", "move;" };
	int (*f[3])(FILE * f1, char* first_coast, char* second_coast, char* boat) { take, put, move };
	int i;

	for (i = 0; i < 3; i++)
	{
		if (!(strcmp(array[i], str)))
		{
			if (!(f[i](f1, first_coast, second_coast, boat)))
				return (0);
			break;
		};
	}
	return ((i != 3));
}

int	main(int argc, char** argv)
{
	FILE* f1;
	char first_coast = 7, second_coast = 0, boat = 0;
	char c;
	char word[20];
	char* ptr = word;

	f1 = fopen(argv[1], "r");
	while ((c = getc(f1)) != EOF)
	{
		if (isalpha(c) || c == ';')
			*ptr++ = c;
		if (c == ' ' || c == '\t' || c == '\n')
		{
			*ptr = 0;
			if (!(check(f1, word, &first_coast, &second_coast, &boat)))
				return (0);
			ptr = word;
		}
	}
	if (second_coast == 7)
		printf("WIN!!!\n");
	else
		printf("LOSING!!!\n");
	return (0);
	fclose(f1);
}
