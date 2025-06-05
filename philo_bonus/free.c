/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:14:14 by ego               #+#    #+#             */
/*   Updated: 2025/06/05 19:11:20 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Sends `SIGKILL`to up to `size` philosophers.
 * 
 * Iterates over the given array of philosopher pointers and forcefully
 * terminates each associated process.
 * 
 * @param philos Array of philosophers.
 * @param size Size of the array.
 * 
 * @return Always returns 0 for convenience.
 */
int	kill_philos(t_philo **philos, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		kill(philos[i]->pid, SIGKILL);
	return (0);
}

/**
 * @brief Frees up to `size` elements of an array of pointers.
 * 
 * @param arr Array of pointers to be freed.
 * @param size Size of the array.
 * 
 * @return Always returns NULL for convenience.
 */
void	*free_array(void **arr, int size)
{
	int	i;

	i = -1;
	while (arr && ++i < size)
		free(arr[i]);
	if (arr)
		free(arr);
	return (NULL);
}

/**
 * @brief Frees all there is to free in the table structure. Also closes all
 * opened semaphores and unlinks them.
 * 
 * @param t Pointer to the table structure.
 * 
 * @return Always returns NULL for convenience.
 */
void	*free_table(t_table *t)
{
	int	i;

	if (t)
	{
		if (t->philos)
		{
			i = -1;
			while (++i < t->n)
				sem_unlink(t->philos[i]->last_meal_sem_name);
			free_array((void **)t->philos, t->n);
		}
		if (t->forks_sem != SEM_FAILED)
			sem_close(t->forks_sem);
		if (t->print_sem != SEM_FAILED)
			sem_close(t->print_sem);
		if (t->death_sem != SEM_FAILED)
			sem_close(t->death_sem);
		if (t->sim_running_sem != SEM_FAILED)
			sem_close(t->sim_running_sem);
		if (t->meals_required > 0 && t->meals_sem != SEM_FAILED)
			sem_close(t->meals_sem);
		unlink_global_semaphores();
		free(t);
	}
	return (NULL);
}

/**
 * @brief Closes the local semaphore and unlinks it, then frees the table
 * structure and exits with provided exit code.
 * 
 * @param p Pointer to the philosopher.
 * @param status Exit code.
 */
void	clean_exit_child(t_philo *p, int status)
{
	if (p->last_meal_sem != SEM_FAILED)
		sem_close(p->last_meal_sem);
	sem_unlink(p->last_meal_sem_name);
	free_table(p->table);
	exit(status);
}
