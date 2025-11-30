/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:19:39 by ego               #+#    #+#             */
/*   Updated: 2025/06/01 15:20:57 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Monitor routine that checks if the simulation should end.
 *
 * This function runs in a separate thread and continuously checks whether a
 * philosopher has died or all philosophers have eaten enough. If either
 * condition is met, sets the shared `sim_running` flag to 0 to terminate the
 * simulation.
 *
 * @param d A void pointer to the table structure.
 *
 * @return Always returns NULL.
 */
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
 * Steps:
 * 1. Lock left and right forks.
 * 2. Print fork and eating status, update last meal timestamp.
 * 3. Eat, release forks, and increment meal count if the simulation continues.
 * 4. Print sleeping status and rest for the configured duration.
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
static void	*eat_sleep_routine(t_philo *p)
{
	pthread_mutex_lock(&p->table->forks[p->left_fork]);
	print_status(p, FORK);
	pthread_mutex_lock(&p->table->forks[p->right_fork]);
	print_status(p, FORK);
	pthread_mutex_lock(&p->last_meal_lock);
	p->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&p->last_meal_lock);
	print_status(p, EATING);
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
 * @brief Simulates the philosopher thinking for a calculated duration.
 *
 * The thinking time is derived from `time_to_die`, time since last meal, and
 * `time_to_eat`, capped between 0 and 200ms.
 *
 * @param p Pointer to the philosopher structure.
 *
 * @return Always returns NULL.
 */
static void	*think_routine(t_philo *p)
{
	time_t	time_since_last_meal;
	time_t	time_to_think;

	print_status(p, THINKING);
	pthread_mutex_lock(&p->last_meal_lock);
	time_since_last_meal = get_time_in_ms() - p->last_meal_time;
	pthread_mutex_unlock(&p->last_meal_lock);
	time_to_think = (p->table->time_to_die
			- time_since_last_meal - p->table->time_to_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > 200)
		time_to_think = 200;
	ft_usleep(time_to_think);
	return (NULL);
}

/**
 * @brief Main routine executed by each philosopher thread.
 *
 * This function defines the behavior of a philosopher throughout the
 * simulation. It performs the following steps:
 * 1. Initialize `last_meal_time` to the table's start time.
 * 2. Wait for the synchronized start via `delay_start`.
 * 3. Loop through eating, sleeping, and thinking while the simulation runs.
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
	t_philo	*p;

	p = (t_philo *)d;
	pthread_mutex_lock(&p->last_meal_lock);
	p->last_meal_time = p->table->start_time;
	pthread_mutex_unlock(&p->last_meal_lock);
	delay_start(p->table->start_time);
	if (p->table->n == 1)
	{
		print_status(p, FORK);
		ft_usleep(p->table->time_to_die);
		print_status(p, DECEASED);
		return (NULL);
	}
	while (is_simulation_running(p->table))
	{
		eat_sleep_routine(p);
		think_routine(p);
	}
	return (NULL);
}
