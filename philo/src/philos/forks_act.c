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

void	take_forks(t_philo *philo)
{
	if (simulation_should_stop(philo->data))
		return ;
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo, "has taken a fork");
		while (!simulation_should_stop(philo->data))
			usleep(100);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_t *first = philo->left_fork;
	pthread_mutex_t *second = philo->right_fork;
	if (philo->left_fork > philo->right_fork) {
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(first);
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock(second);
	safe_print(philo, "has taken a fork");
}

void eat(t_philo *philo)
{
    if (simulation_should_stop(philo->data))
        return;
    pthread_mutex_lock(&philo->data->meal_mutex);
    philo->last_meal_time = get_current_time();
    pthread_mutex_unlock(&philo->data->meal_mutex);
    safe_print(philo, "is eating");
    precise_usleep(philo->data->time_to_eat, philo->data);
    pthread_mutex_lock(&philo->data->meal_mutex);
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->data->meal_mutex);
}

void	leave_forks(t_philo *philo)
{
	if (philo->data->num_philos == 1)
		return ;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

/*
alfon@ESPTPB251:~/42-Madrid-alfsanch/philo$ ./philo 5 600 200 200 
1 1 has taken a fork
1 1 has taken a fork
1 1 is eating
1 3 has taken a fork
1 3 has taken a fork
1 3 is eating
201 3 is sleeping
201 2 has taken a fork
201 2 has taken a fork
201 2 is eating
201 1 is sleeping
201 4 has taken a fork
201 4 has taken a fork
201 4 is eating
201 5 has taken a fork
401 1 is thinking
401 4 is sleeping
401 5 has taken a fork
401 5 is eating
401 2 is sleeping
401 3 is thinking
401 3 has taken a fork
401 3 has taken a fork
401 3 is eating
601 4 is thinking
601 2 is thinking
601 2 has taken a fork
601 5 is sleeping
601 2 has taken a fork
601 2 is eating
601 3 is sleeping
601 4 has taken a fork
601 4 has taken a fork
601 4 is eating
601 1 has taken a fork
602 1 died
*/