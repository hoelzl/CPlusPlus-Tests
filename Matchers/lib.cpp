#include "lib.h"

double Approximate(double number)
{
    double result{ 0.0 };

    if (number < 0)
    {
        while (result > number)
        {
            result -= 0.1;
        }
    }
    else
    {
        while (result < number)
        {
            result += 0.1;
        }
    }
    return result;
}