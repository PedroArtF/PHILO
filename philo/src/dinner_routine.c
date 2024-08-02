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
	if (type == EATING)
    {
        ft_putstr_fd(ft_litoa(id), 1);
        ft_putstr_fd(" IS EATING\n", 1);
    }
    if (type == SLEEPING)
    {
        ft_putstr_fd(ft_litoa(id), 1);
        ft_putstr_fd(" IS SLEEPING\n", 1);
    }
    if (type == THINKING)
    {
        ft_putstr_fd(ft_litoa(id), 1);
        ft_putstr_fd(" IS THINKING\n", 1);
    }
}

void	eating_function(t_philo *philo)
{
    routine_messages(philo->id, EATING);
}

void	sleeping_function(t_philo *philo)
{
    routine_messages(philo->id, SLEEPING);
}


void	*dinner_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
    if (philo->id % 2 == 0)
    {
        usleep(1000000);
        sleeping_function(philo);
    }
    else
    {
        eating_function(philo);
    }
	return (NULL);
}