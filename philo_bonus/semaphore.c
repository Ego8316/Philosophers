/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:06:38 by ego               #+#    #+#             */
/*   Updated: 2025/06/05 19:39:33 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Unlinks all global semaphores.
 * 
 * Removes named semaphores from the system, ensuring no stale semaphores
 * remain from previous runs.
 */
void	unlink_global_semaphores(void)
{
	sem_unlink(FORKS_SEM_NAME);
	sem_unlink(PRINT_SEM_NAME);
	sem_unlink(DEATH_SEM_NAME);
	sem_unlink(MEALS_SEM_NAME);
	sem_unlink(SIM_SEM_NAME);
}

/**
 * @brief Initializes the global semaphores shared across all philosophers.
 * 
 * Unlinks any existing named semaphores before creating new ones.
 * Opens semaphores for forks, printing synchronization, simulation state,
 * philosopher meals tracking, and death detection.
 * 
 * @param t Pointer to the simulation table structure.
 * 
 * @return Returns 1 on successful semaphore initialization, 0 on failure.
 * 
 * @note Should be called before creating philosopher processes.
 */
int	init_global_semaphores(t_table *t)
{
	unlink_global_semaphores();
	t->forks_sem = sem_open(FORKS_SEM_NAME, O_CREAT | O_EXCL, 0644, t->n);
	t->print_sem = sem_open(PRINT_SEM_NAME, O_CREAT | O_EXCL, 0644, 1);
	t->death_sem = sem_open(DEATH_SEM_NAME, O_CREAT | O_EXCL, 0644, 0);
	t->sim_running_sem = sem_open(SIM_SEM_NAME, O_CREAT | O_EXCL, 0644, 1);
	if (t->meals_required > 0)
		t->meals_sem = sem_open(MEALS_SEM_NAME, O_CREAT | O_EXCL, 0644, 0);
	if (t->forks_sem == SEM_FAILED || t->print_sem == SEM_FAILED
		|| t->sim_running_sem == SEM_FAILED
		|| (t->meals_required > 0 && t->meals_sem == SEM_FAILED))
		return (errmsg_null(SEM_OPEN_ERR), 0);
	return (1);
}

/**
 * @brief Constructs a unique semaphore name for each philosopher's semaphore.
 * 
 * Copies the fixed prefix and appends the philosopher's ID as a 3-digit
 * zero-padded number.
 * 
 * @param sem_name The destination buffer.
 * @param prefix Semaphore prefix.
 * @param id Philosopher's ID.
 * 
 * @warning Assumes `sem_name` is pre-allocated with at least
 * `BUFFER_SIZE` bytes.
 */
void	get_unique_sem_name(char *sem_name, char *prefix, int id)
{
	int		i;

	i = ft_strlcpy(sem_name, prefix, BUFFER_SIZE - 4);
	sem_name[i++] = '0' + id / 100;
	sem_name[i++] = '0' + id / 10 % 10;
	sem_name[i++] = '0' + id % 10;
	sem_name[i] = 0;
}

/**
 * @brief Initializes a local semaphore for each philosopher.
 * 
 * Unlinks any existing semaphore with the same name to ensure a clean slate
 * and then creates a new semaphore associated with the given philosopher.
 * This semaphore is used to mutex-protect the philosopher's last meal time.
 * 
 * If the semaphore fails to open, prints the appropriate error message.
 * 
 * @param p Pointer to the philosopher structure containing the semaphore name.
 * 
 * @return 1 on success, 0 on failure.
 */
int	init_local_semaphore(t_philo *p)
{
	sem_unlink(p->last_meal_sem_name);
	p->last_meal_sem = sem_open(p->last_meal_sem_name, O_CREAT, 0644, 1);
	if (p->last_meal_sem == SEM_FAILED)
		return (errmsg_null(SEM_OPEN_ERR), 0);
	return (1);
}
