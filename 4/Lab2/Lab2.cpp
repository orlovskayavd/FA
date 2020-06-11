#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define BUFF_SIZE 30

typedef struct
{
	int		data;
	char* name;
}		variable;

typedef struct
{
	int size;
	variable* array;
}		vector;

void	print_error(int a, char* str)
{
	if (a == 1)
		printf("No variable: %s\n", str);
	if (a == 0)
		printf("No file: %s\n", str);
	exit(a);
}

int comp(const variable* a, const variable* b)
{
	return (strcmp(a->name, b->name));
}

variable* search(vector* vec, char* str)
{
	int left = 0;
	int right = vec->size - 1;
	int midd = 0;

	while (1)
	{
		midd = (left + right) / 2;
		if (strcmp(vec->array[midd].name, str) > 0)
			right = midd - 1;
		else if (strcmp(vec->array[midd].name, str) < 0)
			left = midd + 1;
		else
			return (vec->array + midd);
		if (left > right)
			return (0);
	}
}

void	print(char* str, vector* vec)
{
	variable* temp;

	if (strlen(str) == 6)
		for (int i = 0; i < vec->size; i++)
			printf("%s = %d\n", vec->array[i].name, vec->array[i].data);
	else
	{
		str = strchr(str, ' ') + 1;
		str[strlen(str) - 2] = 0;
		temp = search(vec, str);
		if (!temp)
			print_error(1, str);
		printf("%s = %d\n", temp->name, temp->data);
	}
}

int action(int a, int b, char c)
{
	switch (c)
	{
	case '+':
		return (a + b);
	case '-':
		return (a - b);
	case '/':
		if (!b)
		{
			printf("del zero\n");
			exit(2);
		}
		return (a / b);
	case '*':
		return (a * b);
	case '%':
		if (!b)
		{
			printf("del zero\n");
			exit(2);
		}
		return (a % b);
	default:
		break;
	}
}

char* search_oper(char* str)
{
	str--;
	while (*++str)
		if (*str == '+' || *str == '-' || *str == '*'
			|| *str == '/' || *str == '%')
			return(str);
}

variable* creat_el(char* name, int data, vector* vec)
{
	variable* temp;

	vec->size++;
	if (vec->size == 1)
		vec->array = (variable*)malloc(sizeof(variable));
	else
		vec->array = (variable*)realloc(vec->array, sizeof(variable) * vec->size);
	vec->array[vec->size - 1].name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	temp = vec->array + vec->size - 1;

	strcpy(vec->array[vec->size - 1].name, name);
	vec->array[vec->size - 1].data = data;
	qsort(vec->array, vec->size, sizeof(vec->array[0]), (int(*) (const void*, const void*)) comp);
	return (search(vec, name));
}

void	operation(char* str, vector* vec)
{
	char* arg1, * arg2, * arg3;
	variable* arg1_v, * arg2_v, * arg3_v;
	char oper;

	arg1 = str;
	arg2 = strchr(str, '=');
	*arg2++ = 0;
	if (!(arg1_v = search(vec, arg1)))
		arg1_v = creat_el(arg1, 0, vec);
	arg3 = search_oper(arg2);
	oper = *arg3;
	*arg3++ = 0;
	arg3[strlen(arg3) - 2] = 0;
	if (!(arg2_v = search(vec, arg2)))
		print_error(1, arg2);
	if (!(arg3_v = search(vec, arg3)))
		print_error(1, arg3);
	arg1_v->data = action(arg2_v->data, arg3_v->data, oper);
}

void push_array(char* str, vector* vec)
{
	char* data = str;
	int data_int;

	data = strchr(data, '=');
	*data++ = 0;
	data_int = atoi(data);
	creat_el(str, data_int, vec);
}

void	strtolower(char* str)
{
	while (*str)
		*str++ = tolower(*str);
}

void	parser(vector* vec, char* str)
{
	strtolower(str);
	if (strstr(str, "print"))
	{
		print(str, vec);
		return;
	}
	if (strchr(str, '+') || strchr(str, '-') || strchr(str, '*')
		|| strchr(str, '/') || strchr(str, '%'))
		operation(str, vec);
	else
		push_array(str, vec);
}

void	free_all(vector* vec)
{
	for (size_t i = 0; i < vec->size; i++)
		free(vec->array[i].name);
	free(vec->array);
}

int main(int argc, char** argv)
{
	FILE* f;
	vector		vec;
	char		buf[BUFF_SIZE];

	vec.size = 0;
	if (!(f = fopen(argv[1], "r")))
		print_error(0, argv[1]);
	while (fgets(buf, BUFF_SIZE, f))
		parser(&vec, buf);
	free_all(&vec);
}