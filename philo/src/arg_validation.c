/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:23:57 by parthur-          #+#    #+#             */
/*   Updated: 2024/08/30 20:23:57 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	arg_error_msg(int status)
{
	if (status == 1)
		ft_putstr_fd("ERROR\nphilosophers: invalid \
				number of arguments\n", STDERR_FILENO);
	else if (status == 2)
		ft_putstr_fd("ERROR\nphilosophers: only numerical \
					arguments are accepted\n", STDERR_FILENO);
}

static int	is_the_amount_of_args_correct(int argc)
{
	if (argc > 6 || argc < 5)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

static int	are_the_args_only_digits(char **argv)
{
	int	index_m;
	int	index_s;

	index_m = 1;
	index_s = 0;
	while (argv[index_m])
	{
		while (argv[index_m][index_s])
		{
			if (!ft_isdigit(argv[index_m][index_s]))
				return (EXIT_FAILURE);
			index_s++;
		}
		index_s = 0;
		index_m++;
	}
	return (EXIT_SUCCESS);
}

int	args_validation(int argc, char **argv)
{
	if (is_the_amount_of_args_correct(argc))
	{
		arg_error_msg(1);
		return (EXIT_FAILURE);
	}
	else if (are_the_args_only_digits(argv))
	{
		arg_error_msg(2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
