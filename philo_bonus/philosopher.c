/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:19:39 by ego               #+#    #+#             */
/*   Updated: 2025/06/05 19:38:11 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Special routine for a solitary philosopher.
 *
 * A single philosopher cannot eat as there is only one fork available. In that
 * grim scenario, the philosopher picks up the only fork and waits for its
 * tragic death. Posts `death_sem` on death to allow the reaper thread to exit.
 *
 * @param p Pointer to the lonely philosopher.
 */
static void	solitary_philosopher_routine(t_philo *p)
{
	delay_start(p->table->start_time);
	print_status(p, FORK);
	ft_usleep(p->table->time_to_die);
	print_status(p, DECEASED);
	sem_post(p->table->death_sem);
	clean_exit_child(p, 0);
}

/**
 * @brief Philosopher's routine for eating and sleeping.
 *
 * Steps:
 * 1. Wait on `forks_sem` twice to take both forks.
 * 2. Update `last_meal_time`, print status, and eat.
 * 3. Release forks and, if a meal quota exists and is reached, post to
 *    `meals_sem`.
 * 4. Print sleeping status and rest for the configured duration.
 *
 * @param p Pointer to the philosopher.
 */
static void	eat_sleep_routine(t_philo *p)
{
	sem_wait(p->table->forks_sem);
	print_status(p, FORK);
	sem_wait(p->table->forks_sem);
	print_status(p, FORK);
	sem_wait(p->last_meal_sem);
	p->last_meal_time = get_time_in_ms();
	sem_post(p->last_meal_sem);
	print_status(p, EATING);
	ft_usleep(p->table->time_to_eat);
	sem_post(p->table->forks_sem);
	sem_post(p->table->forks_sem);
	if (++p->meals_eaten == p->table->meals_required)
		sem_post(p->table->meals_sem);
	print_status(p, SLEEPING);
	ft_usleep(p->table->time_to_sleep);
}

/**
 * @brief Simulates the philosopher thinking for a calculated duration.
 *
 * The thinking time is derived from `time_to_die`, time since last meal, and
 * `time_to_eat`, capped between 0 and 200ms.
 *
 * @param p Pointer to the philosopher structure.
 */
static void	think_routine(t_philo *p)
{
	time_t	time_since_last_meal;
	time_t	time_to_think;

	print_status(p, THINKING);
	sem_wait(p->last_meal_sem);
	time_since_last_meal = get_time_in_ms() - p->last_meal_time;
	sem_post(p->last_meal_sem);
	time_to_think = (p->table->time_to_die
			- time_since_last_meal - p->table->time_to_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > 200)
		time_to_think = 200;
	ft_usleep(time_to_think);
}

/**
 * @brief Main philosopher routine executing the lifecycle loop.
 *
 * Initializes last meal time, synchronizes start, and runs an infinite loop
 * of eating, sleeping and thinking. Odd philosophers start by thinking to
 * reduce deadlock risk.
 *
 * @param p Pointer to the philosopher structure.
 */
static void	philo_routine(t_philo *p)
{
	sem_wait(p->last_meal_sem);
	p->last_meal_time = p->table->start_time;
	sem_post(p->last_meal_sem);
	delay_start(p->table->start_time);
	if (p->id % 2)
		think_routine(p);
	while (1)
	{
		eat_sleep_routine(p);
		think_routine(p);
	}
}

/**
 * @brief Entry point for each philosopher process.
 *
 * Handles single philosopher case, initializes semaphores, starts starvation
 * monitoring thread and runs the philosopher lifecycle. Cleans up and exits
 * gracefully on errors or completion.
 *
 * @param p Pointer to the philosopher structure.
 */
void	philosopher(t_philo *p)
{
	if (p->table->n == 1)
	{
		solitary_philosopher_routine(p);
		return ;
	}
	if (!init_local_semaphore(p)
		|| pthread_create(&p->hunger, 0, hunger_routine, p) != 0)
		clean_exit_child(p, 1);
	philo_routine(p);
	pthread_join(p->hunger, 0);
	clean_exit_child(p, 0);
}
