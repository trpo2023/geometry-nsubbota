#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ascii_bracket_left 40
#define ascii_bracket_right 41
#define zero 48
#define nine 57
typedef struct point {
    double x;
    double y;
}point;

typedef struct circle {
    point center;
    double radius;
}circle;
int left_bracket(char* str)
{
    int j = str[6];
    if (j == ascii_bracket_right) {
        return 1;
    }
    return 0;
}
int right_bracket(char* str)
{
    int j = ascii_bracket_left;
    for (int i = 9; i < ascii_bracket_left; i++) {
        if (str[i] == j)
            return i + 1;
    }
    return 0;
}
void strtolower(char* str)
{
    for (int i = 0; i < strlen(str); i++)
        str[i] = tolower(str[i]);
}

int isArguments(char* str)
{
    int ret = 0;
    int count = 0;
    int j = 0;
    int z = 0;
    for (int i = 7; str[i] != ',' && i < strlen(str); i++) {
        if ((str[i] != '.' && str[i] != ' ')
            && !(str[i] >= zero && str[i] <= nine)) {
            printf("Error at column %d: expected '<double>'\n",i+1);
            j = i+1;
            ret++;
            return 1;
        }
        if (str[i] >= zero && str[i] <= nine && str[i + 1] == ' ')
        {
            count++;
            j = i+1;
        }
        if (str[i] == '.' && str[i + 1] == ')')
        {
            count += 2;
            j = i+1;
        }
    }
    if (count + 1 != 2) {
        printf("Error at column %d: expected '<double>'\n",j);
        ret++;
        return ret;
    }
    int index = 0;
    for (int i = 0; i != strlen(str); i++) {
        if (str[i] == ',') {
            index = i + 1;
            i = strlen(str) - 1;
        }
    }
    for (; str[index] != ')' && index < strlen(str); index++) {
        if ((str[index] != '.' && str[index] != ' ')
            && !(str[index] >= 48 && str[index] <= 57)) {
            printf("Error at column %d: expected radius '<double>'\n",index+1);
            z = index+1;
            ret++;
            return 1;
        }
        if (str[index] >= 48 && str[index] <= 57 && str[index + 1] == ' ')
        {
            count++;
            z = index+1;
        }
        if (str[index] == '.' && str[index + 1] == ' ')
        {
            count += 2;
            z = index+1;
        }
    }
    if (count != 1) {
        printf("Error at column %d: expected radius '<double>'\n",z);
        ret++;
    }
    return ret;
}

int isEnd(char* str)
{
    int ret = 1;
    int firstBracket = 0;
    long int endingSymbol;
    if (str[strlen(str) - 1] == '\n')
        endingSymbol = strlen(str) - 2;
    else
        endingSymbol = strlen(str) - 1;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ')') {
            firstBracket = i;
            break;
        }
    }
    if (firstBracket == endingSymbol)
        ret = 0;
    return ret;
}
int issEnd(char* str)
{
    long int endingSymbol;
    if (str[strlen(str) - 1] == '\n')
        endingSymbol = strlen(str) - 2;
    else
        endingSymbol = strlen(str) - 1;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ')') {
        }
    }
    return endingSymbol;
}

int isObject(char* str)
{
    int ret = 1;
    char rec[100];
    for (int i = 0; i < 6; i++) {
        rec[i] = str[i];
    }
    char figure[] = "circle";
    if (strcmp(rec, figure) == 0) {
        ret = 0;
    }
    return ret;
}

int printErrors(char* str, int countObj)
{
	int z = right_bracket(str);
    int s = issEnd(str) - 1;
    printf("Position %d:\n", countObj);
    if (isObject(str))
        printf("Error at column 0: expected 'circle'\n");
    else if (left_bracket(str))
        printf("Error at column 7: expected '('\n");
    else if (right_bracket(str))
        printf("Error at column %d: expected ')'\n",z);
    else if (isArguments(str))
        return 0;
    else if (isEnd(str))
        printf("Error at column %d: unexpected token\n",s);
    else
        printf("%s\n", str);
    return 0;
}

int main()
{
    FILE* file;
    file = fopen("test.txt", "r");
    if (fopen("test.txt", "r") == NULL) {
        printf("File not found\n");
        exit(0);
    }
    char str1[100];
    int countObj = 0;
    while (fgets(str1, 99, file)) {
        countObj++;
        strtolower(str1);
        printErrors(str1, countObj);
    }
    fclose(file);
    return 0;
}

