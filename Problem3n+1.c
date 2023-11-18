include <stdio.h>

/*
The 3n + 1 Problem
Consider the following algorithm to generate a sequence of numbers. Start with an
integer n. If n is even, divide by 2. If n is odd, multiply by 3 and add 1. Repeat this
process with the new value of n, terminating when n = 1. For example, the following
sequence of numbers will be generated for n = 22:

22 11 34 17 52 26 13 40 20 10 5 16 8 4 2 1

It is conjectured (but not yet proven) that this algorithm will terminate at n = 1 for
every integer n. Still, the conjecture holds for all integers up to at least 1, 000, 000.
For an input n, the cycle-length of n is the number of numbers generated up to and
including the 1. In the example above, the cycle length of 22 is 16. Given any two
numbers i and j, you are to determine the maximum cycle length over all numbers
between i and j, including both endpoints.

Input
The input will consist of a series of pairs of integers i and j, one pair of integers per
line. All integers will be less than 1,000,000 and greater than 0.

Output
For each pair of input integers i and j, output i, j in the same order in which they
appeared in the input and then the maximum cycle length for integers between and
including i and j. These three numbers should be separated by one space, with all three
numbers on one line and with one line of output for each line of input.
*/

int CycleSize(int x)
{
    int cycle;
    
    cycle = 1;
    while (x != 1) 
    {
        if (x % 2 == 0) // Se x for par
            x = x / 2;
        else // Se x for ímpar
            x = x * 3 + 1;
        cycle++;
    }
    return (cycle);
}

int MaxCycle(int a, int b)
{
    int maxCycle;
    int cycle;

    maxCycle = 0;
    if (a > b) 
    { // Se b > a, troque-os
        int temp = a;
        a = b;
        b = temp;
    }
    for (int i = a; i <= b; i++)
    {
        cycle = CycleSize(i);
        if (cycle > maxCycle) 
            maxCycle = cycle;
    }   
    return (maxCycle);
}

int main() 
{
    int a, b; // Variáveis de entrada

    while (scanf("%d %d", &a, &b) != EOF)
        printf("%d %d %d\n", a, b, MaxCycle(a, b));
    return (0);
}
