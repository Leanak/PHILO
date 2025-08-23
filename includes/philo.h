/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:10:16 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/23 17:29:25 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"


typedef struct s_philo
{
	pthread_t 		philo_thread;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	int				philo_ID;
}	t_philo;


typedef struct	s_general
{
	int	time_to_eat;
	int	time_to_die;
	int	time_to_sleep;
	int	time_to_think;
	int	number_of_philo;
	t_philo	philo[200];
	pthread_mutex_t	fork[200];
}	t_general;

//int	ft_atoi(char *str);

#endif