/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:51:00 by marvin            #+#    #+#             */
/*   Updated: 2024/07/22 10:51:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*get_action_time(t_philo *philo, char *time_now)
{
	struct	 timeval tv;
	_Atomic long int	time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - philo->start_time;
	time_now = ft_litoa(time);
	return (time_now);
}

void	hold_the_first_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->philo_fork);
	else
		pthread_mutex_lock(philo->right_fork);
}

void	hold_the_second_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(&philo->philo_fork);
}

void	routine_messages(t_philo *philo, int type)
{
	char	*str_id;
	char	*msg;
	char	*time_now;

	time_now = 0;
	str_id = ft_litoa(philo->id);
	time_now = get_action_time(philo, time_now);
	if (type == EATING)
	{
		msg = format_string(time_now, " ", str_id, " IS EATING\n");
		ft_putstr_fd(msg, 1);
	}
	if (type == SLEEPING)
	{
		msg = format_string(time_now, " ", str_id, " IS SLEEPING\n");
		ft_putstr_fd(msg, 1);
	}
	if (type == THINKING)
	{
		msg = format_string(time_now, " ", str_id, " IS THINKING\n");
		ft_putstr_fd(msg, 1);
	}
}

void	eating_function(t_philo *philo)
{
	routine_messages(philo, EATING);
	usleep(philo->data->time_to_eat);
}

void	sleeping_function(t_philo *philo)
{
	routine_messages(philo, SLEEPING);
	usleep(philo->data->time_to_sleep);
}

void	dinner_manager(t_philo *philo)
{
	hold_the_first_fork(philo);
	hold_the_second_fork(philo);
	eating_function(philo);
	pthread_mutex_unlock(&philo->philo_fork);
	pthread_mutex_unlock(philo->right_fork);
	sleeping_function(philo);
}

void	*dinner_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	dinner_manager(philo);
	return (NULL);
}
