/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:43:58 by ego               #+#    #+#             */
/*   Updated: 2025/06/04 13:54:35 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Gets the maximum value between two long integers.
 * 
 * @param a First long.
 * @param b Second long.
 * 
 * @return The maximum between a and b.
 */
long	ft_max(long a, long b)
{
	if (a > b)
		return (a);
	return (b);
}

/** 
 * @brief Copies a string to another buffer with bounds checking.
 * 
 * @param dst The destination buffer.
 * @param src The source string.
 * @param dstsize The size of the destination buffer.
 * 
 * @return The length of the source string.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	while (src[src_len])
		src_len++;
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
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

/** 
 * @brief Allocates memory and initializes it to zero.
 * 
 * @param nmemb The number of elements.
 * @param size The size of each element.
 * 
 * @return A pointer to the allocated memory.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;

	array = (void *)malloc(nmemb * size);
	if (!array)
		return (NULL);
	memset(array, 0, nmemb * size);
	return (array);
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
