/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <alfsanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_death(t_data *data, int i)
{
	long long	current_time;
	long long	last_meal;
	long long	time_since_meal;

	pthread_mutex_lock(&data->meal_mutex);
	current_time = get_current_time();
	last_meal = data->philos[i].last_meal_time;
	time_since_meal = current_time - last_meal;
	pthread_mutex_unlock(&data->meal_mutex);
	if (time_since_meal > data->time_to_die)
	{
		pthread_mutex_lock(&data->print_mutex);
		if (!data->stop_simulation)
		{
			printf("%lld %d died\n",
				current_time - data->start_time, data->philos[i].id);
			pthread_mutex_lock(&data->stop_mutex);
			data->stop_simulation = 1;
			pthread_mutex_unlock(&data->stop_mutex);
		}
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	return (0);
}

static int	check_all_philos_full(t_data *data)
{
	int	i;
	int	all_full;

	i = 0;
	all_full = 1;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->num_meals != -1
			&& data->philos[i].meals_eaten < data->num_meals)
			all_full = 0;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (all_full);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (check_philo_death(data, i))
				return (NULL);
			i++;
		}
		if (data->num_meals != -1 && check_all_philos_full(data))
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop_simulation = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
