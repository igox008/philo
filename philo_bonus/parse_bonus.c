/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:47:47 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/19 07:25:59 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	*get_sem(t_data *data, char *s, int innit)
{
	sem_t	*sem;

	sem = sem_open((const char *)s, O_CREAT, 0644, innit);
	if (sem == SEM_FAILED)
		out(2, data, -1);
	return (sem);
}

bool	is_all_spaces(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (false);
	while (s[i])
	{
		if (s[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

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
		if (i > 0 && !(str[i] >= '0' && str[i] <= '9')
			&& !is_all_spaces(str + i))
			exit(1);
		else if (!(str[i] >= '0' && str[i] <= '9')
			&& str[i] != '+')
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
		if (p->n_philo < 0 || p->t_2_die < 60 || p->t_2_eat < 60
			|| p->t_2_sleep < 60)
			exit(2);
		if (ac == 5)
			p->n_eat = -1;
		else if (p->n_eat < 0)
			exit(2);
	}
	else
		exit(1);
}
