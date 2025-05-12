/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MAX_PHILOS 250
# define STR_MAX_PHILOS "250"
# define SUCCESS 0
# define FAILURE 1

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

# define STDERR_FILENO 2
# define GREEN    "\033[32m"
# define RESET    "\033[0m"
# define RED      "\033[31m"

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	stop_mutex;
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	long long		start_time;
	int				stop_simulation;
	pthread_t		monitor;
}	t_data;

bool		validate_input(int argc, char **argv, t_data *data);
int			init_data(t_data *data);
long		get_current_time(void);
int			error_exit(const char *msg);
void		*philo_routine(void *arg);
void		*monitor_routine(void *arg);
int			init_threads(t_data *data);
void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		leave_forks(t_philo *philo);
void		sleep_philo(t_philo *philo);
void		think(t_philo *philo);
void		safe_print(t_philo *philo, char *msg);
void		precise_usleep(long ms, t_data *data);
int			simulation_should_stop(t_data *data);
void		set_simulation_stop(t_data *data, int value);
void		clean_resources(t_data *data);
int			clean_exit(t_data *data, int exit_code);
int			ft_atoi(const char *str);
int			ft_strcmp(char *s1, char *s2);

#endif