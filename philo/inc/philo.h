/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:18:42 by marvin            #+#    #+#             */
/*   Updated: 2024/07/22 10:18:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

enum e_act_philos
{
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING
};


typedef struct s_philo_data
{
	_Atomic long int	number_of_philosophers;
	_Atomic long int	time_to_die;
	_Atomic long int	time_to_eat;
	_Atomic long int	time_to_sleep;
	_Atomic long int	number_of_times_each_philosopher_must_eat;
}	t_philo_data;

typedef struct s_philo
{
	t_philo_data		*data;
	pthread_t			philosopher;
	int					id;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		philo_fork;
	_Atomic long int	last_meal;
}	t_philo;

//arg validation
int				args_validation(int argc, char **argv);

//initializing functions
t_philo_data	*initializing_philo_data(char **argv);
t_philo			*initializing_philo(char **argv);

//aux functions
long int		ft_atoli(const char *nptr);
int				ft_isdigit(char c);
void			ft_putstr_fd(const char *string, int fd);
int				ft_strlen(const char *string);

//simulation functions

void			start_simulation(t_philo *philo);

//dinner routine

void	*dinner_routine(void *arg);

#endif
