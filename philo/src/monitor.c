/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:13:42 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/31 19:22:04 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_philo(t_philo *philo, t_general *general)
{
	pthread_mutex_lock(&philo->safe_meal);
	if (get_time() - philo->last_meal >= general->time_to_die)
	{
		safe_print(philo, general, "died");
		pthread_mutex_lock(&general->safe_dead);
		general->dead = 1;
		pthread_mutex_unlock(&general->safe_dead);
	}
	pthread_mutex_unlock(&philo->safe_meal);
}

bool	check_full(t_general *general)
{
	pthread_mutex_lock(&general->safe_full);
	if (general->all_full == general->number_of_philo)
	{
		pthread_mutex_unlock(&general->safe_full);
		pthread_mutex_lock(&general->safe_dead);
		general->dead = 1;
		pthread_mutex_unlock(&general->safe_dead);
		return (true);
	}
	pthread_mutex_unlock(&general->safe_full);
	return (false);
}

void	*routine_monitor(void *arg)
{
	int			i;
	t_general	*general;

	i = 0;
	general = (t_general *)arg;
	while (1)
	{
		if (!check_if_dead(general))
			break ;
		i = 0;
		while (i < general->number_of_philo)
		{
			check_philo(&general->philo[i], general);
			if (!check_if_dead(general))
				return (NULL);
			i++;
		}
		if (check_full(general))
			break ;
		usleep(50);
	}
	return (NULL);
}
