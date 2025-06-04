/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:19:39 by ego               #+#    #+#             */
/*   Updated: 2025/06/04 21:09:29 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Special routine for a solitary philosopher.
 * 
 * A single philosopher cannot eat as there is only one fork available. In that
 * grim scenario, the philosopher picks up the only fork and waits for its
 * tragic death.
 * 
 * @param p Pointer to the lonely philosopher.
 * 
 * @note This function should be called within a thread created for a
 * philosopher.
 */
void	solitary_philosopher_routine(t_philo *p)
{
	delay_start(p->table->start_time);
	print_status(p, FORK);
	ft_usleep(p->table->time_to_die);
	print_status(p, DECEASED);
	clean_exit_child(p, 0);
}

/**
 * @brief Philosopher's routine for eating and sleeping.
 * 
 * @brief 1 - Waits on the `forks_sem` semaphore to pick up both forks.
 * @brief 2 - Updates `last_meal_time` and prints status message.
 * @brief 3 - Eats for the configured duration.
 * @brief 4 - Releases both forks.
 * @brief 5 - If meal limit is specified and reached, posts to `meals_sem`.
 * @brief 6 - Sleeps for the configured duration.
 * 
 * @param p Pointer to the philosopher.
 * 
 * @note This function should be called within a thread created for a
 * philosopher.
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
 * @brief Simulates the philosopher thinking for a calculated duration. The
 * thinking time is computed based on the time to die, the time since the last
 * meal and the time to eat. It is also capped to a maximum of 200ms and a
 * minimum of 0.
 * 
 * @param p Pointer to the philosopher structure.
 * 
 * @note This function should be called within a thread created for a
 * philosopher.
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
 * @brief Main routine executed by each philosopher process.
 * 
 * Defines the philosopher's lifecycle and sets up the required threads for
 * starvation monitoring and graceful exit handling.
 * 
 * @brief 1 - Handles the single philosopher edge case.
 * @brief 2 - Opens shared semaphores and initializes local ones.
 * @brief 3 - Starts the per-philosopher starvation detector and exit observer.
 * @brief 4 - Repeats the cycle eat -> sleep -> think.
 * 
 * Philosophers with odd IDs start by thinking to help prevent deadlock.
 * 
 * @param d A void pointer to the philosopher structure.
 * 
 * @return Always returns NULL.
 */
void	philosopher(t_philo *p)
{
	if (p->table->n == 1)
	{
		solitary_philosopher_routine(p);
		return ;
	}
	if (!open_global_semaphores(p->table) || !init_local_semaphore(p)
		|| pthread_create(&p->hunger, 0, hunger_routine, p) != 0)
		clean_exit_child(p, 1);
	if (pthread_create(&p->observer, 0, observer_routine, p) != 0)
	{
		pthread_join(p->hunger, 0);
		clean_exit_child(p, 1);
	}
	pthread_detach(p->hunger);
	pthread_detach(p->observer);
	philo_routine(p);
}
