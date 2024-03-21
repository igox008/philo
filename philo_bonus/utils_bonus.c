/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:00:13 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/20 07:33:56 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	out(int status, t_data *data, pid_t own)
{
	int		i;
	t_philo	*philo;

	i = -1;
	if (status != 0)
	{
		kill_childs(data, own);
		while (++i < data->n_philo)
		{
			philo = &data->philos[i];
			if (philo->name != NULL)
			{
				sem_close(philo->safe_philo);
				sem_unlink(philo->name);
			}
			(free(philo->name), philo->name = NULL);
		}
		(sem_close(data->safe_write), sem_unlink("/safe_write"));
		(sem_close(data->forks), sem_unlink("/forks"));
	}
	free(data->philos);
	if (status >= 0)
		exit(status);
	return (1);
}

void	custom_printf(char *s, t_data *data, int id)
{
	sem_wait(data->safe_write);
	printf("%ld\t%d %s\n", get_msec() - data->stamp, id, s);
	if (s[0] != 'd')
		sem_post(data->safe_write);
}

void	wait_childs(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) != 0)
			break ;
		i++;
	}
	kill_childs(data, -2);
	if (WEXITSTATUS(status) == 0)
		out(-1, data, -1);
	exit(WEXITSTATUS(status));
}

void	kill_childs(t_data *data, pid_t own)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (own > 0 && data->philos[i].pid == own)
			;
		else if (data->philos[i].pid != -1)
		{
			kill(data->philos[i].pid, SIGINT);
			data->philos[i].pid = -1;
		}
	}
}
