#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IN_NAME 1
#define BACK_BRACE 2
#define NOT_DOUBLE 3
#define UNEXPECT_TOKEN 4
#define EXPECT_COMMA 5
#define UNEXPECT_COMMA 6

typedef struct circle {
    double x;
    double y;
    double raduis;
} Circle;

void print_error(int column, int status)
{
    for (int i = 0; i < column; i++) {
        printf(" ");
    }
    printf("^\n");

    if (status == IN_NAME)
        printf("Error at column %d: expected 'circle'\n", column);
    if (status == NOT_DOUBLE)
        printf("Error at column %d: expected '<double>'\n", column);
    if (status == BACK_BRACE)
        printf("Error at column %d: expected '('\n", column);
    if (status == UNEXPECT_TOKEN)
        printf("Error at column %d: unexpected token\n", column);
    if (status == EXPECT_COMMA)
        printf("Error at column %d: expected ','\n", column);
    if (status == UNEXPECT_COMMA)
        printf("Error at column %d: unexpected ','\n", column);

    exit(EXIT_FAILURE);
}

void lower_string(char* string)
{
    while (*string != '\0') {
        *string = tolower(*string);
        string++;
    }
}

void delete_all_space(int* column)
{
    char curr_ch;
    while ((curr_ch = getchar()) == ' ') {
        *column += 1;
    }
    if (curr_ch != ' ')
        ungetc(curr_ch, stdin);
}

double get_number(int* column)
{
    char temp[25];
    char ch;
    int point_count = 0;
    int i = 0;
    int minus_count = 0;

    delete_all_space(column);

    while ((ch = getchar()) != ' ') {
        temp[i] = ch;

        if (temp[i] == '.') {
            point_count++;
            if (point_count > 1) {
                print_error(*column + i + 1, NOT_DOUBLE);
            }
        }

        if (temp[i] == '-') {
            minus_count++;
            if (minus_count > 1 || i > 0) {
                print_error(*column + i + 1, NOT_DOUBLE);
            }
        }

        if (temp[i] == ')') {
            ungetc(temp[i], stdin);
            i++;
            break;
        }

        if (temp[i] == ',') {
            ungetc(temp[i], stdin);
            break;
        }

        if (temp[i] == '(') {
            i++;
            print_error(*column + i, BACK_BRACE);
        }

        if (!isdigit(temp[i]) && temp[i] != '.' && temp[i] != '-') {
            i++;
            print_error(*column + i, NOT_DOUBLE);
        }

        i++;
    }

    delete_all_space(column);

    *column += i + 1;
    char* eptr;
    double number = strtod(temp, &eptr);
    return number;
}

void take_circle(Circle* circle, int* column)
{
    char curr_ch;
    circle->x = get_number(column);
    if ((curr_ch = getchar()) == ',') {
        print_error(*column + 1, UNEXPECT_COMMA);
    }
    ungetc(curr_ch, stdin);

    circle->y = get_number(column);
    if ((curr_ch = getchar()) != ',') {
        print_error(*column, EXPECT_COMMA);
    }

    circle->raduis = get_number(column);
    if ((curr_ch = getchar()) != ')') {
        print_error(*column, BACK_BRACE);
    }

    while ((curr_ch = getchar()) != '\n' && curr_ch != EOF) {
        if (curr_ch != ' ') {
            print_error(*column, UNEXPECT_TOKEN);
        }
        *column += 1;
    }
}

void print_circle(Circle* circle)
{
    printf("circle(%.2f %.2f, %.2f)\n", circle->x, circle->y, circle->raduis);
}

int main()
{
    char geom[25];
    char curr_ch;
    int column;

    printf("Enter geom (or q for exit):\n");
    while ((curr_ch = getchar()) != EOF && curr_ch != 'q') {
        column = 0;
        do {
            if (curr_ch == '(' || curr_ch == ' ') {
                lower_string(geom);
                if (strcmp(geom, "circle") == 0) {
                    Circle circle;
                    take_circle(&circle, &column);
                    printf("\nYour circle: \n");
                    print_circle(&circle);
                    break;
                } else {
                    print_error(0, IN_NAME);
                }
            }

            if (curr_ch == ')') {
                print_error(column, BACK_BRACE);
            }

            geom[column] = curr_ch;
            column++;

        } while ((curr_ch = getchar()) != '\n');
        puts("\nEnter a new geom (or q for exit):");
    }

    return 0;
}