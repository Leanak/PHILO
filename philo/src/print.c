/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:09:50 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/31 15:04:53 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	fork_and_print(t_philo *philo, t_general *general)
{
	if (philo->fork_l < philo->fork_r)
	{
		pthread_mutex_lock(philo->fork_l);
		safe_print(philo, general, "has taken a fork");
		pthread_mutex_lock(philo->fork_r);
		safe_print(philo, general, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->fork_r);
		safe_print(philo, general, "has taken a fork");
		pthread_mutex_lock(philo->fork_l);
		safe_print(philo, general, "has taken a fork");
	}
	philo->check_fork = true;
}

void	safe_print(t_philo *philo, t_general *general, char *message)
{
	pthread_mutex_lock(&general->safe_dead);
	if (general->dead)
	{
		pthread_mutex_unlock(&general->safe_dead);
		return ;
	}
	pthread_mutex_unlock(&general->safe_dead);
	pthread_mutex_lock(&general->safe_print);
	printf("%lu %d %s\n", get_time() - general->start_time, philo->philo_id,
		message);
	pthread_mutex_unlock(&general->safe_print);
}
