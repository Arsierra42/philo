/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsierra <arsierra>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:26:02 by arsierra          #+#    #+#             */
/*   Updated: 2026/01/19 13:00:16 by arsierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
	}
}

static void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

static void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	while (!simulation_stopped(philo))
	{
		usleep(1000);
	}
	pthread_mutex_unlock(philo->left_fork);
}

static void	eat_cycle(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->data->state_mutex);
	philo->last_meal_ms = get_timestamp_ms();
	pthread_mutex_unlock(&philo->data->state_mutex);
	print_state(philo, "is eating");
	ms_sleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->state_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->state_mutex);
	drop_forks(philo);
	print_state(philo, "is sleeping");
	ms_sleep(philo->data->time_to_sleep);
	print_state(philo, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	if (philo->data->num_philos == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	while (!simulation_stopped(philo))
	{
		eat_cycle(philo);
	}
	return (NULL);
}
