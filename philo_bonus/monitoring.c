/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:02:05 by ego               #+#    #+#             */
/*   Updated: 2025/06/04 19:54:41 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Monitor routine that waits for all philosophers to finish eating.
 * 
 * Runs as a dedicated thread in the main process. It blocks on the `meals_sem`
 * semaphore `n` times - once per philosopher - effectively waiting until all
 * philosophers have reached their required meal count. Once done, posts
 * `death_sem` `n` timesto allow child processes to exit gracefully.
 * 
 * @param d A void pointer to the table structure.
 * 
 * @return Always returns NULL.
 */
void	*watchdog_routine(void *d)
{
	t_table	*table;
	int		i;

	table = (t_table *)d;
	delay_start(table->start_time);
	i = -1;
	while (++i < table->n)
		sem_wait(table->meals_sem);
	while (i--)
		sem_post(table->death_sem);
	return (NULL);
}

/**
 * @brief Per-philosopher monitoring thread that detects death by starvation.
 * 
 * Runs inside each philosopher process as a dedicated thread. Repeatedly
 * checks whether the philosopher has exceeded the `time_to_die` threshold
 * since their last meal. Access to `last_meal_time` is synchronized via
 * `last_meal_sem`. If starvation is detected, prints a death message and
 * broadcasts to all children using `death_sem` to end the simulation.
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
	int		i;

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
			i = -1;
			while (++i < p->table->n)
				sem_post(p->table->death_sem);
		}
		ft_usleep(1);
	}
	return (NULL);
}

/**
 * @brief Exit observer thread for each philosopher.
 * 
 * Runs in each philosopher process and waits on the shared `death_sem`. When
 * signaled, it performs cleanup and exits the process gracefully.
 * 
 * @param d A void pointer to the philosopher structure.
 * @return Always returns NULL.
 */
void	*observer_routine(void *d)
{
	t_philo	*p;

	p = (t_philo *)d;
	delay_start(p->table->start_time);
	sem_wait(p->table->death_sem);
	clean_exit_child(p, 0);
	return (NULL);
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

	sem_wait(philo->table->print_sem);
	printf("%li\tPhilosopher %i %s%s%s\n",
		get_time_in_ms() - philo->table->start_time,
		philo->id, colors[status], labels[status], C_RESET);
	fflush(stdout);
	if (status != DECEASED)
		sem_post(philo->table->print_sem);
	return ;
}
