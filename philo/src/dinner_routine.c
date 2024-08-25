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
		usleep(philo->data->time_to_eat);
	}
	if (type == SLEEPING)
	{
		msg = format_string(time_now, " ", str_id, " IS SLEEPING\n");
		ft_putstr_fd(msg, 1);
		usleep(philo->data->time_to_sleep);
	}
	if (type == THINKING)
	{
		msg = format_string(time_now, " ", str_id, " IS THINKING\n");
		ft_putstr_fd(msg, 1);
	}
	if (type == FIRSTFORK)
	{
		msg = format_string(time_now, " ", str_id, " PICKED UP THE FIRST FORK\n");
		ft_putstr_fd(msg, 1);
	}
	if (type == SECONDFORK)
	{
		msg = format_string(time_now, " ", str_id, " PICKED UP THE SECOND FORK\n");
		ft_putstr_fd(msg, 1);
	}
}

int dinner_validation(t_philo *philo)
{
	_Atomic long int	time_without_eating;

	time_without_eating = get_simulation_time(MICROSECONDS, philo->last_meal);
	//printf("philo %d last meal = %ld time without eating = %ld time to die %ld\n", philo->id, philo->last_meal, time_without_eating, (philo->data->time_to_die * 1000));
	if (time_without_eating > (philo->data->time_to_die * 1000))
	{
		//printf("philo last meal = %ld time without eating = %ld time to die %ld\n", philo->last_meal, time_without_eating, (philo->data->time_to_die * 1000));
		pthread_mutex_lock(&philo->dinner_validation);
		philo->data->simulation_state = FALSE;
		pthread_mutex_unlock(&philo->dinner_validation);
		printf("\nPHILO %d IS DIED\n\n", philo->id);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	eating_function(t_philo *philo)
{
	routine_messages(philo, EATING);
	philo->last_meal = 	get_simulation_time(MICROSECONDS, 0);
}

int	dinner_manager(t_philo *philo)
{
	hold_the_first_fork(philo);
	routine_messages(philo, FIRSTFORK);
	//printf("1 - philo id = %d time now = %ld\n", philo->id, (philo->last_meal - philo->start_time));
	if (dinner_validation(philo))
	{
		if (philo->id % 2 == 0)
			pthread_mutex_unlock(&philo->philo_fork);
		else
			pthread_mutex_unlock(philo->right_fork);
		return (EXIT_FAILURE);
	}
	hold_the_second_fork(philo);
	routine_messages(philo, SECONDFORK);
	//printf("2 - philo id = %d time now = %ld\n", philo->id, (philo->last_meal - philo->start_time));
	if (dinner_validation(philo))
	{
		pthread_mutex_unlock(&philo->philo_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (EXIT_FAILURE);
	}
	eating_function(philo);
	pthread_mutex_unlock(&philo->philo_fork);
	pthread_mutex_unlock(philo->right_fork);
	routine_messages(philo, SLEEPING);
	routine_messages(philo, THINKING);
	return (EXIT_SUCCESS);
}

void	*dinner_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	dinner_manager(philo);
	return (NULL);
}
