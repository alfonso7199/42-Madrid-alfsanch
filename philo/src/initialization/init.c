/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (error_exit("Malloc error (forks)"));
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (error_exit("Mutex init error (forks)"));
		i++;
	}
	return (SUCCESS);
}

static int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (error_exit("Malloc error (philos)"));
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].data = data;
		i++;
	}
	return (SUCCESS);
}

static int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (error_exit("Mutex init error (print)"));
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
		return (error_exit("Mutex init error (meal)"));
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
		return (error_exit("Mutex init error (stop)"));
	return (SUCCESS);
}

int	init_data(t_data *data)
{
	if (init_mutexes(data) != SUCCESS)
		return (FAILURE);
	if (init_forks(data) != SUCCESS)
		return (FAILURE);
	if (init_philos(data) != SUCCESS)
		return (FAILURE);
	data->start_time = get_current_time();
	if (data->start_time == -1)
		return (error_exit("Time error"));
	data->stop_simulation = 0;
	return (SUCCESS);
}

int	init_threads(t_data *data)
{
	int	i;

	data->start_time = get_current_time();
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
			return (error_exit("Thread creation error"));
		i++;
	}
	if (pthread_create(&data->monitor, NULL, monitor_routine, data) != 0)
		return (error_exit("Monitor thread error"));
	return (0);
}
