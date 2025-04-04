/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

int	count_elements(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	has_duplicates(char **args)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = count_elements(args);
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_atoi(args[i]) == ft_atoi(args[j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	validate_input(int argc, char **argv)
{
	int		i;
	long	num;
	char	**args;

	i = 0;
	if (argc == 2)
		args = ft_split(argv[1], ' ');
	else
		args = argv + 1;
	while (args[i])
	{
		num = ft_atoi(args[i]);
		if (num < INT_MIN || num > INT_MAX || !is_valid_number(args[i]))
			error_exit("Error");
		i++;
	}
	if (has_duplicates(args))
		error_exit("Error");
	if (argc == 2)
		free_string_array(args);
}
