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
	if (philo->number_of_meals == \
			philo->data->number_of_times_each_philosopher_must_eat)
		status = FALSE;
	pthread_mutex_unlock(philo->dinner_validation);
	return (status);
}

int	dinner_validation(t_philo *philo, int type)
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

int	just_one_on_the_table(t_philo *philo)
{
	if (philo->data->number_of_philosophers == 1)
	{
		hold_the_second_fork(philo);
		while (checking_simulation_philo(philo))
			continue ;
		pthread_mutex_unlock(&philo->philo_fork);
		return (TRUE);
	}
	else
		return (FALSE);
}

void	dinner_manager(t_philo *philo)
{
	if (!just_one_on_the_table(philo))
	{
		while (checking_simulation_philo(philo))
		{
			hold_the_first_fork(philo);
			if (dinner_validation(philo, FIRST_VALIDATION))
				break ;
			hold_the_second_fork(philo);
			if (dinner_validation(philo, SECOND_VALIDATION))
				break ;
			if (dinner_validation(philo, FINAL_VALIDATION))
				break ;
			philo->last_meal = get_simulation_time(MICROSECONDS, 0);
			routine_messages(philo, EATING);
			philo->number_of_meals++;
			pthread_mutex_unlock(&philo->philo_fork);
			pthread_mutex_unlock(philo->right_fork);
			routine_messages(philo, SLEEPING);
			routine_messages(philo, THINKING);
		}
	}
}

void	*dinner_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	dinner_manager(philo);
	return (NULL);
}
