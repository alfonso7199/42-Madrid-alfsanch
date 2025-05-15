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

static int	take_first_fork(t_philo *philo, pthread_mutex_t *first)
{
	pthread_mutex_lock(first);
	safe_print(philo, "has taken a fork");
	if (simulation_should_stop(philo->data))
	{
		pthread_mutex_unlock(first);
		return (0);
	}
	return (1);
}

static int	take_second_fork(t_philo *philo, pthread_mutex_t *first,
							pthread_mutex_t *second)
{
	pthread_mutex_lock(second);
	safe_print(philo, "has taken a fork");
	if (simulation_should_stop(philo->data))
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return (0);
	}
	return (1);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (simulation_should_stop(philo->data))
		return (0);
	if (philo->data->num_philos == 1)
		return (handle_single_philo(philo), 0);
	select_forks(philo, &first, &second);
	if (!take_first_fork(philo, first))
		return (0);
	if (!take_second_fork(philo, first, second))
		return (0);
	return (1);
}

void	leave_forks(t_philo *philo)
{
	if (philo->data->num_philos == 1)
		return ;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
