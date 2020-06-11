#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct	s_string
{
	char* str;
	int	size;
}String;


String ft_strnew(const char* str)
{
	String str_new;

	str_new.size = strlen(str);
	str_new.str = (char*)malloc(sizeof(char) * (str_new.size + 1));
	strcpy(str_new.str, str);
	return (str_new);
}

void ft_strdel(String* str)
{
	str->size = 0;
	free(str->str);
	str->str = NULL;
}

int	ft_strcmp(String str1, String str2)
{
	if (str1.size != str2.size)
		return (0);
	return (!(strcmp(str1.str, str2.str)));
}

String	ft_strcat(String* str1, String str2)
{
	String result;

	result.size = str1->size + str2.size;
	result.str = (char*)malloc(sizeof(char) * (result.size + 1));
	strcpy(result.str, str1->str);
	strcat(result.str, str2.str);
	ft_strdel(str1);
	str1->str = result.str;
	str1->size = result.size;
	return (*str1);
}

String ft_strdup(String str)
{
	String	str_new;

	str_new = ft_strnew(str.str);
	return (str_new);
}

int	main()
{
	String str, str2, str3;

	str = ft_strnew("First");
	printf("%s = %d\n", str.str, str.size);
	ft_strdel(&str);
	printf("%p = %d\n", str.str, str.size);
	str = ft_strnew("First");
	str2 = ft_strnew("Second");
	printf("%d\n", ft_strcmp(str, str2));
	ft_strcat(&str, str2);
	printf("%s\n", str.str);
	str3 = ft_strdup(str);
	printf("%s\n", str3.str);
	ft_strdel(&str3);
	ft_strdel(&str2);
}
