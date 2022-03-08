#include <cs50.h>
#include <stdio.h>

bool valid_triangle (double x, double y, double z);

int main (void)
{
    double a = get_double("Side a: ");
    double b = get_double("Side a: ");
    double c = get_double("Side a: ");

    bool answer = valid_triangle (a, b, c);
    if (answer == true)
    {
        printf ("Votre triangle formé de %f, %f, %f est valide\n", a, b, c);
    }
    else
    {
        printf ("Votre triangle formé de %f, %f, %f est non valide\n", a, b, c);
    }

}

bool valid_triangle (double x, double y, double z)
{
    if (x <= 0 || y <= 0 || z <= 0)
    {
        return false;
    }
    if ((x + y) <= z || (y + z) <= x || (z + x) <= y)
    {
        return false;
    }
    return true;
}