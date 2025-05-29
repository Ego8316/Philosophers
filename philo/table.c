/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:46:00 by ego               #+#    #+#             */
/*   Updated: 2025/05/29 20:07:09 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**get_philos(t_table *table)
{
	t_philo		**philos;
	int			i;

	philos = (t_philo **)ft_calloc(table->n_philos, sizeof(t_philo *));
	if (!philos)
		return (errmsg_null(MALLOC_ERROR));
	i = -1;
	while (++i < table->n_philos)
	{
		philos[i] = (t_philo *)ft_calloc(1, sizeof(t_philo));
		if (!philos[i])
			return (errmsg_null(MALLOC_ERROR));
		philos[i]->id = i;
		philos[i]->table = table;
		philos[i]->left_fork = i;
		philos[i]->right_fork = (i + 1) % table->n_philos;
		if (i % 2)
			swap_int(&philos[i]->left_fork, &philos[i]->right_fork);
	}
	return (philos);
}

pthread_mutex_t	*get_fork_locks(t_table *table)
{
	pthread_mutex_t	*f;
	int				i;

	f = (pthread_mutex_t *)ft_calloc(table->n_philos, sizeof(pthread_mutex_t));
	if (!f)
		return (errmsg_null(MALLOC_ERROR));
	i = -1;
	while (++i < table->n_philos)
	{
		if (pthread_mutex_init(&f[i], 0) != 0)
			return (errmsg_null(MUTEX_ERROR));
	}
	return (f);
}

t_table	*get_table(int ac, char **av)
{
	t_table	*table;

	table = (t_table *)ft_calloc(1, sizeof(t_table));
	if (!table)
		return (errmsg_null(MALLOC_ERROR));
	table->n_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->meals_required = -1;
	if (ac == 6)
		table->meals_required = ft_atoi(av[5]);
	table->philos = (t_philo **)ft_calloc(table->n_philos, sizeof(t_philo *));
	if (!table->philos)
		return (free_table(table));
	table->start_time = get_time_in_ms();
	return (table);
}

void	*free_table(t_table *t)
{
	if (t)
	{
		free(t);
		if (t->philos)
			free(t->philos);
		
	}
	return (NULL);
}
