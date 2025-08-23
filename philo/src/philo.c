/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:29:20 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/24 00:46:35 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_if_dead(t_general *general, int duration)
{
	long	debut;

	debut = get_time();
	// (void)general;
	while (1)
	{
		pthread_mutex_lock(&general->safe_dead);
		if (general->dead)
			break ;
		pthread_mutex_unlock(&general->safe_dead);
		if (get_time () - debut >= duration)
			break ;
		usleep(50);
	}
	// if (get_time() - debut >= duration)
	// 	return ;
	// else
	// 	usleep(duration - get_time());
}

void	safe_print(t_philo *philo, t_general *general, char *message)
{
	pthread_mutex_lock(&general->safe_print);
	printf("%lu %d %s\n",get_time() - general->start_time, philo->philo_ID, message);
	pthread_mutex_unlock(&general->safe_print);
}

void	fork_and_print(t_philo *philo, t_general *general)
{
	pthread_mutex_lock(philo->fork_r);
	safe_print(philo, general, "has taken a fork");
	pthread_mutex_lock(philo->fork_l);
	safe_print(philo, general, "has taken a fork");
	philo->check_fork = true;
}

int	think(t_general *general, t_philo *philo)
{
	int	time_to_think;
	
	time_to_think = general->time_to_die - general->time_to_eat - general->time_to_sleep;
	safe_print(philo, general, "is thinking");
	return (time_to_think);
}

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_general *general = (t_general *)philo->general;
	
	if (general->number_of_philo == 1)
	{
		safe_print(philo, general, "has taken a fork");
		usleep(general->time_to_die);
		return (NULL);
	}
	if (philo->philo_ID % 2 == 0)
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(&general->safe_dead);
		if (general->dead)
			break ;
		pthread_mutex_unlock(&general->safe_dead);
		fork_and_print(philo, general);
		pthread_mutex_lock(&philo->happy_meal);
		philo->nb_meals++;
		pthread_mutex_unlock(&philo->happy_meal);
		//Commence a manger
		safe_print(philo, general, "is eating");
		sleep_if_dead(general, general->time_to_eat);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		safe_print(philo, general, "is sleeping");
		sleep_if_dead(general, general->time_to_sleep);
		sleep_if_dead(general, think(general, philo));
		//usleep(think(general, philo));
	}
	return (NULL);
}
void	*start_philo(t_general *general, int i)
{
	general->philo[i].philo_ID = i + 1;
	general->philo[i].general = general;
	general->philo[i].nb_meals = 0;
	pthread_mutex_init(&general->philo[i].happy_meal, NULL);
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
		return (1);
	// Parsing a ajouter + init general
	if (!init_general(&general, av, ac) || general.error == -1)
	{
		printf("Parsing pas ok\n");
		return (1);
	}
	while (++i < general.number_of_philo)
		start_philo(&general, i);
	//usleep(5000);
	i = -1;
	while (++i < general.number_of_philo)
		pthread_join(general.philo[i].philo_thread, NULL);
	return (0);
}
