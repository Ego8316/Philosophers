/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:14:21 by ego               #+#    #+#             */
/*   Updated: 2025/05/29 13:16:16 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Displays on the standard error a help message.
 * 
 * @return Always returns 1 for convenience.
 */
int	put_help_message(void)
{
	ft_putstr_fd("Invalid number of arguments.\n", STDERR_FILENO);
	ft_putstr_fd("Usage:\t./philo number_of_philosophers\n\t\t", STDERR_FILENO);
	ft_putstr_fd("time_to_die\n\t\ttime_to_eat", STDERR_FILENO);
	ft_putstr_fd("\n\t\ttime_to_sleep\n\t\t", STDERR_FILENO);
	ft_putstr_fd("[number_of_times_each_philosopher_must_eat]", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}

/**
 * @brief Displays on the standard error three strings
 * and returns the given status.
 * 
 * @param s1 First string to be printed.
 * @param s2 Second string to be printed.
 * @param s3 Third string to be printed.
 * @param status Error code.
 * 
 * @return The error code.
 */
int	errmsg(char *s1, char *s2, char *s3, int status)
{
	if (s1)
		ft_putstr_fd(s1, STDERR_FILENO);
	if (s2)
		ft_putstr_fd(s2, STDERR_FILENO);
	if (s3)
		ft_putstr_fd(s3, STDERR_FILENO);
	return (status);
}
