/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 11:48:50 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/31 18:14:10 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

long	ft_atol(char *str, int *error)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (*error = -1, 0);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		if (res > INT_MAX)
			return (*error = -1, 0);
		i++;
	}
	if (str[i] != '\0')
		return (*error = -1, 0);
	return (res);
}

bool	init_general(t_general *general, int ac, char **av)
{
	int	i;
	general->error = 0;
	general->dead = 0;
	general->all_full = 0;
	general->start_time = get_time();
	general->number_of_philo = ft_atol(av[1], &general->error);
	if (general->number_of_philo > 200 || general->number_of_philo <= 0)
		return (false);
	general->time_to_die = ft_atol(av[2], &general->error);
	general->time_to_eat = ft_atol(av[3], &general->error);
	general->time_to_sleep = ft_atol(av[4], &general->error);
	if (ac == 6)
		general->max_meal = ft_atol(av[5], &general->error);
	else
		general->max_meal = -1;
	if (general->max_meal == 0)
		return (false);
	i = 0;
	while (i < general->number_of_philo)
		pthread_mutex_init(&general->fork[i++], NULL);
	pthread_mutex_init(&general->safe_full, NULL);
	pthread_mutex_init(&general->safe_dead, NULL);
	pthread_mutex_init(&general->safe_print, NULL);
	return (true);
}

void	init_fork(t_general *general, int i)
{
	general->philo[i].fork_r = &general->fork[i];
	if (i != general->number_of_philo - 1)
		general->philo[i].fork_l = &general->fork[i + 1];
	else
		general->philo[i].fork_l = &general->fork[0];
}
