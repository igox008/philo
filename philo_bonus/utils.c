/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:00:13 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/15 08:15:28 by alaassir         ###   ########.fr       */
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

int	out(int status, t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	kill_childs(data);
	while (++i < data->n_philo)
	{
		philo = &data->philos[i];
		ft_sem(philo->safe_philo, data, CLOSE, philo->name, 0);
		ft_sem(philo->safe_philo, data, UNLINK, philo->name, 0);
		(free(philo->name), philo->name = NULL);
	}
	ft_sem(data->safe_write, data, CLOSE, "/safe_write", 1);
	ft_sem(data->safe_access, data, CLOSE, "/safe_access", 1);
	ft_sem(data->forks, data, CLOSE, "/forks", data->n_philo);
	ft_sem(data->safe_write, data, UNLINK, "/safe_write", 1);
	ft_sem(data->safe_access, data, UNLINK, "/safe_access", 1);
	ft_sem(data->forks, data, UNLINK, "/forks", data->n_philo);
	(free(data->philos), exit(status));
	return (1);
}

void	custom_printf(t_ephilo status, t_data *data, int id)
{
	long		t;

	ft_sem(data->safe_write, data, WAIT, NULL, 0);
	t = get_msec() - data->stamp;
	if (status == TAKE_FORK)
		printf("%ld\t%d has taken a fork\n", t, id);
	else if (status == EATING)
		printf("%ld\t%d is eating\n", t, id);
	else if (status == SLEEPING)
		printf("%ld\t%d is sleeping\n", t, id);
	else if (status == THINKING)
		printf("%ld\t%d is thinking\n", t, id);
	else if (status == DIED)
		printf("%ld\t%d died\n", t, id);
	ft_sem(data->safe_write, data, POST, NULL, 0);
}

void	wait_childs(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	(void)data;
	while (i < data->n_philo)
	{
		waitpid(data->philos[i].pid, &status, 0);
		// exit(0);
		// printf("test\n");
		i++;
	}
	kill(0, SIGINT);
}

void	kill_childs(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (data->philos[i].pid != -1)
			kill(data->philos[i].pid, SIGINT);
	}
}
