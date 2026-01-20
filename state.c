/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsierra <arsierra>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:26:02 by arsierra          #+#    #+#             */
/*   Updated: 2026/01/19 13:00:20 by arsierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_stopped(t_philo *philo)
{
	int	stopped;

	pthread_mutex_lock(&philo->data->state_mutex);
	stopped = philo->data->stop;
	pthread_mutex_unlock(&philo->data->state_mutex);
	return (stopped);
}

void	print_state(t_philo *philo, const char *msg)
{
	long	elapsed;

	if (simulation_stopped(philo))
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	elapsed = get_elapsed_ms(philo->data->start_ms);
	printf("%ld %d %s\n", elapsed, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
