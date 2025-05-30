/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:02:05 by ego               #+#    #+#             */
/*   Updated: 2025/05/30 14:16:31 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Checks if the simulation is still running.
 * 
 * @return 1 if it is running, 0 otherwise.
 */
int	is_simulation_running(t_table *table)
{
	int	ret;

	pthread_mutex_lock(&table->sim_running_lock);
	ret = table->sim_running;
	pthread_mutex_unlock(&table->sim_running_lock);
	return (ret);
}

void	print_status(t_philo *philo, t_status status)
{
	const char	*labels[5] = {
		"died",
		"has taken a fork",
		"is eating",
		"is thinking",
		"is sleeping"
	};
	const char	*colors[5] = {
		COLOR_R,
		COLOR_A,
		COLOR_G,
		COLOR_V,
		COLOR_B
	};

	if (!is_simulation_running(philo->table) && status != DECEASED)
		return ;
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%s%li\tPhilosopher %i %s%s\n", colors[status], get_time_in_ms()
		- philo->table->start_time, philo->id, labels[status], C_RESET);
	pthread_mutex_unlock(&philo->table->print_lock);
	return ;
}
