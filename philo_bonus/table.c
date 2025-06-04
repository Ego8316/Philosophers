/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:46:00 by ego               #+#    #+#             */
/*   Updated: 2025/06/04 14:27:24 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Allocates and initializes an array of philosopher structures given
 * the table configuration.
 * 
 * For each philosopher, allocates and initializes its structure with the
 * appropriate ID, pointer to the table and personal unique semaphore name.
 * 
 * If any allocation fails, cleans up any allocated memory and returns NULL.
 * 
 * @param Pointer to the table.
 * 
 * @return Allocated and initialized array of philosophers, NULL if memory
 * allocation fails.
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
		get_last_meal_sem_name(philos[i]->last_meal_sem_name, i + 1);
		printf("philosopher %i\t%s\n", philos[i]->id, philos[i]->last_meal_sem_name);
	}
	return (philos);
}

/**
 * @brief Parses input and allocates the main simulation table.
 * 
 * Allocates memory for the simulation table and initializes all required
 * philosophers and global semaphores. If any allocation or initialization
 * fails, previously allocated resources are properly freed. Also prints the
 * appropriate error message.
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
