/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 11:44:47 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/31 20:48:07 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	destroy_mutexes(t_general *general)
{
	int	i;

	i = 0;
	while (i < general->number_of_philo)
	{
		pthread_mutex_destroy(&general->philo[i].safe_meal);
		i++;
	}
	i = 0;
	while (i < general->number_of_philo)
	{
		pthread_mutex_destroy(&general->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&general->safe_full);
	pthread_mutex_destroy(&general->safe_dead);
	pthread_mutex_destroy(&general->safe_print);
}

void	*start_philo(t_general *general, int i)
{
	general->philo[i].philo_id = i + 1;
	general->philo[i].general = general;
	general->philo[i].nb_meals = 0;
	general->philo[i].last_meal = general->start_time;
	pthread_mutex_init(&general->philo[i].safe_meal, NULL);
	init_fork(general, i);
	pthread_create(&general->philo[i].philo_thread, NULL, routine,
		&general->philo[i]);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_general	general;
	int			i;

	i = -1;
	if (!(ac >= 5 && ac <= 6))
	{
		printf("Wrong number of args\n");
		return (1);
	}
	if (!init_general(&general, ac, av) || general.error == -1)
	{
		printf("Arguments not valid\n");
		return (1);
	}
	while (++i < general.number_of_philo)
		start_philo(&general, i);
	pthread_create(&general.monitor, NULL, routine_monitor, &general);
	i = -1;
	while (++i < general.number_of_philo)
		pthread_join(general.philo[i].philo_thread, NULL);
	pthread_join(general.monitor, NULL);
	destroy_mutexes(&general);
	return (0);
}
