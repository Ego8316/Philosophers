/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:40:07 by ego               #+#    #+#             */
/*   Updated: 2025/05/29 14:59:33 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_table(t_table *t)
{
	printf("Number of philosophers:\t%i\n", t->philo_number);
	printf("Time to die:\t\t%i\n", t->time_to_die);
	printf("Time to eat:\t\t%i\n", t->time_to_eat);
	printf("Time to sleep:\t\t%i\n", t->time_to_sleep);
	printf("Minimal lunches:\t%i\n", t->min_lunches);
}

int	main(int ac, char **av)
{
	t_table	*table;

	if (ac < 5 || ac > 6)
		return (put_help_message(ac));
	if (!is_valid_input(ac, av))
		return (errmsg("Invalid user input.\n", 0, 0, 1));
	table = get_table(ac, av);
	if (!table)
		return (errmsg("malloc: failed allocation\n", 0, 0, 1));
	print_table(table);
	free_table(table);
	return (0);
}
