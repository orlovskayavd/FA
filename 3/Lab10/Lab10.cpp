#pragma warning(disable:4996)
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INSTRUCTION_LENGTH 11
#define COMMANDS_COUNT 12


void error(int errorId);
int command(const char* str, int a, int b);
void read_and_write(const char* str, int* a, int base);
#define ISGOOD(c) (isalnum(c) || c == ':' || c == '=' || \
c == '+' || c == '&' || c == '-' || c == '<' || c == '>' || \
c == '~' || c == '?' || c == '!' || c == '\\' || c == ',' || \
c == '(' || c == ')')

int array[32] = { 0 };

const char* com[COMMANDS_COUNT] =
{
	"\\", "+", "&", "->", "<-", "<>", "~", "+>", "?", "!",
	 "READ", "WRITE"
}, ** cm = com;

const char* errors[] =
{
	"Input file not found!!1!1",
	"Multiline comment wasn't opened",
	"Multiline comment wasn't closed",
	"Invalid instruction",
	"Command wasn't found"
};

int main(int argc, char* argv[])
{
	FILE* fIn;
	char c;
	char arg1, arg2, arg3;
	int	base = 0;
	int inMultilineComment = 0;
	char buf[MAX_INSTRUCTION_LENGTH + 1], * b = buf;

	if (!(fIn = fopen(argv[1], "r")))
		error(1);

	while (!feof(fIn))
	{
		c = fgetc(fIn);
		if (c == '%' && !inMultilineComment)
		{
			while ((c = fgetc(fIn)) != '\n' && c != EOF);
		}
		else if (c == '{')
		{
			inMultilineComment++;
		}
		else if (c == '}')
		{
			inMultilineComment--;
			if (inMultilineComment == -1)
				error(2);
		}
		else if (c == EOF)
		{
			if (inMultilineComment)
				error(3);
		}
		else if (ISGOOD(c) && !inMultilineComment)
		{
			*b++ = toupper(c);
			if (b - buf > MAX_INSTRUCTION_LENGTH)
				error(4);
		}
		else if (c == ';' && !inMultilineComment)
		{
			*b = 0;
			printf("%s\n", buf);
			b = buf;
			if (!isalpha(*b++))
				error(4);
			if (*b == ':')
			{
				arg1 = toupper(*buf);
				b++;
				if (*b++ != '=')
					error(4);
				if (*b == '\\')
				{
					b++;
					if (!isalpha(arg2 = toupper(*b)) || strlen(b) != 1)
						error(4);
					array[arg1 - 'A'] = command("\\", array[arg2 - 'A'], 0);
				}
				else if (isalpha(arg2 = toupper(*b++)))
				{

					for (cm = com + 1; cm - com < COMMANDS_COUNT; cm++)
						if (strstr(buf, *cm))
							break;
					if (cm - com == COMMANDS_COUNT)
						error(5);
					b += strlen(*cm);
					if (!isalpha(arg3 = toupper(*b)) || strlen(b) != 1)
						error(4);
					array[arg3 - 'A'] = command(*cm, array[arg2 - 'A'], array[arg3 - 'A']);
				}
				else
				{
					error(4);
				}
			}
			else if (isalpha(*b))
			{
				for (cm = com + 10; cm - com < COMMANDS_COUNT; cm++)
					if (strstr(buf, *cm) == buf)
						break;
				if (cm - com == COMMANDS_COUNT)
					error(5);
				b = buf + strlen(*cm);
				if (*b++ != '(')
					error(4);
				if (!isalpha(arg1 = toupper(*b++)))
					error(4);
				if (*b++ != ',')
					error(4);
				base = 0;
				while (isdigit(*b))
				{
					base = base * 10 + *b - '0';
					b++;
				}
				if (*b != ')' || strlen(b) != 1)
					error(4);
				read_and_write(*cm, array + arg1 - 'A', base);

			}
			else
			{
				error(4);
			}
			b = buf;
		}
	}

	fclose(fIn);
	return 0;
}

void error(int errorId)
{
	printf("Error #%d: %s", errorId, errors[errorId - 1]);
	exit(errorId);
}

// "+", "&", "->", "<-", "<>", "~", "+>", "?", "!", "\\"
// , "READ", "WRITE"

int command(const char* str, int a, int b)
{
	if (!(strcmp("+", str)))
		return(a | b);
	if (!(strcmp("&", str)))
		return(a & b);
	if (!(strcmp("->", str)))
		return((~a) | b);
	if (!(strcmp("<-", str)))
		return(a | (~b));
	if (!(strcmp("<>", str)))
		return(a + b);
	if (!(strcmp("~", str)))
		return(a | b);
	if (!(strcmp("+>", str)))
		return(a | b);
	if (!(strcmp("?", str)))
		return(a | b);
	if (!(strcmp("!", str)))
		return(a | b);
	if (!(strcmp("\\", str)))
		return(~a);
}

void read_and_write(const char* str, int* a, int base)
{
	char res_str[33];
	int	result = 0;
	char* ptr = res_str;
	int	temp = *a;

	if (!(strcmp(str, "READ")))
	{
		scanf("%s", res_str);
		while (*ptr)
		{
			if (!isalnum(*ptr))
				error(4);
			result = result * base + (isalpha(*ptr) ? toupper(*ptr) - 'A' + 10 : *ptr - '0');
			ptr++;
		}
		*a = result;
	}
	else
	{
		ptr = res_str + 32;
		if (temp < 0)
			temp *= -1;
		while ((temp / base))
		{
			*ptr-- = ((temp % base > 9) ? temp % base - 10 + 'A' : temp % base + '0');
			temp /= base;
		}
		*ptr = ((temp % base > 9) ? temp % base - 10 + 'A' : temp % base + '0');
		if (*a < 0)
		{
			ptr--;
			*ptr = '-';
		}
		printf("%s\n", ptr);
	}

}