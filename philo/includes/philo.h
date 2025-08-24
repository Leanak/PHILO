/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:10:16 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/24 19:07:40 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/time.h>

struct	s_general;

typedef struct s_philo
{
	pthread_t 		philo_thread;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	happy_meal; 
	bool			check_fork;
	bool			full;
	long			last_meal;
	int				nb_meals;
	int				philo_ID;
	struct s_general	*general;	
}	t_philo;


typedef struct	s_general
{
	int	time_to_eat;
	int	error;
	int	time_to_die;
	int	time_to_sleep;
	int	time_to_think;
	int	number_of_philo;
	int	max_meal;
	int	dead;
	int	all_full;
	long	start_time;
	t_philo	philo[200];
	pthread_t	monitor;
	pthread_mutex_t	safe_dead;
	pthread_mutex_t	safe_full;
	pthread_mutex_t	fork[200];
	pthread_mutex_t	safe_print;
}	t_general;

long ft_atol(char *str, int *error);
bool	init_general(t_general *general, char **av, int ac);
void	init_fork(t_general *general, int i);
void	*test(void *arg);
long	get_time(void);


#endif