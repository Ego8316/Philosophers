/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:40:07 by ego               #+#    #+#             */
/*   Updated: 2025/06/05 19:24:40 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Waits for a specific process to terminate and returns its exit code.
 * 
 * @param pid PID of the child process to wait for.
 * 
 * @return Exit code of the process.
 */
int	wait_and_get_exit_code(pid_t pid)
{
	int		status;
	pid_t	wpid;

	while (1)
	{
		wpid = waitpid(pid, &status, 0);
		if (wpid == -1)
			continue ;
		break ;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

/**
 * @brief Launches the philosopher simulation.
 * 
 * Sets up the simulation by forking `n` philosopher processes. Starts
 * `reaper_routine` to monitor for death. If multiple philosophers and a meal
 * requirement are present, also launches `watchdog_routine`.
 * 
 * @param table Pointer to the table structure.
 * 
 * @return 1 on success, 0 on any failure (e.g. fork or thread error).
 */
int	start_simulation(t_table *table)
{
	int	i;

	table->start_time = get_time_in_ms() + 50 * table->n;
	table->sim_running = 1;
	i = -1;
	while (++i < table->n)
	{
		table->philos[i]->pid = fork();
		if (table->philos[i]->pid == -1)
			return (errmsg_null(FORK_ERR), kill_philos(table->philos, i));
		if (table->philos[i]->pid == 0)
			philosopher(table->philos[i]);
	}
	if (pthread_create(&table->reaper, 0, &reaper_routine, table) != 0)
		return (errmsg_null(THREAD_ERR), kill_philos(table->philos, i));
	if (table->n > 1 && table->meals_required > 0
		&& pthread_create(&table->watchdog, 0, &watchdog_routine, table) != 0)
	{
		pthread_join(table->reaper, 0);
		return (errmsg_null(THREAD_ERR), kill_philos(table->philos, i));
	}
	return (1);
}

/**
 * @brief Collects exit statuses of all philosopher processes. 
 * 
 * Waits on each philosopher process. If any philosopher exits early while
 * simulation is still marked as running, forcefully ends the simulation.
 * 
 * @param table Pointer to the simulation table.
 * 
 * @return 1 if the early exit was detected and handled, 0 otherwise.
 */
int	end_simulation(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n)
	{
		wait_and_get_exit_code(table->philos[i]->pid);
		sem_wait(table->sim_running_sem);
		if (table->sim_running == 1)
		{
			kill_philos(table->philos, table->n);
			table->sim_running = 0;
			sem_post(table->death_sem);
			if (table->n > 1 && table->meals_required > 0)
				sem_post(table->sim_running_sem);
			return (1);
		}
		sem_post(table->sim_running_sem);
	}
	return (0);
}

/**
 * @brief Entry point of the philosopher simulation.
 * 
 * Validates user input, initializes the simulation table, and starts the
 * simulation. Waits for all created child processes, wait for all created
 * threads before freeing resources.
 * 
 * @param ac Argument count.
 * @param av Argument vector.
 * 
 * @return 0 on successful execution, 1 if any error occurs.
 */
int	main(int ac, char **av)
{
	t_table	*table;
	int		status;

	if (ac < 5 || ac > 6)
		return (put_help_message(ac));
	if (!is_valid_input(ac, av))
		return (errmsg("Invalid user input.\n", 0, 0, 1));
	table = get_table(ac, av);
	if (!table)
		return (errmsg("Error building the table\n", 0, 0, 1));
	if (!start_simulation(table))
		return (errmsg("Error starting the simulation\n", 0, 0, 1));
	status = end_simulation(table);
	if (table->n > 1 && table->meals_required > 0)
		pthread_join(table->watchdog, NULL);
	pthread_join(table->reaper, NULL);
	free_table(table);
	return (status);
}
