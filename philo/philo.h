/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:40:17 by ego               #+#    #+#             */
/*   Updated: 2025/05/29 13:21:02 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_table
{
	int	philo_number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	min_lunches;
}	t_table;

// Table

t_table	*get_table(int ac, char **av);
void	*free_table(t_table *t);

// Utilities

int		ft_atoi(const char *nptr);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_calloc(size_t nmemb, size_t size);

// Display

int		put_help_message(void);
int		errmsg(char *s1, char *s2, char *s3, int status);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(const char *s, int fd);

#endif