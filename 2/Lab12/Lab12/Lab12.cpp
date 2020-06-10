#pragma warning(disable:4996)
#include <stdarg.h>
#include <stdio.h>
#include <math.h>

int	strfile(FILE* fread, const char* str)
{
	char c;
	const char* ptr;

	while ((c = getc(fread)) != -1)
	{
		ptr = str;
		if (c == *ptr)
		{
			ptr++;
			while (*ptr && (c = getc(fread)) == *ptr)
				ptr++;
			if (!*ptr)
				return (1);
		}
	}
	return (0);
}

void my_read(const char* str, int n, ...)
{
	va_list ptr;
	FILE* fread;
	char* name;

	va_start(ptr, n);
	for (size_t i = 0; i < n; i++)
	{
		name = va_arg(ptr, char*);
		if (!(fread = fopen(name, "r")))
		{
			printf("ERROR\n");
			return;
		}
		if (strfile(fread, str))
			printf("%s: YES\n", name);
		else
			printf("%s: NO\n", name);
		fclose(fread);
	}
	va_end(ptr);
}

int main()
{
	my_read("str", 2, "test.txt", "test1.txt");
	return 0;
}