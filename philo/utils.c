/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:43:58 by ego               #+#    #+#             */
/*   Updated: 2025/05/29 12:57:48 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
