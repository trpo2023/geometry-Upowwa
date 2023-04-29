#pragma once

#define IN_NAME 1
#define BACK_BRACE 2
#define NOT_DOUBLE 3
#define UNEXPECT_TOKEN 4
#define EXPECT_COMMA 5
#define UNEXPECT_COMMA 6

void print_error(int column, int status);
void lower_string(char* string);
void delete_all_space(int* column);
double get_number(int* column);