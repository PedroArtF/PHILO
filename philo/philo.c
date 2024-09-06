/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:25:37 by parthur-          #+#    #+#             */
/*   Updated: 2024/09/05 22:25:37 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_dinner_manager		*manager;

	if (args_validation(argc, argv))
		return (EXIT_FAILURE);
	manager = initializing_manager(argv);
	if (!manager)
		return (EXIT_FAILURE);
	start_simulation(manager);
	return (EXIT_SUCCESS);
}
