/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine_massages.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:25:59 by parthur-          #+#    #+#             */
/*   Updated: 2024/09/05 22:25:59 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(const char *string, int fd)
{
	if (!string)
		return ;
	write(fd, string, ft_strlen(string));
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

void	write_action_message(char *str_id, char *time_now, \
			int type, t_philo *philo)
{
	char	*msg;

	msg = NULL;
	if (type == EATING)
	{
		msg = format_string(time_now, " ", str_id, " IS EATING\n");
		ft_putstr_fd(msg, 1);
		free(msg);
		usleep(philo->data->time_to_eat);
	}
	else if (type == SLEEPING)
	{
		msg = format_string(time_now, " ", str_id, " IS SLEEPING\n");
		ft_putstr_fd(msg, 1);
		free(msg);
		usleep(philo->data->time_to_sleep);
	}
	else if (type == THINKING)
	{
		msg = format_string(time_now, " ", str_id, " IS THINKING\n");
		ft_putstr_fd(msg, 1);
		free(msg);
		usleep(100);
	}
}

void	routine_messages(t_philo *philo, int type)
{
	char	*str_id;
	char	*time_now;

	str_id = ft_litoa(philo->id);
	time_now = NULL;
	time_now = get_action_time_str(philo, time_now);
	if (type == EATING && checking_simulation_philo(philo))
		write_action_message(str_id, time_now, EATING, philo);
	else if (type == SLEEPING && checking_simulation_philo(philo))
		write_action_message(str_id, time_now, SLEEPING, philo);
	else if (type == THINKING && checking_simulation_philo(philo))
		write_action_message(str_id, time_now, THINKING, philo);
	free(time_now);
	free(str_id);
}

void	fork_messages(t_philo *philo, int type)
{
	char	*str_id;
	char	*msg;
	char	*time_now;

	str_id = ft_litoa(philo->id);
	time_now = NULL;
	time_now = get_action_time_str(philo, time_now);
	if (type == FIRSTFORK && checking_simulation_philo(philo))
	{
		msg = format_string(time_now, " ", str_id, " HAS TAKEN A FORK\n");
		ft_putstr_fd(msg, 1);
		free(msg);
	}
	if (type == SECONDFORK && checking_simulation_philo(philo))
	{
		msg = format_string(time_now, " ", str_id, " HAS TAKEN A FORK\n");
		ft_putstr_fd(msg, 1);
		free(msg);
	}
	free(time_now);
	free(str_id);
}
