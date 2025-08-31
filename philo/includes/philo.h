/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 11:44:32 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/31 19:38:31 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// Libraries
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// Structures
typedef struct s_philo
{
	pthread_t			philo_thread;
	pthread_mutex_t		*fork_r;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		safe_meal;
	bool				check_fork;
	bool				full;
	long				last_meal;
	int					nb_meals;
	int					philo_id;
	struct s_general	*general;
}						t_philo;

typedef struct s_general
{
	int					error;
	int					time_to_eat;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_think;
	int					number_of_philo;
	int					max_meal;
	int					dead;
	int					all_full;
	long				start_time;
	t_philo				philo[200];
	pthread_t			monitor;
	pthread_mutex_t		safe_dead;
	pthread_mutex_t		safe_full;
	pthread_mutex_t		fork[200];
	pthread_mutex_t		safe_print;
}						t_general;

void					*routine(void *arg);
void					fork_and_print(t_philo *philo, t_general *general);
void					safe_print(t_philo *philo, t_general *general,
							char *message);
void					check_time_passing(t_general *general, int duration);
bool					one_philo(t_general *general, t_philo *philo);
bool					check_if_dead(t_general *general);
void					*routine_monitor(void *arg);
long					get_time(void);
bool					init_general(t_general *general, int ac, char **av);
void					init_fork(t_general *general, int i);

#endif