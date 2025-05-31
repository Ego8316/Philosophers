/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:40:45 by ego               #+#    #+#             */
/*   Updated: 2025/05/31 22:13:44 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Retrieves the current time in milliseconds since the Unix Epoch.
 * 
 * @return The current timestamp in milliseconds.
 */
time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/**
 * @brief Custom sleep function that pauses execution for a precise number of
 * milliseconds using a busy wait loop with micro-sleeps.
 * 
 * Standard sleep functions like `usleep` can be imprecise, especially for
 * small durations, often oversleeping due to OS scheduling or process delays.
 * This function mitigates that by continously polling the actual time,
 * ensuring a more accurate sleep duration, which is needed for this project.
 * Also helps avoiding conversion errors.
 * 
 * @param wait_time Duration to sleep in milliseconds.
 */
void	ft_usleep(time_t wait_time)
{
	time_t	start;

	start = get_time_in_ms();
	while (get_time_in_ms() - start < wait_time)
		usleep(50);
	return ;
}

/**
 * @brief Busy-waits until the given start time is reached. Used to ensure all
 * threads are synchronized before actually starting the simulation.
 * 
 * @param start_time The exact timestamp in milliseconds to wait until.
 */
void	delay_start(time_t start_time)
{
	while (get_time_in_ms() < start_time)
		continue ;
	return ;
}
