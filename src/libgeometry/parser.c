#include <stdio.h>
#include <string.h>

#include <lexer.h>
#include <parser.h>

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

int parser()
{
    char geom[25] = {0};
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