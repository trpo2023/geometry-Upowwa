#pragma once

typedef struct circle {
    double x;
    double y;
    double raduis;
} Circle;

void take_circle(Circle* circle, int* column);
void print_circle(Circle* circle);
int parser();