/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:46:00 by ego               #+#    #+#             */
/*   Updated: 2025/05/29 21:22:31 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*get_forks(t_table *table)
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
	table->philos = (t_philo **)ft_calloc(table->n, sizeof(t_philo *));
	table->forks = get_forks(table);
	if (!table->philos || !table->forks)
		return (NULL);
	return (table);
}
