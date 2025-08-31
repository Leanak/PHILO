/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 12:52:08 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/31 18:15:43 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	think(t_general *general, t_philo *philo)
{
	int	time_to_think;

	time_to_think = general->time_to_die - general->time_to_eat
		- general->time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	safe_print(philo, general, "is thinking");
	if (time_to_think > 100)
		return (time_to_think - 100);
	return (0);
}

void	eating(t_philo *philo, t_general *general)
{
	fork_and_print(philo, general);
	safe_print(philo, general, "is eating");
	check_time_passing(general, general->time_to_eat);
	pthread_mutex_lock(&philo->safe_meal);
	philo->last_meal = get_time();
	philo->nb_meals++;
	if (philo->nb_meals == general->max_meal)
	{
		philo->full = true;
		general->all_full++;
		pthread_mutex_unlock(&philo->safe_meal);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		while (general->all_full != general->number_of_philo)
			usleep(50);
		return ;
	}
	pthread_mutex_unlock(&philo->safe_meal);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	sleeping(t_philo *philo, t_general *general)
{
	safe_print(philo, general, "is sleeping");
	check_time_passing(general, general->time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	t_general	*general;

	philo = (t_philo *)arg;
	general = (t_general *)philo->general;
	if (one_philo(general, philo))
		return (NULL);
	/* while (1)
	{
		pthread_mutex_lock(&general->safe_start);
		if (general->start)
		{
			pthread_mutex_unlock(&general->safe_start);
			break ;
		}
		pthread_mutex_unlock(&general->safe_start);
		usleep(50);
	} */
	if (philo->philo_id % 2 == 0)
	 	usleep(general->time_to_eat);
	while (1)
	{
		if (!check_if_dead(general))
			break ;
		eating(philo, general);
		if (!check_if_dead(general))
			break ;
		sleeping(philo, general);
		if (!check_if_dead(general))
			break ;
		check_time_passing(general, think(general, philo));
	}
	return (NULL);
}
