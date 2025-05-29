/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:46:00 by ego               #+#    #+#             */
/*   Updated: 2025/05/29 22:18:14 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Initializes the mutexes required by the table structure.
 * 
 * Initializes the mutexes used for printing (`print_lock`) and controlling
 * simulation state (`sim_running_lock`). If either initialization fails,
 * previously initialized mutexes are destroyed to avoid leaks.
 * 
 * @param t Pointer to the table structure.
 * 
 * @return 1 on success, 0 on failure.
 */
static int	initiate_table_mutexes(t_table *t)
{
	if (pthread_mutex_init(&t->print_lock, 0) != 0)
		return (0);
	if (pthread_mutex_init(&t->sim_running_lock, 0) != 0)
	{
		pthread_mutex_destroy(&t->print_lock);
		return (0);
	}
	return (1);
}

/**
 * @brief Initializes all mutexes inside each philosopher. If any initalization
 * fails, already initialized mutexes are destroyed.
 * 
 * @param p Array of philosopher structures.
 * @param n Number of philosophers.
 * 
 * @return 1 on success, 0 on failure.
 */
static int	initiate_philo_mutexes(t_philo **p, int n)
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

/**
 * @brief Allocates and initializes all fork mutexes for philosophers.
 * 
 * Allocates and initializes one mutex per fork. If any mutex initialization
 * fails, all previously initialized mutexes are destroyed and memory is freed.
 * 
 * @param table Pointer to the table containing the number of philosophers.
 * 
 * @return Array of initialized mutexes, NULL on failure.
 */
static pthread_mutex_t	*get_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)ft_calloc(table->n, sizeof(pthread_mutex_t));
	if (!forks)
		return (errmsg_null(MALLOC_ERR));
	i = -1;
	while (++i < table->n)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
		{
			destroy_mutexes(forks, i);
			free(forks);
			return (errmsg_null(MUTEX_ERR));
		}
	}
	return (forks);
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
	if (!initiate_table_mutexes(table))
		return (free(table), errmsg_null(MUTEX_ERR));
	table->n = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->meals_required = -1;
	if (ac == 6)
		table->meals_required = ft_atoi(av[5]);
	table->philos = get_philos(table);
	table->forks = get_forks(table);
	if (!table->philos || !table->forks)
		return (free_table(table));
	return (table);
}
