/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 02:34:05 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/20 20:34:36 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

# define EATING "is eating"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define TAKE_FORK "has taken a fork"
# define DIED "died"

typedef struct s_data	t_data;

typedef struct s_philo
{
	bool			is_full;
	long			last_eat;
	long			id;
	long			times_eat;
	pid_t			pid;
	t_data			*data;
	sem_t			*safe_philo;
	bool			ready;
	char			*name;
	pthread_t		monitor;
}	t_philo;

typedef struct s_data
{
	long			n_philo;
	long			t_2_die;
	long			t_2_eat;
	long			t_2_sleep;
	long			n_eat;
	long			stamp;
	sem_t			*safe_write;
	bool			wrt;
	sem_t			*forks;
	t_philo			*philos;
	bool			ready;
}	t_data;

typedef enum s_sem
{
	OPEN,
	POST,
	WAIT,
	CLOSE,
	UNLINK
}	t_sem;

void	parse_it(int ac, char **av, t_data *p);
void	innit_data(t_data *i);
long	get_msec(void);
sem_t	*get_sem(t_data *data, char *s, int innit);
int		out(int status, t_data *data, pid_t own);
void	ft_usleep(long msec);
void	custom_printf(char *s, t_data *data, int id);
void	simulation_engine(t_data *data);
void	*monitor_philos(void *dt);
int		ft_strlen(char *s);
void	wait_childs(t_data *data);
void	null_it(t_data *data);
void	kill_childs(t_data *data, pid_t own);

#endif