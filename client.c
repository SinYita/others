/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedu <wedu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:58:37 by wedu              #+#    #+#             */
/*   Updated: 2025/09/14 22:43:48 by wedu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static volatile int	g_ack = 0;

static void	ack_handler(int sig)
{
	(void)sig;
	g_ack = 1;
}

static int	ft_atoi(const char *str)
{
	long	res;
	int		neg;
	int		i;

	res = 0;
	neg = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return ((int)res * neg);
}

static void	send_bit(int server_pid, int bit_value)
{
	g_ack = 0;
	if (bit_value)
		kill(server_pid, SIGUSR1);
	else
		kill(server_pid, SIGUSR2);
	// 等待服务器确认
	while (!g_ack)
		usleep(50);
}

static void	send_char(int server_pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		send_bit(server_pid, c & (1 << bit));
		bit++;
	}
}

static void	send_string(int server_pid, char *message)
{
	int	i;

	i = 0;
	while (message[i] != '\0')
	{
		send_char(server_pid, message[i]);
		i++;
	}
	send_char(server_pid, '\0');
}

int	main(int argc, char **argv)
{
	int					server_pid;
	char				*message;
	struct sigaction	sa;

	if (argc != 3)
	{
		write(1, "Error\n", 7);
		return (1);
	}
	// 设置确认信号处理器
	sa.sa_handler = ack_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	send_string(server_pid, message);
	return (0);
}
