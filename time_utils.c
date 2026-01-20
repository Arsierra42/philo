/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsierra <arsierra>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:26:09 by arsierra          #+#    #+#             */
/*   Updated: 2026/01/19 12:59:46 by arsierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_timestamp_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

long	get_elapsed_ms(long start_ms)
{
	long	now;

	now = get_timestamp_ms();
	if (now == 0)
		return (0);
	return (now - start_ms);
}

void	ms_sleep(long ms)
{
	long	start;

	start = get_timestamp_ms();
	while (get_elapsed_ms(start) < ms)
	{
		usleep(100);
	}
}
