/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:31:01 by ego               #+#    #+#             */
/*   Updated: 2025/05/29 13:12:37 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** 
 * @brief Checks if a character is a space.
 * 
 * @param c The character to check.
 * 
 * @return 1 if the character is a space, 0 otherwise.
 */
int	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

/** 
 * @brief Checks if a character is a digit.
 * 
 * @param c The character to check.
 * 
 * @return 1 if the character is a digit, 0 otherwise.
 */
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/**
 * @brief Checks if the given string represents a valid signed integer.
 * 
 * Skips leading whitespace characters, allows an optional '+' or '-' sign,
 * ensures that the rest of the string consists only of digits, and checks if
 * the parsed number does not overflow or underflow the limits of an integer.
 * 
 * @param s String to be checked.
 * 
 * @return 1 if the string is a valid integer within int range, 0 otherwise.
 */
int	is_valid_integer(char *s)
{
	int			i;
	int			j;
	long int	n;

	i = 0;
	n = 0;
	while (ft_isspace(s[i]))
		i++;
	j = i;
	if ((s[i] == '+' || s[i] == '-') && ft_isdigit(s[i + 1]))
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		n = n * 10 + (s[i] - '0');
		if (n > ((long int)INT_MAX + (s[j] == '-')))
			return (0);
		i++;
	}
	return (1);
}

/** 
 * @brief Converts a string to an integer.
 * 
 * @param str The string to convert.
 * 
 * @return The integer value of the string.
 */
int	ft_atoi(const char *nptr)
{
	int	nb;
	int	i;
	int	sign;

	nb = 0;
	i = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		sign = -(nptr[i] - 44);
		i++;
	}
	if (sign < 0 && !ft_strcmp("2147483648", nptr + i))
		return (-2147483648);
	while (ft_isdigit(nptr[i]))
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	return (nb * sign);
}
