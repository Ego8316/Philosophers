/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:14:14 by ego               #+#    #+#             */
/*   Updated: 2025/06/04 14:37:53 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Destroys up to `size` mutexes of an array of mutexes.
 * 
 * @param m Array of mutexes to be destroyed.
 * @param size Size of the array.
 */
void	destroy_mutexes(pthread_mutex_t *m, int size)
{
	int	i;

	i = -1;
	while (m && ++i < size)
		pthread_mutex_destroy(&m[i]);
	return ;
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
 * @brief Frees up to `size` philo structures in an array of philosophers. Also
 * destroys all initiated mutexes.
 * 
 * @param p Array of philosophers.
 * @param size Size of the array.
 * 
 * @return Always returns NULL for convenience.
 */
void	*free_philos(t_philo **p, int size)
{
	int	i;

	i = -1;
	while (p && ++i < size)
	{
		pthread_mutex_destroy(&p[i]->last_meal_lock);
		pthread_mutex_destroy(&p[i]->meals_lock);
		free(p[i]);
	}
	if (p)
		free(p);
	return (NULL);
}

/**
 * @brief Joins up to `size` philosopher's threads of an array of philosophers.
 * 
 * @param p Array of philosophers.
 * @param size Size of the array.
 * 
 * @return Always returns 0 for convenience.
 */
int	join_philos(t_philo **p, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		pthread_join(p[i]->thread, 0);
	return (0);
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
			free_philos(t->philos, t->n);
		if (t->forks)
		{
			destroy_mutexes(t->forks, t->n);
			free(t->forks);
		}
		pthread_mutex_destroy(&t->print_lock);
		pthread_mutex_destroy(&t->sim_running_lock);
		free(t);
	}
	return (NULL);
}
