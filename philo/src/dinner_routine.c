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

char	*get_action_time_str(t_philo *philo, char *time_now)
{
	struct timeval		tv;
	_Atomic long int	time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - philo->start_time;
	philo->last_meal = time;
	time_now = ft_litoa(time);
	return (time_now);
}

long int	get_simulation_time(int type, long int first_time)
{
	struct timeval		tv;
	_Atomic long int	time;

	gettimeofday(&tv, NULL);
	if (type == MILLISECONDS)
		time = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - first_time;
	if (type == MICROSECONDS)
		time = (tv.tv_sec * 1000000 + tv.tv_usec) - (first_time * 1000);
	if (type == SECONDS)
		time = (tv.tv_sec + tv.tv_usec / 1000000) - (first_time / 1000);
	return (time);
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

	str_id = ft_litoa(philo->id);
	time_now = NULL;
	time_now = get_action_time_str(philo, time_now);
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

int dinner_validation(_Atomic long int time_now, t_philo *philo)
{
	_Atomic long int	time_without_eating;

	if (philo->last_meal > 0)
	{
		time_without_eating = time_now - philo->last_meal;
		if (time_without_eating < philo->data->time_to_die)
		{
			philo->data->simulation_state = FALSE;
			printf("\nPHILO %d IS DIED\n\n", philo->id);
			return (EXIT_FAILURE);
		}
		else
			return (EXIT_SUCCESS);
	}
	else
		return (EXIT_SUCCESS);
}

void	eating_function(t_philo *philo)
{
	_Atomic long int	time_now;

	routine_messages(philo, EATING);
	time_now = get_simulation_time(MILLISECONDS, 0);
	philo->last_meal = time_now;
	usleep(philo->data->time_to_eat);
}

void	sleeping_function(t_philo *philo)
{
	routine_messages(philo, SLEEPING);
	usleep(philo->data->time_to_sleep);
}

int	dinner_manager(t_philo *philo)
{
	_Atomic long int	time_now;

	hold_the_first_fork(philo);
	time_now = get_simulation_time(MILLISECONDS, philo->last_meal);
	if (dinner_validation(time_now, philo))
	{
		if (philo->id % 2 == 0)
			pthread_mutex_unlock(&philo->philo_fork);
		else
			pthread_mutex_unlock(philo->right_fork);
		return (EXIT_FAILURE);
	}
	hold_the_second_fork(philo);
	time_now = get_simulation_time(MILLISECONDS, philo->last_meal);
	if (dinner_validation(time_now, philo))
	{
		pthread_mutex_unlock(&philo->philo_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (EXIT_FAILURE);
	}
	eating_function(philo);
	pthread_mutex_unlock(&philo->philo_fork);
	pthread_mutex_unlock(philo->right_fork);
	sleeping_function(philo);
	return (EXIT_SUCCESS);
}

void	*dinner_routine(void *arg)
{
	t_philo	*philo;
	int		simulation_status;

	simulation_status = 0;
	philo = (t_philo *) arg;
	*philo->data->simulation_state = TRUE;
	simulation_status = dinner_manager(philo);
	if (simulation_status)
		philo->data->simulation_state = FALSE;
	return (NULL);
}
