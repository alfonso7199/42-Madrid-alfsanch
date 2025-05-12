/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_act.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <alfsanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_usleep(philo->data->time_to_eat / 2, philo->data);
	while (!simulation_should_stop(philo->data))
	{
		take_forks(philo);
		eat(philo);
		leave_forks(philo);
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
}

void	sleep_philo(t_philo *philo)
{
	safe_print(philo, "is sleeping");
	precise_usleep(philo->data->time_to_sleep, philo->data);
}

void	think(t_philo *philo)
{
	safe_print(philo, "is thinking");
}

int	simulation_should_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->stop_mutex);
	stop = data->stop_simulation;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}
