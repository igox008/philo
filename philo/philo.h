/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:24:06 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/20 20:34:20 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
	bool			ready;
}	t_fork;

typedef struct s_philo
{
	bool			is_full;
	long			last_eat;
	long			id;
	long			times_eat;
	pthread_t		philo;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_data			*data;
	pthread_mutex_t	safe_philo;
	bool			ready;
}	t_philo;

typedef struct s_data
{
	long			n_philo;
	long			t_2_die;
	long			t_2_eat;
	long			t_2_sleep;
	long			n_eat;
	long			stamp;
	pthread_mutex_t	safe_write;
	bool			wrt;
	pthread_mutex_t	safe_access;
	bool			acss;
	t_fork			*forks;
	t_philo			*philos;
	bool			all_philos_ready;
	bool			sim_finish;
	bool			ready;
	bool			free_it;
	pthread_t		monitor;
}	t_data;

typedef enum s_emtx
{
	INNIT,
	LOCK,
	UNLOCK,
	DESTROY
}	t_emtx;

typedef enum s_ephilo
{
	EATING,
	THINKING,
	SLEEPING,
	TAKE_FORK,
	DIED
}	t_ephilo;

void	parse_it(int ac, char **av, t_data *p, bool *innit);
void	innit_data(t_data *data, bool *innit);
long	get_msec(void);
void	ft_mutex(pthread_mutex_t *mtx, t_data *data, t_emtx call, bool *ready);
int		out(int status, t_data *data);
void	ft_usleep(long msec);
bool	get_bool(t_data *data, bool *access);
void	set_bool(t_data *data, bool *access, bool target);
long	get_long(t_data *data, long *access);
void	set_long(t_data *data, long *access, long target);
void	custom_printf(t_ephilo status, t_data *data, int id);
int		simulation_engine(t_data *data);
void	*monitor_philos(void *dt);
long	ft_atoi(char *str);

#endif