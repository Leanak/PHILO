/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:29:20 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/23 18:11:41 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_fork(t_general *general, int i)
{
	general->philo[i].fork_r = &general->fork[i];
	if (i != general->number_of_philo)
		general->philo[i].fork_l = &general->fork[i + 1];
	else
		general->philo[i].fork_l = &general->fork[i - (general->number_of_philo
				+ 1)];
	if (general->philo[i].fork_l && general->philo[i].fork_r)
		printf("YES");
	pthread_mutex_init(general->philo[i].fork_r, NULL);
	pthread_mutex_init(general->philo[i].fork_l, NULL);
}

void	*test(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	printf("%d\n", philo->philo_ID);
	return (NULL);
}

void	*fonction_vide(t_general *general, void* (*f)(void *), int i)
{
	pthread_create(&general->philo[i].philo_thread, NULL, f, &general->philo[i]);
	init_fork(general, i);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_general general;
	int i;

	i = 0;
	if (!(ac >= 5 && ac <= 6))
		return (1);
	general.number_of_philo = ft_atoi(av[1]);
	while (i < 1)
	{
		general.philo[i].philo_ID = i + 1;
		fonction_vide(&general, test, i);
		usleep(5000);
		i++;
	}
	i = 0;
	while (i < general.number_of_philo)
	{
		pthread_join(general.philo[i].philo_thread, NULL);
		i++;
	}
	printf("Main here");
	return (0);
}