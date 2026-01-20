/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsierra <arsierra>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:25:01 by arsierra          #+#    #+#             */
/*   Updated: 2026/01/19 13:00:09 by arsierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_long(long *dst, char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result <= 0)
		return (1);
	*dst = result;
	return (0);
}

int	parse_args(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Uso: %s nb_philo time_die time_eat time_sleep [nb_meals]\n",
			argv[0]);
		return (1);
	}
	if (parse_long((long *)&data->num_philos, argv[1])
		|| parse_long(&data->time_to_die, argv[2])
		|| parse_long(&data->time_to_eat, argv[3])
		|| parse_long(&data->time_to_sleep, argv[4]))
	{
		printf("Argumentos no válidos\n");
		return (1);
	}
	data->meals_required = -1;
	if (argc == 6 && parse_long((long *)&data->meals_required, argv[5]))
	{
		printf("Argumentos no válidos\n");
		return (1);
	}
	return (0);
}
