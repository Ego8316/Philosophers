/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:14:14 by ego               #+#    #+#             */
/*   Updated: 2025/06/04 14:37:45 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Kills up to `size` philosophers of an array of philosophers.
 * 
 * @param philos Array of philosophers.
 * @param size Size of the array.
 * 
 * @return Always returns NULL for convenience.
 */
void	*kill_philos(t_philo **philos, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		kill(philos[i]->pid, SIGKILL);
	return (NULL);
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
 * @brief Frees all there is to free in the table structure. Also destroys all
 * initiated mutexes.
 * 
 * @param t Pointer to the table structure.
 * 
 * @return Always returns NULL for convenience.
 */
void	*free_table(t_table *t)
{
	if (t)
	{
		if (t->philos)
			free_array((void **)t->philos, t->n);
		if (t->forks_sem != SEM_FAILED)
			sem_close(t->forks_sem);
		if (t->print_sem != SEM_FAILED)
			sem_close(t->print_sem);
		if (t->meals_required > 0 && t->meals_sem != SEM_FAILED)
			sem_close(t->meals_sem);
		free(t);
	}
	return (NULL);
}
