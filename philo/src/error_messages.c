/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:44:00 by marvin            #+#    #+#             */
/*   Updated: 2024/09/04 10:44:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_msg_mutex(enum e_error type, int id)
{
	char	*str_id;
	char	*error_msg;
	char	*type_msg;

	str_id = ft_litoa(id);
	type_msg = "";
	if (type == EINVAL)
		type_msg = ": Invalid attribute attr or mutex already initialized.";
	else if (type == ENOMEM)
		type_msg = ": Not enough memory to create the mutex.";
	else if (type == EAGAIN)
		type_msg = ": Mutex limit reached.";
	else if (type == EPERM)
		type_msg = ": Process does not have permission to create the mutex.";
	error_msg = format_string("Mutex error, in thread ", "", str_id, type_msg);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	free(str_id);
	free(error_msg);
}

void	error_msg_thread_create(enum e_error type, int id)
{
	char	*str_id;
	char	*error_msg;
	char	*type_msg;

	str_id = ft_litoa(id);
	type_msg = "";
	if (type == EINVAL)
		type_msg = ": Invalid attr, start_routine, or arg.";
	else if (type == ENOMEM)
		type_msg = ": Insufficient memory.";
	else if (type == EAGAIN)
		type_msg = ": System resources or thread limit exceeded.";
	else if (type == EPERM)
		type_msg = ": Permission denied to set scheduling policy.";
	error_msg = format_string("Thread creation error in ", \
			"", str_id, type_msg);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	free(str_id);
	free(error_msg);
}

void	error_msg_thread_join(enum e_error type, int id)
{
	char	*str_id;
	char	*error_msg;
	char	*type_msg;

	str_id = ft_litoa(id);
	type_msg = "";
	if (type == EDEADLK)
		type_msg = ": Deadlock would occur if thread waits to terminate.";
	else if (type == EINVAL)
		type_msg = ": thread is not a joinable thread.";
	else if (type == ESRCH)
		type_msg = ": thread not found.";
	error_msg = format_string("Join error in ", "", str_id, type_msg);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	free(str_id);
	free(error_msg);
}

void	error_msg_mutex_destroy(enum e_error type)
{
	char	*error_msg;
	char	*type_msg;

	type_msg = "";
	if (type == EBUSY)
		type_msg = ": The mutex is currently locked by a thread.";
	else if (type == EINVAL)
		type_msg = ": The value specified by mutex \
			does not refer to a valid mutex.";
	error_msg = format_string("Mutex destroy error ", "", "", type_msg);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	free(error_msg);
}
