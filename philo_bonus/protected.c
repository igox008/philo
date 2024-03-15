/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 04:42:56 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/14 08:42:15 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sem(sem_t *sem, t_data *data, t_sem call,
		char *s, int innit)
{
	(void)data;
	if (call == OPEN)
	{
		sem = sem_open((const char *)s, O_CREAT, 0644, innit);
		if (sem == SEM_FAILED)
			;//LATER
	}
	else if (call == POST && sem_post(sem) != 0)
			;//LATER
	else if (call == WAIT && sem_wait(sem) != 0)
			;//LATER
	else if (call == CLOSE && sem_close(sem) != 0)
			;//LATER
	else if (call == UNLINK && sem_unlink((const char *)s) != 0)
			;//LATER
}

bool	get_bool(t_data *data, bool *access)
{
	bool	ret;

	ft_sem(data->safe_access, data, WAIT, NULL, 0);
	ret = *access;
	ft_sem(data->safe_access, data, POST, NULL, 0);
	return (ret);
}

void	set_bool(t_data *data, bool *access, bool target)
{
	ft_sem(data->safe_access, data, WAIT, NULL, 0);
	*access = target;
	ft_sem(data->safe_access, data, POST, NULL, 0);
}

long	get_long(t_data *data, long *access)
{
	long	ret;

	ft_sem(data->safe_access, data, WAIT, NULL, 0);
	ret = *access;
	ft_sem(data->safe_access, data, POST, NULL, 0);
	return (ret);
}

void	set_long(t_data *data, long *access, long target)
{
	ft_sem(data->safe_access, data, WAIT, NULL, 0);
	*access = target;
	ft_sem(data->safe_access, data, POST, NULL, 0);
}
