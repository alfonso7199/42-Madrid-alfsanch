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
		usleep(1000);
	while (!simulation_should_stop(philo->data))
	{
		if (!take_forks(philo))
			break ;
		eat(philo);
		leave_forks(philo);
		if (simulation_should_stop(philo->data))
			break ;
		sleep_philo(philo);
		if (simulation_should_stop(philo->data))
			break ;
		think(philo);
	}
	return (NULL);
}

void	sleep_philo(t_philo *philo)
{
	safe_print(philo, "is sleeping");
	precise_usleep(philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	long long	think_time;

	safe_print(philo, "is thinking");
	if (philo->data->num_philos % 2 != 0)
	{
		think_time = (philo->data->time_to_eat * 2) - 10;
		if (think_time < 0)
			think_time = 0;
		if (think_time > 0)
			usleep(think_time * 100);
	}
}

void	eat(t_philo *philo)
{
	if (simulation_should_stop(philo->data))
		return ;
	safe_print(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	precise_usleep(philo->data->time_to_eat);
}

int	simulation_should_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->stop_mutex);
	stop = data->stop_simulation;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}
