/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_routine_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:17:23 by parthur-          #+#    #+#             */
/*   Updated: 2024/09/05 23:17:43 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*format_string(const char *s, const char *s1, \
	const char *s2, const char *s3)
{
	int		lenght;
	int		index;
	char	*formatted_string;

	lenght = (ft_strlen(s) + ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3));
	formatted_string = malloc((lenght + 1) * sizeof(char));
	formatted_string[lenght] = '\0';
	lenght = 0;
	index = 0;
	while (s[index])
		formatted_string[lenght++] = s[index++];
	index = 0;
	while (s1[index])
		formatted_string[lenght++] = s1[index++];
	index = 0;
	while (s2[index])
		formatted_string[lenght++] = s2[index++];
	index = 0;
	while (s3[index])
		formatted_string[lenght++] = s3[index++];
	return (formatted_string);
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
	fork_messages(philo, FIRSTFORK);
}

void	hold_the_second_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(&philo->philo_fork);
	fork_messages(philo, SECONDFORK);
}
