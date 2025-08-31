/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:06:00 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/31 15:23:44 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	one_philo(t_general *general, t_philo *philo)
{
	if (general->number_of_philo == 1)
	{
		safe_print(philo, general, "has taken a fork");
		usleep(general->time_to_die);
		return (true);
	}
	return (false);
}

bool	check_if_dead(t_general *general)
{
	pthread_mutex_lock(&general->safe_dead);
	if (general->dead)
	{
		pthread_mutex_unlock(&general->safe_dead);
		return (false);
	}
	pthread_mutex_unlock(&general->safe_dead);
	return (true);
}

void	check_time_passing(t_general *general, int duration)
{
	long	debut;

	debut = get_time();
	while (1)
	{
		pthread_mutex_lock(&general->safe_dead);
		if (general->dead == 1)
		{
			pthread_mutex_unlock(&general->safe_dead);
			break ;
		}
		pthread_mutex_unlock(&general->safe_dead);
		if (get_time() - debut >= duration)
			break ;
		usleep(50);
	}
}
