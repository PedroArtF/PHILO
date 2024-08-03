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

void	routine_messages(int id, int type)
{
    char    *str_id;
    char    *msg;

    str_id = ft_litoa(id);
	if (type == EATING)
    {
        msg = format_string(str_id, " IS EATING\n");
        ft_putstr_fd(msg, 1);
    }
    if (type == SLEEPING)
    {
        msg = format_string(str_id, " IS SLEEPING\n");
        ft_putstr_fd(msg, 1);
    }
    if (type == THINKING)
    {
        msg = format_string(str_id, " IS THINKING\n");
        ft_putstr_fd(msg, 1);
    }
}

void	eating_function(t_philo *philo)
{
    routine_messages(philo->id, EATING);
    usleep(philo->data->time_to_eat);
}

void	sleeping_function(t_philo *philo)
{
    routine_messages(philo->id, SLEEPING);
    usleep(philo->data->time_to_sleep);
}

void    dinner_manager(t_philo *philo)
{
    int number_of_meals;

    number_of_meals = 0;
    while (number_of_meals < philo->data->number_of_times_each_philosopher_must_eat)
    {
        if (number_of_meals % 2 != 0)
        {
            if (philo->id % 2 == 0)
                eating_function(philo);
            else
                sleeping_function(philo);   
        }
        else
        {
            if (philo->id % 2 != 0)
                eating_function(philo);
            else
                sleeping_function(philo); 
        }
        number_of_meals++;
    }
    
}

void	*dinner_routine(void *arg)
{
    t_philo	*philo;

	philo = (t_philo *) arg;
	dinner_manager(philo);
	return (NULL);
}