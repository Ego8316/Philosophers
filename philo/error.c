/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:14:21 by ego               #+#    #+#             */
/*   Updated: 2025/05/29 20:07:00 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Prints up to three strings to standard error and returns provided
 * status code. Also optionally prints in red depending on status value.
 *
 * @param s1 First string to be printed.
 * @param s2 Second string to be printed.
 * @param s3 Third string to be printed.
 * @param status Error code.
 *
 * @return Provided status code.
 *
 * @note Each string is optional.
 */
int	errmsg(const char *s1, const char *s2, const char *s3, int status)
{
	if (status)
		ft_putstr_fd(COLOR_R, STDERR_FILENO);
	if (s1)
		ft_putstr_fd(s1, STDERR_FILENO);
	if (s2)
		ft_putstr_fd(s2, STDERR_FILENO);
	if (s3)
		ft_putstr_fd(s3, STDERR_FILENO);
	if (status)
		ft_putstr_fd(C_RESET, STDERR_FILENO);
	return (status);
}

/**
 * @brief Prints one string in red to the standard error and returns NULL.
 *
 * @param s String to be printed.
 *
 * @return Always returns NULL for convenience.
 */
void	*errmsg_null(const char *s)
{
	ft_putstr_fd(COLOR_R, STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd(C_RESET, STDERR_FILENO);
	return (NULL);
}

/**
 * @brief Displays on the standard error a help message in case the user does
 * not give a valid number of arguments.
 *
 * @param ac Argument count received by the program.
 *
 * @return Always returns 1 for convenience.
 */
int	put_help_message(int ac)
{
	int	i;

	ft_putstr_fd("Usage:\t./philo ", STDERR_FILENO);
	i = -1;
	while (++i < 5)
	{
		if (i > 0)
			ft_putstr_fd("\t\t", STDERR_FILENO);
		if (i == 4)
			ft_putchar_fd('[', STDERR_FILENO);
		ft_putstr_fd(arg_label(i), STDERR_FILENO);
		if (i == 4)
			ft_putchar_fd(']', STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	if (ac < 5)
		return (errmsg("Not enough arguments.\n", 0, 0, 1));
	else
		return (errmsg("Too many arguments.\n", 0, 0, 1));
}
