/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:19:39 by ego               #+#    #+#             */
/*   Updated: 2025/06/04 19:44:48 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	solitary_philosopher_routine(t_philo *p)
{
	printf("hey\n");
	delay_start(p->table->start_time);
	print_status(p, FORK);
	ft_usleep(p->table->time_to_die);
	print_status(p, DECEASED);
	clean_exit_child(p, 0);
}

/**
 * @brief Philosopher's routine for eating and sleeping.
 * 
 * @brief 1 - Pick up their forks (left and right) using `sem_wait`.
 * @brief 2 - Print their actions to the console (taking forks, eating, and
 * sleeping).
 * @brief 3 - Update their last meal timestamp and increment their counter.
 * @brief 4 - Sleep for the configured amount of time after eating.
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
	return (NULL);
}

/**
 * @brief Simulates the philosopher thinking for a calculated duration. The
 * thinking time is computed based on the time to die, the time since the last
 * meal and the time to eat. It is also capped to a maximum of 200ms and a
 * minimum of 0.
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
 * @param d A void pointer to the philosopher structure.
 * 
 * @return Always returns NULL.
 */
void	*philo_routine(t_philo *p)
{
	printf("ALLO %p\n", p->table);
	printf("yo %i\n", p->table->n);
	if (p->table->n == 1)
		solitary_philosopher_routine(p);
	if (!open_global_semaphores(p->table) || !init_local_semaphore(p)
		|| pthread_create(&p->hunger, 0, hunger_routine, p) != 0)
		clean_exit_child(p, 1);
	if (pthread_create(&p->watcher, 0, observer_routine, p))
		clean_exit_child(p, 1);
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
	pthread_join(p->hunger, 0);
	return (NULL);
}
