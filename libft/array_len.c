
#include "libft.h"

size_t  array_len(char **str)
{
    size_t  i;
    size_t  j;
    size_t  len;

    if (!*str)
        return (0);
    i = 1;
    j = 0;
    len = 0;
    while (str[i])
    {
        j = 0;
        while(str[i][j])
            j++;
        len += j;
        i++;
    }
    return (len);
}

/*#include <stdio.h>
int main(int ac, char **av)
{
    if (ac > 1)
    {
        size_t result = array_len(av);
        printf("%ld\n", result);
    }
    return 0;
}*/