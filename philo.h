/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsierra <arsierra>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:25:53 by arsierra          #+#    #+#             */
/*   Updated: 2026/01/19 12:53:16 by arsierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			last_meal_ms;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

struct s_data
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_ms;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
	int				stop;
	int				meals_required;
	t_philo			*philos;
};

/* time_utils.c */
long	get_timestamp_ms(void);
long	get_elapsed_ms(long start_ms);
void	ms_sleep(long ms);

/* init.c */
int		parse_args(t_data *data, int argc, char **argv);
int		init_data(t_data *data);
int		init_philosophers(t_data *data);

/* routine.c */
void	*philo_routine(void *arg);

/* monitor.c */
void	*monitor_routine(void *arg);

int		simulation_stopped(t_philo *philo);
void	print_state(t_philo *philo, const char *msg);

#endif