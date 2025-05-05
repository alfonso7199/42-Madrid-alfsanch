/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int check_philo_death(t_data *data, int i)
{
    long long current_time;
    long long time_since_last_meal;

    pthread_mutex_lock(&data->meal_mutex);
    current_time = get_current_time();
    time_since_last_meal = current_time - data->philos[i].last_meal_time;
    
    if (time_since_last_meal > data->time_to_die && !data->stop_simulation)
    {
        pthread_mutex_lock(&data->print_mutex);
        printf("%lld %d died\n", current_time - data->start_time, data->philos[i].id);
        data->stop_simulation = 1;
        pthread_mutex_unlock(&data->print_mutex);
        pthread_mutex_unlock(&data->meal_mutex);
        return (1);
    }
    pthread_mutex_unlock(&data->meal_mutex);
    return (0);
}

void *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;
    int all_full;

    while (1)
    {
        i = 0;
        all_full = 1;
        while (i < data->num_philos)
        {
            if (check_philo_death(data, i))
                return (NULL);
            
            pthread_mutex_lock(&data->meal_mutex);
            if (data->num_meals != -1 && 
                data->philos[i].meals_eaten < data->num_meals)
                all_full = 0;
            pthread_mutex_unlock(&data->meal_mutex);
            
            i++;
        }
        
        if (data->num_meals != -1 && all_full)
        {
            pthread_mutex_lock(&data->print_mutex);
            data->stop_simulation = 1;
            pthread_mutex_unlock(&data->print_mutex);
            return (NULL);
        }
        
        usleep(1000);
    }
    return (NULL);
}

int all_philos_full(t_data *data)
{
    int i;
    int full_count;
    
    if (data->num_meals == -1)
        return (0);
        
    full_count = 0;
    i = 0;
    while (i < data->num_philos)
    {
        pthread_mutex_lock(&data->meal_mutex);
        if (data->philos[i].meals_eaten >= data->num_meals)
            full_count++;
        pthread_mutex_unlock(&data->meal_mutex);
        i++;
    }
    return (full_count == data->num_philos);
}