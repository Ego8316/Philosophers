/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:40:07 by ego               #+#    #+#             */
/*   Updated: 2025/05/29 21:37:29 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_table(t_table *t)
{
	printf("Number of philosophers:\t%i\n", t->n);
	printf("Time to die:\t\t%li\n", t->time_to_die);
	printf("Time to eat:\t\t%li\n", t->time_to_eat);
	printf("Time to sleep:\t\t%li\n", t->time_to_sleep);
	printf("Minimal lunches:\t%i\n", t->meals_required);
	printf("Start time:\t%li\n", t->start_time);
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
		return (errmsg("Error building the table\n", 0, 0, 1));
	print_table(table);
	free_table(table);
	return (0);
}
