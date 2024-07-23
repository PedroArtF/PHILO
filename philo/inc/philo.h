/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:18:42 by marvin            #+#    #+#             */
/*   Updated: 2024/07/22 10:18:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PILHO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo_data
{
    int                 number_of_philosophers;
    _Atomic long int    time_to_die;
    _Atomic long int    time_to_eat;
    _Atomic long int    time_to_sleep;
    int                 number_of_times_each_philosopher_must_eat;
}   t_philo_data;

typedef struct s_philo
{
    t_philo_data        *data;
    pthread_t           philo;
    int                 id;
    pthread_mutex_t     *right_fork;
    pthread_mutex_t     philo_fork;
    _Atomic long int    last_meal;
}   t_philo;

t_philo_data    initializing_philo_data(char **argv)
t_philo    initializing_philo(t_philo_data *data)

#endif