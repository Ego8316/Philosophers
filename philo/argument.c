/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:31:01 by ego               #+#    #+#             */
/*   Updated: 2025/06/01 12:07:02 by ego              ###   ########.fr       */
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
 * @brief Valideates command-line arguments for the simulation.
 * 
 * Performs the following checks on each argument:
 * @brief - Not empty.
 * @brief - Represents a valid integer.
 * @brief - Is positive (greater than 0).
 * 
 * Also ensures the number of philosophers do not exceed `MAX_PHILO` and
 * prints on the standard error the appropriate error message.
 * 
 * @param ac Argument count.
 * @param av Argument vector.
 * 
 * @return 1 if all inputs are valid, 0 otherwise.
 */
int	is_valid_input(int ac, char **av)
{
	int	i;
	int	ret;
	int	value;

	i = -1;
	ret = 1;
	while (++i < ac - 1)
	{
		value = ft_atoi(av[i + 1]);
		if (!*av[i + 1])
			ret = errmsg(arg_label(i), ": empty argument\n", 0, 0);
		else if (!is_valid_integer(av[i + 1]))
			ret = errmsg(arg_label(i), ": not a valid integer\n", 0, 0);
		else if (value < 0)
			ret = errmsg(arg_label(i), ": negative value\n", 0, 0);
		else if (value == 0)
			ret = errmsg(arg_label(i), ": null value\n", 0, 0);
		else if (i == 0 && value > MAX_PHILO)
			ret = errmsg(arg_label(i), ": too many philosophers\n", 0, 0);
	}
	return (ret);
}
