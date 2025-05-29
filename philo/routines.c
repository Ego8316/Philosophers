/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:19:39 by ego               #+#    #+#             */
/*   Updated: 2025/05/30 01:25:39 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*reaper_routine(void *d)
{
	t_table	*table;

	table = (t_table *)d;
	table->n = 0;
	return (NULL);
}

void	*philo_routine(void *d)
{
	t_philo	*philo;

	philo = (t_philo *)d;
	philo->id = 0;
	return (NULL);
}
