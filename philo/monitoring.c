/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:02:05 by ego               #+#    #+#             */
/*   Updated: 2025/06/04 19:04:59 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Checks if the simulation should stop.
 * 
 * The simulation should stop if any philosopher has died (i.e. has not eaten
 * in time) or if all philosophers have eaten the required number of meals.
 * 
 * @param t Pointer to the table structure.
 * 
 * @return 1 if the simulation should stop, 0 otherwise.
 */
int	should_simulation_stop(t_table *t)
{
	int	i;
	int	max_meals_reached;

	i = -1;
	max_meals_reached = 1;
	while (++i < t->n)
	{
		pthread_mutex_lock(&t->philos[i]->last_meal_lock);
		if (get_time_in_ms() - t->philos[i]->last_meal_time > t->time_to_die)
		{
			print_status(t->philos[i], DECEASED);
			pthread_mutex_unlock(&t->philos[i]->last_meal_lock);
			return (1);
		}
		pthread_mutex_unlock(&t->philos[i]->last_meal_lock);
		pthread_mutex_lock(&t->philos[i]->meals_lock);
		if (t->philos[i]->meals_eaten < t->meals_required)
			max_meals_reached = 0;
		pthread_mutex_unlock(&t->philos[i]->meals_lock);
	}
	if (t->meals_required > -1 && max_meals_reached)
		return (1);
	return (0);
}

/**
 * @brief Thread-safe check to determine if the simulation is still running.
 * 
 * @param table Pointer to the table structure.
 * 
 * @return 1 if simulation is running, 0 otherwise.
 */
int	is_simulation_running(t_table *table)
{
	int	ret;

	pthread_mutex_lock(&table->sim_running_lock);
	ret = table->sim_running;
	pthread_mutex_unlock(&table->sim_running_lock);
	return (ret);
}

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

	if (!is_simulation_running(philo->table) && status != DECEASED)
		return ;
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%li\tPhilosopher %i %s%s%s\n",
		get_time_in_ms() - philo->table->start_time,
		philo->id, colors[status], labels[status], C_RESET);
	if (status != DECEASED)
		pthread_mutex_unlock(&philo->table->print_lock);
	return ;
}
