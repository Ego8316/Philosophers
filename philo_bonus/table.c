/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:46:00 by ego               #+#    #+#             */
/*   Updated: 2025/06/04 13:24:09 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Initializes semaphores.
 */
static int	get_semaphores(t_table *t)
{

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
static t_philo	**get_philos(t_table *table)
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
			return (free_array((void **)philos, i), errmsg_null(MALLOC_ERR));
		philos[i]->id = i + 1;
		philos[i]->table = table;
	}
	return (philos);
}

/**
 * @brief Parses input and allocates the main simulation table.
 * 
 * Allocates memory for the simulation table and initializes all required
 * mutexes, philosophers and fork mutexes. If any allocation or mutex
 * initialization fails, previously allocated resources are properly freed.
 * Also prints the appropriate error message.
 * 
 * @param ac Argument count.
 * @param av Argument vector.
 * 
 * @return The fully initialized table structure, NULL on failure.
 */
t_table	*get_table(int ac, char **av)
{
	t_table	*table;

	table = (t_table *)ft_calloc(1, sizeof(t_table));
	if (!table)
		return (errmsg_null(MALLOC_ERR));
	table->n = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->meals_required = -1;
	if (ac == 6)
		table->meals_required = ft_atoi(av[5]);
	table->philos = get_philos(table);
	if (!table->philos || !init_global_semaphores(table))
		return (free_table(table));
	return (table);
}
