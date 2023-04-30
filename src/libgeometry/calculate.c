#include <math.h>

#include <calculate.h>

double get_perimeter(Circle circle)
{
    return 2 * M_PI * circle.raduis;
}

double get_area(Circle circle)
{
    return M_PI * circle.raduis * circle.raduis;
}