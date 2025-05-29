/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:50:58 by ego               #+#    #+#             */
/*   Updated: 2025/05/29 21:22:01 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Initializes all mutexes inside each philosopher. If any initalization
 * fails, already initialized mutexes are destroyed.
 * 
 * @param p Array of philosopher structures.
 * @param n Number of philosophers.
 * 
 * @return 1 on success, 0 on failure.
 */
int	initiate_philo_mutexes(t_philo **p, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (pthread_mutex_init(&p[i]->last_meal_lock, 0) != 0)
			break ;
		if (pthread_mutex_init(&p[i]->meals_lock, 0) != 0)
		{
			pthread_mutex_destroy(&p[i]->last_meal_lock);
			break ;
		}
	}
	if (i == n)
		return (1);
	while (--i >= 0)
	{
		pthread_mutex_destroy(&p[i]->last_meal_lock);
		pthread_mutex_destroy(&p[i]->meals_lock);
	}
	return (0);
}

/**
 * @brief Allocates and initializes an array of philosopher structures given
 * the table configuration.
 * 
 * For each philosopher, allocates and initializes its structure with the
 * appropriate ID, pointer to the table, and assigned left and right forks. The
 * left and right forks are integers referring to indices in the shared forks
 * mutex array. Odd-numbered philosophers swap fork assignment to avoid
 * deadlock.
 * 
 * Once all philosophers are allocated, initializes their internal mutexes. If
 * any allocation or initialization fails, cleans up any allocated memory and
 * mutexes before returning NULL.
 * 
 * @param Pointer to the table.
 * 
 * @return Allocated and initialized array of philosophers, NULL if memory
 * allocation fails or mutex initialization fails.
 */
t_philo	**get_philos(t_table *table)
{
	t_philo		**philos;
	int			i;

	philos = (t_philo **)ft_calloc(table->n, sizeof(t_philo *));
	if (!philos)
		return (errmsg_null(MALLOC_ERR));
	i = -1;
	while (++i < table->n)
	{
		philos[i] = (t_philo *)ft_calloc(1, sizeof(t_philo));
		if (!philos[i])
			return (free_philos(philos, i), errmsg_null(MALLOC_ERR));
		philos[i]->id = i;
		philos[i]->table = table;
		philos[i]->left_fork = i;
		philos[i]->right_fork = (i + 1) % table->n;
		if (i % 2)
			swap_int(&philos[i]->left_fork, &philos[i]->right_fork);
	}
	if (!initiate_philo_mutexes(philos, table->n))
		return (free_array((void **)philos, table->n), errmsg_null(MUTEX_ERR));
	return (philos);
}
