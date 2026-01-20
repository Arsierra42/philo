/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsierra <arsierra>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:25:43 by arsierra          #+#    #+#             */
/*   Updated: 2026/01/19 13:00:03 by arsierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_fed(t_data *data)
{
	int	i;

	if (data->meals_required <= 0)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].meals_eaten < data->meals_required)
			return (0);
		i++;
	}
	return (1);
}

static int	check_finish(t_data *data)
{
	if (!data->stop && all_fed(data))
	{
		data->stop = 1;
		return (1);
	}
	return (0);
}

static int	check_death(t_data *data)
{
	int		i;
	long	now;
	long	diff;

	now = get_timestamp_ms();
	i = 0;
	while (i < data->num_philos)
	{
		diff = now - data->philos[i].last_meal_ms;
		if (!data->stop && diff > data->time_to_die)
		{
			data->stop = 1;
			pthread_mutex_unlock(&data->state_mutex);
			pthread_mutex_lock(&data->print_mutex);
			printf("%ld %d died\n",
				get_elapsed_ms(data->start_ms),
				data->philos[i].id);
			pthread_mutex_unlock(&data->print_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->state_mutex);
		if (check_finish(data) || check_death(data))
			break ;
		pthread_mutex_unlock(&data->state_mutex);
		usleep(1000);
	}
	return (pthread_mutex_unlock(&data->state_mutex), NULL);
}
