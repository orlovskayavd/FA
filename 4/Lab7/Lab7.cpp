#pragma warning(disable:4996)
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_INSTRUCTION_LENGTH 50
#define COMMANDS_COUNT 14


char* commands[COMMANDS_COUNT] =
{
        "ADD", "MULT", "SUB", "POW", "DIV", "REM", "XOR", "INPUT", "OUTPUT", "=", "()OP", "OP()", "LEFT", "RIGHT"
}, ** cm;

typedef struct Var {
    char* name;
    int data;

} Var;

Var* vars;
int size = 0;

int cmp(Var* a, Var* b) {
    char* aPtr = a->name;
    char* bPtr = b->name;

    for (int i = 0; i < strlen(a->name); ++i) {
        if (*aPtr > * bPtr) return 1;
        if (*aPtr < *bPtr) return -1;
    }
    if (strlen(a->name) < strlen(b->name)) return -1;
    return 0;
}

int cmpChar(char* a, char* b) {
    char* aPtr = a;
    char* bPtr = b;

    for (int i = 0; i < strlen(a); ++i) {
        if (*aPtr > * bPtr) return 1;
        if (*aPtr < *bPtr) return -1;
        aPtr++;
        bPtr++;
    }
    if (strlen(a) < strlen(b)) return -1;
    return 0;
}

void setVar(char* str, int data) {
    char* name = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(name, str);
    for (int i = 0; i < size; ++i) {
        if (strcmp(name, vars[i].name) == 0) {
            vars[i].data = data;
            return;
        }
    }
    size++;
    vars = realloc(vars, sizeof(Var) * size);
    vars[size - 1].name = name;
    vars[size - 1].data = data;
    qsort(vars, size, sizeof(Var), (int (*)(const void*, const void*)) cmp);
}

Var getVar(char* name) {
    int l = 0;
    int r = size;
    int c = 0;

    while (l != r) {
        c = (l + r) / 2;
        if (cmpChar(vars[c].name, name) == 1) {
            r = c;
        }
        else if (cmpChar(vars[c].name, name) == -1) {
            l = c;
        }
        else {
            return vars[c];
        }
    }
    if (strcmp(vars[c].name, name) == 0) {
        return vars[c];
    }
    else {
        printf("Error\n");
        exit(3);
    }
}

void clearBuf(char* buf) {
    char* b = buf;
    while (*b) *b++ = 0;
}

int fromTenToBase(int ten, int base) {
    int tmp = ten;
    int count = 0;
    while (tmp != 0) {
        tmp /= 2;
        count++;
    }
    int arr[count], * ptr = arr;
    int result = 0;

    while (ten != 0) {
        *ptr++ = ten % base;
        ten /= base;
    }

    for (int i = count; i >= 0; --i) {
        result = result * 10 + arr[i];
    }
    return result;
}

int fromBaseToTen(int num, int base) {
    int tmp = num;
    int count = 0;
    while (tmp != 0) {
        tmp /= 10;
        count++;
    }
    int arr[count], * ptr = arr;
    int result = 0;

    while (num != 0) {
        *ptr++ = num % 10;
        num /= 10;
    }

    for (int i = count - 1; i >= 0; --i) {
        result = result * base + arr[i];
    }
    return result;
}

int main(int argc, char* argv[]) {
    int op = 0; //0 - операция слева, 1 - операция справа
    int varOrientation = 0; // 0 - сохраняет влево, 1 - вправо


    FILE* fIn;
    char c;
    char buf[MAX_INSTRUCTION_LENGTH], * b = buf;
    int inMultilineComment = 0, commandId;
    char optionsFileName[BUFSIZ];
    if (argc < 3) {
        FILE* tmp = fopen("tmp", "r");
        if (tmp == NULL) exit(-5);
        fscanf(tmp, "%s", optionsFileName);
        fclose(tmp);
    }
    else {
        strcpy(optionsFileName, argv[2]);
    }

    FILE* tmp = fopen("tmp", "w");
    if (tmp == NULL) exit(-5);
    fprintf(tmp, "%s", optionsFileName);
    fclose(tmp);

    FILE* optionsFile;

    if (!(optionsFile = fopen(optionsFileName, "r"))) {
        printf("Couldn't open file");
        exit(-1);
    }


    while (!feof(optionsFile)) {
        c = fgetc(optionsFile);
        if (c == '#') {
            while (c != '\n' && c != EOF) {
                c = fgetc(optionsFile);
            }
        }
        else if (c != '\n' && c != 0 && c != -1) {
            *b++ = toupper(c);
        }
        else if (c == '\n' || c == -1) {
            *b = 0;
            b = buf;

            for (cm = commands; cm - commands < COMMANDS_COUNT; cm++) {
                if (strstr(buf, *cm) == buf) {
                    break;
                }
            }

            commandId = cm - commands;

            switch (commandId) { // 10 11 12
            case 10: //op
                op = 1;
                break;


            case 11:
                op = 0;
                break;

            case 12:
                varOrientation = 0;
                break;

            case 13:
                varOrientation = 1;
                break;

            default: {
                char left[BUFSIZ];
                char right[BUFSIZ];

                sscanf(buf, "%s %s", left, right);
                commands[commandId] = malloc(sizeof(char) * (strlen(right) + 1));
                strcpy(commands[commandId], right);
            }


            }


        }
    }
    //        for (cm = commands; cm - commands < COMMANDS_COUNT; cm++) {
    //            printf("%s\n", *cm);
    //        }

    //ПОСЛЕ ФАЙЛА НАСТРОЕК
    if (!(fIn = fopen(argv[1], "r")))
    {
        printf("Couldn't open file");
        exit(-1);
    }
    b = buf;
    while (!feof(fIn))
    {
        c = fgetc(fIn);
        if (c == ' ' || c == '\n')
        {

        }
        else if (c == '[')
        {
            inMultilineComment++;
        }
        else if (c == ']')
        {
            inMultilineComment--;
            if (inMultilineComment == -1)
            {
                printf("Comment err\n");
                exit(-7);
            }
        }
        else if (c == EOF && inMultilineComment)
        {
            printf("Comment err\n");
            exit(-7);
        }
        else if (!inMultilineComment && c != ';' && c != 0 && c != -1)
        {
            *b++ = toupper(c);
        }
        else if (c == ';' && !inMultilineComment)
        {
            *b = 0;
            b = buf;
            if (isalpha(*b) || *b == '(')
            {
                for (cm = commands; cm - commands < COMMANDS_COUNT; cm++)
                {
                    if (strstr(buf, *cm))
                    {

                        break;
                    }
                }
                commandId = cm - commands;


                //получаем аргументы
                char left[BUFSIZ], * lPtr = left;
                char right[BUFSIZ], * rPtr = right;

                while (*b != '(') b++;
                b++;

                if (commandId == 7 || commandId == 8) {
                    while (*b != ')') *lPtr++ = *b++;
                }
                else {
                    while (*b != ',') *lPtr++ = *b++;
                    b++;
                    while (*b != ')') *rPtr++ = *b++;
                }
                *lPtr = 0;
                *rPtr = 0;
                int l = 0;
                int r = 0;

                char varName[BUFSIZ], * varNamePtr = varName;
                if (commandId != 8) { // Для всех, кроме вывода
                    char* startOfEq = strstr(buf, commands[9]);
                    if (varOrientation == 0) {
                        b = buf;
                        while (b != startOfEq) {
                            *varNamePtr++ = *b++;
                        }
                    }
                    else {
                        startOfEq++;
                        while (*startOfEq != 0) {
                            *varNamePtr++ = *startOfEq++;
                        }
                    }
                    *varNamePtr = 0;
                    if (commandId != 7) {
                        l = getVar(left).data;
                        r = getVar(right).data;
                    }
                }

                switch (commandId) { //"ADD", "MULT", "SUB", "POW", "DIV", "REM", "XOR", "INPUT", "OUTPUT", "=", "OP", "LEFT", "RIGHT"
                case 0: {
                    setVar(varName, l + r);
                    break;
                }
                case 1: {
                    setVar(varName, l * r);
                    break;
                }

                case 2: {
                    setVar(varName, l - r);
                    break;
                }

                case 3: {
                    setVar(varName, pow(l, r));
                    break;
                }

                case 4: {
                    setVar(varName, l / r);
                    break;
                }

                case 5: {
                    setVar(varName, l % r);
                    break;
                }

                case 6: {
                    setVar(varName, l ^ r);
                    break;
                }

                case 7: { // in
                    int num;
                    printf("%s: ", varName);
                    scanf("%d", &num);
                    printf("\n");
                    setVar(varName, num);
                    break;
                }

                case 8: { // out
                    printf("%d\n", getVar(left).data);
                }


                }
                b = buf;
            }
        }
    }

    fclose(fIn);
    return 0;
}

