#include <unistd.h>

int is_space(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
        char *str = argv[1];
        int end = 0;
    
        while (str[end])
            end++;
        end--; 

        int first = 1;
    
        while (end >= 0)
        {
            while (end >= 0 && is_space(str[end]))
                end--;
            if (end < 0)
                break;
            int word_end = end;
            while (end >= 0 && !is_space(str[end]))
                end--;
            int word_start = end + 1;

            if (!first)
                write(1, " ", 1);
            first = 0;
            while (word_start <= word_end)
                write(1, &str[word_start++], 1);

        }
	}
	write(1, "\n", 1);
	return (0);
}
