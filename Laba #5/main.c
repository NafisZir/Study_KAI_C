#include <stdio.h>
#include <stdlib.h>

unsigned long long solution(unsigned long long a, int shift)
{
    unsigned long long n_o, n_e, x, c = 1, r;
    int i = 1, b;
    x = (c << 62);

    n_o = (a&0x5555555555555555);   // выделяем единицы нечетных битов
    n_e = (a&0xAAAAAAAAAAAAAAAA);   // выделяем единицы четных битов

    while(i <= shift)
    {
         b = (n_o & 1);
         n_o = n_o >> 2;
         if(b == 1)
         {
             n_o = (n_o|x);
         }
         ++i;
    }
    r = (n_o|n_e);
    return r;
}

int main(int argc, char *argv[])
{
    char *end;
    unsigned long long a = strtoull(argv[1], &end, 10);
    int a2 = atoi(argv[2]);
    unsigned long long r;

    printf("%s %llu\n", "Initial number: ", a);

    r = solution(a, a2);
    printf("%s %llu", "Result: ", r);
    return 0;
}
