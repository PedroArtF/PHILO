/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine_massages.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:41:10 by marvin            #+#    #+#             */
/*   Updated: 2024/09/04 19:41:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	free(time_now);
	free(str_id);
}

void    fork_messages(t_philo *philo, int type)
{
    char	*str_id;
	char	*msg;
	char	*time_now;

	str_id = ft_litoa(philo->id);
	time_now = NULL;
	time_now = get_action_time_str(philo, time_now);
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