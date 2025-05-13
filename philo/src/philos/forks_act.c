/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <alfsanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	safe_print(philo, "has taken a fork");
	while (!simulation_should_stop(philo->data))
		usleep(100);
	pthread_mutex_unlock(philo->left_fork);
}

static void	select_forks(t_philo *philo, pthread_mutex_t **first,
						pthread_mutex_t **second)
{
	if (philo->id % 2 == 0)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (simulation_should_stop(philo->data))
		return ;
	if (philo->data->num_philos == 1)
		return (handle_single_philo(philo));
	select_forks(philo, &first, &second);
	pthread_mutex_lock(first);
	safe_print(philo, "has taken a fork");
	if (philo->data->num_philos > 100)
		precise_usleep(50);
	pthread_mutex_lock(second);
	safe_print(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	if (simulation_should_stop(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	safe_print(philo, "is eating");
	precise_usleep(philo->data->time_to_eat);
}

void	leave_forks(t_philo *philo)
{
	if (philo->data->num_philos == 1)
		return ;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
