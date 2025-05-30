/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:40:07 by ego               #+#    #+#             */
/*   Updated: 2025/05/30 14:20:41 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(t_philo *p)
{
	printf("----- Philo %i -----\n", p->id);
	printf("left fork:\t%i\nright fork:\t%i\n", p->left_fork, p->right_fork);
	printf("meals:\t\t%i\nlast:\t\t%li\n", p->meals_eaten, p->last_meal_time);
	printf("-------------------\n");

}

void	print_table(t_table *t, int p)
{
	int	i;

	printf("Number of philosophers:\t%i\n", t->n);
	printf("Time to die:\t\t%li\n", t->time_to_die);
	printf("Time to eat:\t\t%li\n", t->time_to_eat);
	printf("Time to sleep:\t\t%li\n", t->time_to_sleep);
	printf("Minimal lunches:\t%i\n", t->meals_required);
	printf("Start time:\t%li\n", t->start_time);
	i = -1;
	while (p && ++i < t->n)
		print_philo(t->philos[i]);
}

/**
 * @brief Starts the simulation.
 * 
 * @param table Pointer to the table structure.
 * 
 * @return 1 if successful, 0 otherwise.
 */
int	start_simulation(t_table *table)
{
	int	i;

	table->start_time = get_time_in_ms() + 10 * table->n;
	i = -1;
	while (++i < table->n)
	{
		if (pthread_create(&table->philos[i]->thread, 0, &philo_routine,
			table->philos[i]) != 0)
			return (errmsg_null(THREAD_ERR), join_philos(table->philos, i));
	}
	if (table->n > 1
		&& pthread_create(&table->reaper, 0, &reaper_routine, table) != 0)
		return (errmsg_null(THREAD_ERR), join_philos(table->philos, i));
	return (1);
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
	print_table(table, 0);
	table->start_time = get_time_in_ms();
	table->sim_running = 1;
	for (int i = 0; i < 5; i++)
	{
		print_status(table->philos[2], i);
		ft_usleep(100);
	}
	free_table(table);
	return (0);
}
