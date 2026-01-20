/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsierra <arsierra>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:25:01 by arsierra          #+#    #+#             */
/*   Updated: 2026/01/19 12:59:36 by arsierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_forks(t_data *data, int count)
{
	while (count > 0)
	{
		pthread_mutex_destroy(&data->forks[count - 1]);
		count--;
	}
	free(data->forks);
	data->forks = NULL;
}

static int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			destroy_forks(data, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		destroy_forks(data, data->num_philos);
		return (1);
	}
	if (pthread_mutex_init(&data->state_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		destroy_forks(data, data->num_philos);
		return (1);
	}
	return (0);
}

int	init_data(t_data *data)
{
	data->forks = NULL;
	data->philos = NULL;
	data->stop = 0;
	if (init_forks(data))
		return (1);
	if (init_mutexes(data))
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
	{
		pthread_mutex_destroy(&data->state_mutex);
		pthread_mutex_destroy(&data->print_mutex);
		destroy_forks(data, data->num_philos);
		return (1);
	}
	data->start_ms = get_timestamp_ms();
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].last_meal_ms = data->start_ms;
		data->philos[i].meals_eaten = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		i++;
	}
	return (0);
}
