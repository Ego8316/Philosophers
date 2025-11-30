/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:02:05 by ego               #+#    #+#             */
/*   Updated: 2025/06/05 19:41:17 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Checks whether the simulation is still marked as running.
 *
 * Reads the `sim_running` flag in a thread-safe way using its semaphore.
 *
 * @param t Pointer to the table structure.
 *
 * @return 1 if the simulation is still running, 0 otherwise.
 */
int	is_simulation_running(t_table *t)
{
	int	running;

	sem_wait(t->sim_running_sem);
	running = t->sim_running;
	sem_post(t->sim_running_sem);
	return (running);
}

/**
 * @brief Per-philosopher monitoring thread that detects death by starvation.
 * 
 * Runs inside each philosopher process as a dedicated thread. Repeatedly
 * checks whether the philosopher has exceeded the `time_to_die` threshold
 * since their last meal. Access to `last_meal_time` is synchronized via
 * `last_meal_sem`. If starvation is detected, prints a death message and
 * posts `death_sem` to end the simulation.
 * 
 * This loop runs with a very short sleep to ensure timely detection.
 * 
 * @param d A void pointer to the philosopher structure.
 * 
 * @return Always returns NULL.
 */
void	*hunger_routine(void *d)
{
	t_philo	*p;
	time_t	last_meal_time;

	p = (t_philo *)d;
	delay_start(p->table->start_time);
	while (1)
	{
		sem_wait(p->last_meal_sem);
		last_meal_time = p->last_meal_time;
		sem_post(p->last_meal_sem);
		if (get_time_in_ms() - last_meal_time > p->table->time_to_die)
		{
			print_status(p, DECEASED);
			sem_post(p->table->death_sem);
			break ;
		}
		ft_usleep(1);
	}
	return (NULL);
}

/**
 * @brief Monitor routine that waits for all philosophers to finish eating.
 *
 * Runs as a dedicated thread in the main process. It blocks on the `meals_sem`
 * semaphore `n` times - once per philosopher - effectively waiting until all
 * philosophers have reached their required meal count. If the simulation is
 * still running when all are full, kills all philosophers and exits.
 *
 * @param d A void pointer to the table structure.
 *
 * @return Always returns NULL.
 */
void	*watchdog_routine(void *d)
{
	t_table	*table;

	table = (t_table *)d;
	delay_start(table->start_time);
	while (table->full_philos < table->n)
	{
		sem_wait(table->meals_sem);
		sem_wait(table->sim_running_sem);
		if (table->sim_running == 1)
			table->full_philos++;
		else
			table->full_philos = table->n;
		sem_post(table->sim_running_sem);
	}
	sem_wait(table->sim_running_sem);
	if (table->sim_running == 0)
	{
		sem_post(table->sim_running_sem);
		return (NULL);
	}
	kill_philos(table->philos, table->n);
	table->sim_running = 0;
	sem_post(table->death_sem);
	sem_post(table->sim_running_sem);
	return (NULL);
}

/**
 * @brief Monitor routine that waits for the first philosopher death.
 *
 * Runs in the main process and waits on the shared `death_sem`. When signaled
 * and if the simulation is still running, kills all the child processes and
 * sets `sim_running` to 0.
 *
 * @param d A void pointer to the table structure.
 * @return Always returns NULL.
 */
void	*reaper_routine(void *d)
{
	t_table	*table;

	table = (t_table *)d;
	delay_start(table->start_time);
	if (!is_simulation_running(table))
		return (NULL);
	sem_wait(table->death_sem);
	sem_wait(table->sim_running_sem);
	kill_philos(table->philos, table->n);
	table->sim_running = 0;
	if (table->meals_required > 0)
		sem_post(table->meals_sem);
	sem_post(table->sim_running_sem);
	return (NULL);
}

/**
 * @brief Prints the current status of a philosopher with emoji and color.
 * 
 * Ensures that only one message prints at a time using `print_sem`. If the
 * simulation has ended, suppresses further printing (except death).
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
	if (status != DECEASED)
		sem_post(philo->table->print_sem);
	return ;
}
