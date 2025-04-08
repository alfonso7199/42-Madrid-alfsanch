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

void	send_bit(int pid, char c);
void	send_message(int pid, char *message);
void	ok_bit(int sig);
void	handle_signal(int sig, siginfo_t *info, void *context);
void	setup_signal_handlers(void);
int		ft_atoi(const char *str);
void	ft_putnbr(int num);

#endif