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

enum e_validations
{
	FIRST_VALIDATION,
	SECOND_VALIDATION,
	FINAL_VALIDATION
};

enum e_times
{
	MICROSECONDS,
	MILLISECONDS,
	SECONDS
};

enum e_act_philos
{
	EATING,
	SLEEPING,
	THINKING,
	FIRSTFORK,
	SECONDFORK
};

typedef struct s_philo_data
{
	_Atomic long int	number_of_philosophers;
	_Atomic long int	time_to_die;
	_Atomic long int	time_to_eat;
	_Atomic long int	time_to_sleep;
	_Atomic long int	number_of_times_each_philosopher_must_eat;
	int					*simulation_state;
	//pthread_mutex_t		dinner_validation;
}	t_philo_data;

typedef struct s_philo
{
	t_philo_data		*data;
	pthread_t			philosopher;
	int					id;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		philo_fork;
	pthread_mutex_t		*dinner_validation;
	int					number_of_meals;
	_Atomic long int	last_meal;
	_Atomic long int	start_time;
}	t_philo;

typedef struct s_dinner_manager
{
	_Atomic long int	start;
	_Atomic long int	last_time;
	_Atomic long int	time_now;
	pthread_t			dinner_supervisor;
	pthread_mutex_t		dinner_validation;
	t_philo				*philos;
	t_philo_data		*data;
	int					simulation_state;
}	t_dinner_manager;

//arg validation
int					args_validation(int argc, char **argv);

//initializing functions
t_philo_data		*initializing_philo_data(char **argv);
t_philo				*initializing_philos(char **argv, t_dinner_manager *manager);
t_dinner_manager	*initializing_manager(char **argv);

//aux functions
long int			ft_atoli(const char *nptr);
int					ft_isdigit(char c);
void				ft_putstr_fd(const char *string, int fd);
int					ft_strlen(const char *string);
char				*ft_litoa(long int num);
char				*format_string(const char *s, const char *s1,
						const char *s2, const char *s3);
long int			get_simulation_time(int type, long int first_time);

//simulation functions

void				start_simulation(t_dinner_manager *manager);

//dinner routine

void				*dinner_routine(void *arg);

// monitoring functions

void				*dinner_monitoring(void *arg);

#endif
