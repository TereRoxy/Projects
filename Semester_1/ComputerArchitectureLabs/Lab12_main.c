#include <stdio.h>
#include <stdlib.h>

extern int is_prime(unsigned int n);

int main()
{
    int x, n;
    scanf("%u", &n);
    for (int i=1; i<=n; i++)
    {
        scanf("%u", x);
        if (is_prime(x)==1)
            printf("%u", x);
    }

    return 0;
}
