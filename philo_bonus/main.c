/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:40:07 by ego               #+#    #+#             */
/*   Updated: 2025/06/04 15:20:13 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Launches the philosopher simulation.
 * 
 * Initializes the simulation's start time with a delay to allow threads to be
 * perfectly synchronized, sets its flag as running and creates a thread for
 * each philosopher. If there is more than one philosopher, also creates a
 * thread for the reaper to monitor their states. If any thread creation
 * fails, joins all previously created ones.
 * 
 * @param table Pointer to the table structure.
 * 
 * @return 1 if all threads are successfully created, 0 otherwise.
 */
int	start_simulation(t_table *table)
{
	int	i;

	table->sim_running = 1;
	table->start_time = get_time_in_ms() + 50 * table->n;
	i = -1;
	while (++i < table->n)
	{
		table->philos[i]->pid = fork();
		if (table->philos[i]->pid == -1)
			return (errmsg_null(FORK_ERR), kill_philos(table->philos, i));
		if (table->philos[i]->pid == 0)
			philo_routine(table);
	}
	waitpid(-1, 0, 0);
	kill(-1, SIGKILL);
	// if (table->n > 1
	// 	&& pthread_create(&table->reaper, 0, &reaper_routine, table) != 0)
	// 	return (errmsg_null(THREAD_ERR), kill_philos(table->philos, i));
	return (1);
}

/**
 * @brief Entry point of the philosopher simulation.
 * 
 * Validates user input, initializes the simulation table, and starts the
 * simulation. Joins all created threads before freeing resources.
 * 
 * @param ac Argument count.
 * @param av Argument vector.
 * 
 * @return 0 on successful execution, 1 if any error occurs.
 */
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
	start_simulation(table);
	// if (!start_simulation(table))
	// {
	// 	free_table(table);
	// 	return (errmsg("Error starting the simulation\n", 0, 0, 1));
	// }
	// if (table->n > 1)
	// 	pthread_join(table->reaper, 0);
	free_table(table);
	return (0);
}
