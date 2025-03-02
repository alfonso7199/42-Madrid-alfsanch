/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:14:58 by alfsanch          #+#    #+#             */
/*   Updated: 2024/11/06 17:15:04 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINITALK_H
# define MINITALK_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <signal.h>
# include "libft/libft.h"

typedef struct s_mini
{
	int	pid_server;
	int	pid_client;
}	t_mini;

t_mini	*client_start(void);
t_mini	*server_start(void);
void	client_send(t_mini *talk, char *message);
void	server_receive(int boolean);
int		ft_atoi(const char *str);
void	ft_putstr(char *str);
void	ft_putnbr(int num);
void	handle_signal(int sig, siginfo_t *info, void *context);

#endif