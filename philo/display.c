/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:40:19 by ego               #+#    #+#             */
/*   Updated: 2025/05/28 20:40:29 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** 
 * @brief Writes a character to a file descriptor.
 * 
 * @param c The character to write.
 * @param fd The file descriptor.
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return ;
}

/** 
 * @brief Writes a string to a file descriptor.
 * 
 * @param s The string to write.
 * @param fd The file descriptor.
 */
void	ft_putstr_fd(const char *s, int fd)
{
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
	return ;
}

/** 
 * @brief Writes a number to a file descriptor.
 * 
 * @param n The number to write.
 * @param fd The file descriptor.
 */
void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		n %= 10;
	}
	ft_putchar_fd('0' + n, fd);
	return ;
}

/** 
 * @brief Writes a string followed by a newline to a file descriptor.
 * 
 * @param s The string to write.
 * @param fd The file descriptor.
 */
void	ft_putendl_fd(const char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
	return ;
}
