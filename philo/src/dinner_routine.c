/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:24:16 by parthur-          #+#    #+#             */
/*   Updated: 2024/08/30 20:24:16 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checking_simulation_philo(t_philo *philo)
{
	int	status;

	status = TRUE;
	pthread_mutex_lock(philo->dinner_validation);
	if (!philo->data->simulation_state)
		status = FALSE;
	if (philo->number_of_meals == philo->data->number_of_times_each_philosopher_must_eat)
		status = FALSE;
	pthread_mutex_unlock(philo->dinner_validation);
	return (status);
}

char	*get_action_time_str(t_philo *philo, char *time_now)
{
	struct timeval		tv;
	_Atomic long int	time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000000 + tv.tv_usec) - philo->start_time;
	time = time / 1000;
	time_now = ft_litoa(time);
	return (time_now);
}

long int	get_simulation_time(int type, long int first_time)
{
	struct timeval		tv;
	_Atomic long int	time;

	gettimeofday(&tv, NULL);
	if (type == MILLISECONDS)
		time = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - (first_time / 1000);
	if (type == MICROSECONDS)
		time = (tv.tv_sec * 1000000 + tv.tv_usec) - first_time;
	if (type == SECONDS)
		time = (tv.tv_sec + tv.tv_usec / 1000000) - (first_time / 1000000);
	return (time);
}

void	routine_messages(t_philo *philo, int type)
{
	char	*str_id;
	char	*msg;
	char	*time_now;

	str_id = ft_litoa(philo->id);
	time_now = NULL;
	time_now = get_action_time_str(philo, time_now);
	if (type == EATING && checking_simulation_philo(philo))
	{
		msg = format_string(time_now, " ", str_id, " IS EATING\n");
		ft_putstr_fd(msg, 1);
		usleep(philo->data->time_to_eat);
	}
	if (type == SLEEPING && checking_simulation_philo(philo))
	{
		msg = format_string(time_now, " ", str_id, " IS SLEEPING\n");
		ft_putstr_fd(msg, 1);
		usleep(philo->data->time_to_sleep);
	}
	if (type == THINKING && checking_simulation_philo(philo))
	{
		msg = format_string(time_now, " ", str_id, " IS THINKING\n");
		ft_putstr_fd(msg, 1);
		usleep(100);
	}
	if (type == FIRSTFORK && checking_simulation_philo(philo))
	{
		msg = format_string(time_now, " ", str_id, " PICKED UP THE FIRST FORK\n");
		ft_putstr_fd(msg, 1);
	}
	if (type == SECONDFORK && checking_simulation_philo(philo))
	{
		msg = format_string(time_now, " ", str_id, " PICKED UP THE SECOND FORK\n");
		ft_putstr_fd(msg, 1);
	}
	free(time_now);
	free(str_id);
}

void	hold_the_first_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->philo_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	routine_messages(philo, FIRSTFORK);
}

void	hold_the_second_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(&philo->philo_fork);
	routine_messages(philo, SECONDFORK);
}

int dinner_validation(t_philo *philo, int type)
{
	if (type == FIRST_VALIDATION && !checking_simulation_philo(philo))
	{
		if (philo->id % 2 == 0)
			pthread_mutex_unlock(&philo->philo_fork);
		else
			pthread_mutex_unlock(philo->right_fork);
		return (EXIT_FAILURE);
	}
	else if (type == SECOND_VALIDATION && !checking_simulation_philo(philo))
	{
		pthread_mutex_unlock(&philo->philo_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (EXIT_FAILURE);
	}
	else if (type == FINAL_VALIDATION && !checking_simulation_philo(philo))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	eating_function(t_philo *philo)
{
	philo->last_meal = get_simulation_time(MICROSECONDS, 0);
	routine_messages(philo, EATING);
}

void	dinner_manager(t_philo *philo)
{
	while (checking_simulation_philo(philo))
	{
		hold_the_first_fork(philo);
		if (dinner_validation(philo, FIRST_VALIDATION))
			break;
		hold_the_second_fork(philo);
		if (dinner_validation(philo, SECOND_VALIDATION))
			break;
		if (dinner_validation(philo, FINAL_VALIDATION))
			break;
		eating_function(philo);
		philo->number_of_meals++;
		pthread_mutex_unlock(&philo->philo_fork);
		pthread_mutex_unlock(philo->right_fork);
		routine_messages(philo, SLEEPING);
		routine_messages(philo, THINKING);
	}
}

void	*dinner_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	dinner_manager(philo);
	return (NULL);
}
