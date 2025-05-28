/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:31:01 by ego               #+#    #+#             */
/*   Updated: 2025/05/28 20:34:06 by ego              ###   ########.fr       */
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
 * @brief Compares two strings lexicographically.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * 
 * @return 0 if the strings are equal, a positive value if s1 > s2,
 * or a negative value if s1 < s2.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	int		diff;
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		diff = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (diff)
			return (diff);
		i++;
	}
	return (0);
}

/*	ft_isint
*	Checks if the given string corresponds to an integer.
*	Return: 1 if the string is an int, 2 if it is a zero, 0 otherwise.
*/
static int	ft_isint(char *s)
{
	int			i;
	int			j;
	long int	n;

	i = 0;
	j = 0;
	n = 0;
	if ((s[i] == '+' || s[i] == '-') && s[i + 1])
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		if (s[i] == '0')
			j++;
		n = n * 10 + (s[i] - '0');
		if (n > ((long int)INT_MAX + (s[0] == '-')))
			return (0);
		i++;
	}
	if ((j + (s[0] == '+' || s[0] == '-')) == i)
		return (2);
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
