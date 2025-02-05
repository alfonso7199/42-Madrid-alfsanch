int ft_strlen(char *str)
{
    unsigned    i; 

    i = 0;
    while (*str++)
    {
        i++;
    }
    return (i);
}