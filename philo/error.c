/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:14:21 by ego               #+#    #+#             */
/*   Updated: 2025/05/28 20:46:54 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
