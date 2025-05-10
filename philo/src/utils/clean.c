/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	clean_exit(t_data *data, int exit_code)
{
	int	i;

	if (data)
	{
		if (data->philos)
		{
			i = 0;
			while (i < data->num_philos)
			{
				if (data->philos[i].thread)
					pthread_join(data->philos[i].thread, NULL);
				i++;
			}
		}
		clean_resources(data);
	}
	return (exit_code);
}

void	clean_resources(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}
