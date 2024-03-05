/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:47:47 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/04 00:06:34 by alaassir         ###   ########.fr       */
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
		out(1);
	while (str[i])
	{
		if (i > 0 && !(str[i] >= '0' && str[i] <= '9'))
			out(1);
		else if (!(str[i] >= '0' && str[i] <= '9')
			&& str[i] != '+' && str[i] != '-')
			out(1);
		if (str[i] >= '0' && str[i] <= '9')
			c++;
		i++;
	}
	if (!c)
		out(1);
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
		out(1);
}
