/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_act.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
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

void take_forks(t_philo *philo)
{
    if (philo->data->num_philos == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        safe_print(philo, "has taken a fork");
        precise_usleep(philo->data->time_to_die * 2, philo->data);
        return;
    }
    
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        safe_print(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        safe_print(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        safe_print(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        safe_print(philo, "has taken a fork");
    }
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->meal_mutex);
    philo->last_meal_time = get_current_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->data->meal_mutex);
    
    safe_print(philo, "is eating");
    precise_usleep(philo->data->time_to_eat, philo->data);
}

void leave_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void sleep_philo(t_philo *philo)
{
    safe_print(philo, "is sleeping");
    precise_usleep(philo->data->time_to_sleep, philo->data);
}

void think(t_philo *philo)
{
    safe_print(philo, "is thinking");
}

int simulation_should_stop(t_data *data)
{
    int stop;
    
    pthread_mutex_lock(&data->meal_mutex);
    stop = data->stop_simulation;
    pthread_mutex_unlock(&data->meal_mutex);
    return (stop);
}

void set_simulation_stop(t_data *data, int value)
{
    pthread_mutex_lock(&data->meal_mutex);
    data->stop_simulation = value;
    pthread_mutex_unlock(&data->meal_mutex);
}