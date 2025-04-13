#include <stdlib.h>

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	count_words(char *str)
{
	int	count = 0;
	int	in_word = 0;

	while (*str)
	{
		if (!is_space(*str) && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (is_space(*str))
			in_word = 0;
		str++;
	}
	return (count);
}

char	*get_word(char *str, int *i)
{
	int		start;
	int		len;
	char	*word;

	while (is_space(str[*i]))
		(*i)++;
	start = *i;
	while (str[*i] && !is_space(str[*i]))
		(*i)++;
	len = *i - start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	word[len] = '\0';
	while (len--)
		word[len] = str[start + len];
	return (word);
}

char	**ft_split(char *str)
{
	int		i = 0;
	int		j = 0;
	int		word_count;
	char	**result;

	if (!str)
		return (NULL);
	word_count = count_words(str);
	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (j < word_count)
	{
		result[j] = get_word(str, &i);
		if (!result[j])
		{
			while (j-- > 0)
				free(result[j]);
			free(result);
			return (NULL);
		}
		j++;
	}
	result[j] = NULL;
	return (result);
}