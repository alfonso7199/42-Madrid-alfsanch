/*
Write a function that reverses (in-place) a string.

It must return its parameter.

Your function must be declared as follows:

char    *ft_strrev(char *str);
*/
char    *ft_strrev(char *str)
{
    int i;
    int j;
    char tmp;

    i = 0;
    j = 0;

    while (str[i])
        i++;
    i--;

    while (j < i)
    {
        tmp = str[j];
        str[j] = str[i];
        str[i] = tmp;
        j++;
        i--;
    }
    return (str);
}