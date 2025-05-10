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
#include "philo.h"

static bool	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static bool	validate_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (false);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
		{
			printf("Error: Argument %d is not a valid positive number\n", i);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	check_values(t_data *data)
{
	if (data->num_philos < 1)
	{
		printf("Error: There must be at least 1 philosopher\n");
		return (false);
	}
	if (data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_sleep < 60)
	{
		printf("Error: Time arguments must be at least 60ms\n");
		return (false);
	}
	if (data->num_meals != -1 && data->num_meals < 1)
	{
		printf("Error: Number of meals must be at least 1\n");
		return (false);
	}
	return (true);
}

bool	validate_input(int argc, char **argv, t_data *data)
{
	if (!validate_args(argc, argv))
		return (false);
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_meals = ft_atoi(argv[5]);
	else
		data->num_meals = -1;
	data->philos = NULL;
	data->forks = NULL;
	data->stop_simulation = 0;
	if (!check_values(data))
		return (false);
	return (true);
}
