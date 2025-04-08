/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <alfsanch@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:14:58 by alfsanch          #+#    #+#             */
/*   Updated: 2024/11/06 17:15:04 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_bit_received;

void	send_bit(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		g_bit_received = 0;
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit++;
		while (g_bit_received == 0)
			usleep(10);
	}
}

void	send_message(int pid, char *message)
{
	int	i;

	i = 0;
	while (message[i])
	{
		send_bit(pid, message[i]);
		i++;
	}
	send_bit(pid, '\0');
}

void	ok_bit(int sig)
{
	if (sig == SIGUSR1)
		g_bit_received = 1;
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		ft_printf("Usage: %s <PID> <message>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_printf("ERROR: Invalid PID (must be greater than 0)!\n");
		return (EXIT_FAILURE);
	}
	signal(SIGUSR1, ok_bit);
	send_message(pid, argv[2]);
	return (EXIT_SUCCESS);
}
