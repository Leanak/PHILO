/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:29:20 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/24 19:11:18 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	printf("%lu %d %s\n", get_time() - general->start_time, philo->philo_ID,
		message);
	pthread_mutex_unlock(&general->safe_print);
}

void	check_philo(t_philo *philo, t_general *general)
{
	if (get_time() - philo->last_meal >= general->time_to_die)
	{
		safe_print(philo, general, "died");
		pthread_mutex_lock(&general->safe_dead);
		general->dead = 1;
		pthread_mutex_unlock(&general->safe_dead);
	}
}

void	*routine_monitor(void *arg)
{
	int			i;
	t_general	*general;

	i = 0;
	general = (t_general *)arg;
	while (1)
	{
		pthread_mutex_lock(&general->safe_dead);
		if (general->dead == 1)
		{
			pthread_mutex_unlock(&general->safe_dead);
			break ;
		}
		pthread_mutex_unlock(&general->safe_dead);
		i = 0;
		while (i < general->number_of_philo)
		{
			check_philo(&general->philo[i], general);
			i++;
		}
		pthread_mutex_lock(&general->safe_full);
		if (general->all_full == general->number_of_philo)
		{
			pthread_mutex_unlock(&general->safe_full);
			pthread_mutex_lock(&general->safe_dead);
			general->dead = 1;
			pthread_mutex_unlock(&general->safe_dead);
			printf("%lu", get_time() - general->start_time);
			printf("SALUT C VA\n");
			break ;
		}
		pthread_mutex_unlock(&general->safe_full);
		usleep(50);
	}
	return (NULL);
}

void	sleep_if_dead(t_general *general, int duration)
{
	long	debut;

	debut = get_time();
	// (void)general;
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
	// if (get_time() - debut >= duration)
	// 	return ;
	// else
	// 	usleep(duration - get_time());
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

	time_to_think = general->time_to_die - general->time_to_eat
		- general->time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	safe_print(philo, general, "is thinking");
	return (time_to_think - 100);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	t_general	*general;

	philo = (t_philo *)arg;
	general = (t_general *)philo->general;
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
		{
			pthread_mutex_unlock(&general->safe_dead);
			break ;
		}
		pthread_mutex_unlock(&general->safe_dead);
		fork_and_print(philo, general);
		// Commence a manger
		safe_print(philo, general, "is eating");
		sleep_if_dead(general, general->time_to_eat);
		pthread_mutex_lock(&philo->happy_meal);
		philo->nb_meals++;
		philo->last_meal = get_time();
		if (philo->nb_meals == general->max_meal)
		{
			philo->full = true;
			general->all_full++;
			pthread_mutex_unlock(philo->fork_l);
			pthread_mutex_unlock(philo->fork_r);
			while(general->all_full != general->number_of_philo)
			usleep(50);
			/* if (general->all_full == general->number_of_philo)
			{
				pthread_mutex_lock(&general->safe_dead);
				general->dead = 1;
				pthread_mutex_unlock(&general->safe_dead);
				break ;
				} */
			break ; 
		}
		pthread_mutex_unlock(&philo->happy_meal);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		pthread_mutex_lock(&general->safe_dead);
		if (general->dead)
		{
			pthread_mutex_unlock(&general->safe_dead);
			break ;
		}
		pthread_mutex_unlock(&general->safe_dead);
		safe_print(philo, general, "is sleeping");
		sleep_if_dead(general, general->time_to_sleep);
		pthread_mutex_lock(&general->safe_dead);
		if (general->dead)
		{
			pthread_mutex_unlock(&general->safe_dead);
			break ;
		}
		pthread_mutex_unlock(&general->safe_dead);
		sleep_if_dead(general, think(general, philo));
		// usleep(think(general, philo));
	}
	return (NULL);
}
void	*start_philo(t_general *general, int i)
{
	general->philo[i].philo_ID = i + 1;
	general->philo[i].general = general;
	general->philo[i].nb_meals = 0;
	general->philo[i].last_meal = general->start_time;
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
	pthread_create(&general.monitor, NULL, routine_monitor, &general);
	// usleep(5000);
	i = -1;
	while (++i < general.number_of_philo)
		pthread_join(general.philo[i].philo_thread, NULL);
	pthread_join(general.monitor, NULL);
	return (0);
}
