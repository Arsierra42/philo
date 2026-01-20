/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsierra <arsierra>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:25:15 by arsierra          #+#    #+#             */
/*   Updated: 2026/01/19 12:59:55 by arsierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_and_free(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->state_mutex);
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}

static int	start_threads(t_data *data, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine,
				&data->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(monitor, NULL, &monitor_routine, data) != 0)
		return (1);
	return (0);
}

static void	join_threads(t_data *data, pthread_t monitor)
{
	int	i;

	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor;

	data.forks = NULL;
	data.philos = NULL;
	if (parse_args(&data, argc, argv))
		return (1);
	if (init_data(&data) || init_philosophers(&data))
		return (printf("Error al inicializar\n"), destroy_and_free(&data), 1);
	if (start_threads(&data, &monitor))
		return (printf("Error al crear hilos\n"), destroy_and_free(&data), 1);
	join_threads(&data, monitor);
	destroy_and_free(&data);
	return (0);
}
