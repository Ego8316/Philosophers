/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:46:00 by ego               #+#    #+#             */
/*   Updated: 2025/05/29 21:40:36 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
