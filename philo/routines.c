/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:19:39 by ego               #+#    #+#             */
/*   Updated: 2025/05/30 18:45:47 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*reaper_routine(void *d)
{
	t_table	*table;

	table = (t_table *)d;
	delay_start(table->start_time);
	while (1)
	{
		if (should_simulation_stop(table))
		{
			pthread_mutex_lock(&table->sim_running_lock);
			table->sim_running = 0;
			pthread_mutex_unlock(&table->sim_running_lock);
			return (NULL);
		}
		ft_usleep(1);
	}
	return (NULL);
}

/**
 * @brief Philosopher's routine for eating and sleeping.
 * 
 * @brief 1 - Pick up their forks (left and right) using mutexes.
 * @brief 2 - Print their actions to the console (taking forks, eating, and
 * sleeping).
 * @brief 3 - Update their last meal timestamp and increment their counter.
 * @brief 4 - Sleep for the configured amount of time after eating.
 * 
 * Fork acquisition follows the philosopher's assigned left and right fork
 * indices. Locks are released right after eating. The meal count is only
 * updated if the simulation is still running.
 * 
 * @param p Pointer to the philosopher.
 * 
 * @return Always returns NULL.
 * 
 * @note This function should be called within a thread created for a
 * philosopher.
 */
void	*eat_sleep_routine(t_philo *p)
{
	pthread_mutex_lock(&p->table->forks[p->left_fork]);
	print_status(p, FORK);
	pthread_mutex_lock(&p->table->forks[p->right_fork]);
	print_status(p, FORK);
	print_status(p, EATING);
	pthread_mutex_lock(&p->last_meal_lock);
	p->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&p->last_meal_lock);
	ft_usleep(p->table->time_to_eat);
	pthread_mutex_unlock(&p->table->forks[p->left_fork]);
	pthread_mutex_unlock(&p->table->forks[p->right_fork]);
	if (is_simulation_running(p->table))
	{
		pthread_mutex_lock(&p->meals_lock);
		p->meals_eaten++;
		pthread_mutex_unlock(&p->meals_lock);
	}
	print_status(p, SLEEPING);
	ft_usleep(p->table->time_to_sleep);
	return (NULL);
}

/**
 * @brief Main routine executed by each philosopher thread.
 * 
 * This function defines the behavior of a philosopher throughout the
 * simulation. It performs the following steps:
 * @brief 1 - Initializes the philosopher's `last_meal_time` to the table's
 * start time.
 * @brief 2 - Waits until the synchronized simulation start time using
 * `delay_start`.
 * @brief 3 - Continuously loops through eating, sleeping and thinking as long
 * as the simulation is running.
 * 
 * The loop condition is controlled by the shared simulation running flag,
 * which is mutex-protected.
 * 
 * @param d A void pointer to the philosopher structure.
 * 
 * @return Always returns NULL.
 */
void	*philo_routine(void *d)
{
	t_philo	*philo;

	philo = (t_philo *)d;
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal_time = philo->table->start_time;
	pthread_mutex_unlock(&philo->last_meal_lock);
	delay_start(philo->table->start_time);
	while (is_simulation_running(philo->table))
	{
		eat_sleep_routine(philo);
		if (is_simulation_running(philo->table))
		{
			print_status(philo, THINKING);
			ft_usleep(50);
		}
	}
	return (NULL);
}
