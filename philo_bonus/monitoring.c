/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:02:05 by ego               #+#    #+#             */
/*   Updated: 2025/06/04 13:41:13 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Prints the current status of a philosopher with emoji and color.
 * 
 * Skips printing if the simulation has ended and the status is not `DECEASED`.
 * Ensures thread-safe printing by using a dedicated mutex.
 * 
 * @param philo Pointer to the philosopher whose status is to be printed.
 * @param status The current status to be displayed.
 */
void	print_status(t_philo *philo, t_status status)
{
	const char	*labels[5] = {
		"died ☠️",
		"has taken a fork 🍴",
		"is eating 🍝",
		"is sleeping 😴",
		"is thinking 🤔"
	};
	const char	*colors[5] = {
		COLOR_R,
		COLOR_A,
		COLOR_G,
		COLOR_V,
		COLOR_B
	};

	sem_wait(philo->table->print_sem);
	printf("%li\tPhilosopher %i %s%s%s\n",
		get_time_in_ms() - philo->table->start_time,
		philo->id, colors[status], labels[status], C_RESET);
	sem_post(philo->table->print_sem);
	return ;
}
