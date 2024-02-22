/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:47:47 by alaassir          #+#    #+#             */
/*   Updated: 2024/02/22 13:43:25 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_arg(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (*str && *str == ' ')
		str++;
	if (!str[i])
		exit(1);
	while (str[i])
	{
		if (i > 0 && !(str[i] >= '0' && str[i] <= '9'))
			exit(1);
		else if (!(str[i] >= '0' && str[i] <= '9')
			&& str[i] != '+' && str[i] != '-')
			exit(1);
		if (str[i] >= '0' && str[i] <= '9')
			c++;
		i++;
	}
	if (!c)
		exit(1);
}

void	get_res(char *s, t_data *p)
{
	static int	i;

	if (!i)
		p->n_philo = atoi(s);
	else if (i == 1)
		p->t_2_die = atoi(s);
	else if (i == 2)
		p->t_2_eat = atoi(s);
	else if (i == 3)
		p->t_2_sleep = atoi(s);
	else if (i == 4)
		p->n_eat = atoi(s);
	i++;
}

void	parse_it(int ac, char **av, t_data *p)
{
	int	i;

	i = 1;
	if (ac == 5 || ac == 6)
	{
		while (i < ac)
		{
			check_arg(av[i]);
			get_res(av[i], p);
			i++;
		}
	}
	else
		exit(1);
}

void	innit_data(t_data *i)
{
	int	n;

	i = 0;
	i->philos = (t_philo *)malloc(sizeof(t_philo) * i->n_philo);
	if (!i->philos)
		exit(2);
	i->forks = (t_fork *)malloc(sizeof(t_fork) * i->n_philo);
	if (!i->forks)
		(free(i->philos), exit(2));
	i->time = get_time;
	while (n < i->n_philo)
	{
		i->philos[n].id = i + 1;
		i->philos[n].last_eat = i->time();
		i->philos[n].info = i;
		i->philos[n].n_eat = 0;
		i->philos[n].is_finish = false;
		n++;
	}
}
