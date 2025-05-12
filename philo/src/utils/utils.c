/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"
#include <sys/time.h>
#include <stdio.h>

long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	error_exit(const char *msg)
{
	printf("Error: %s\n", msg);
	return (FAILURE);
}

void	safe_print(t_philo *philo, char *msg)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!simulation_should_stop(philo->data))
	{
		time = get_current_time() - philo->data->start_time;
		if (ft_strcmp(msg, "died") == 0)
			printf(RED"[%lld]"RESET" %d %s\n", time, philo->id, msg);
		else
			printf(GREEN"[%lld]"RESET" %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	precise_usleep(long ms, t_data *data)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < ms && !simulation_should_stop(data))
		usleep(100);
}
