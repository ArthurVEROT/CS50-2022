#include <cs50.h>
#include <stdio.h>

int recursion_bis(int n);

int main(void)
{
    int n = get_int("n: ");
    int result = recursion_bis(n);
    printf("%i steps\n", result);
}

int recursion_bis(int n)
{
    if (n == 1)
    {
        return 0;
    }
    else if (n % 2 == 0)
    {
        return 1 + recursion_bis(n/2);
    }
    else
    {
        return 1 + recursion_bis(3*n+1);
    }
}