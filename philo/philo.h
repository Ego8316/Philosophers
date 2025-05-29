/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:40:17 by ego               #+#    #+#             */
/*   Updated: 2025/05/29 14:59:26 by ego              ###   ########.fr       */
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

# define COLOR_R "\033[31m"
# define COLOR_G "\033[32m"
# define COLOR_B "\033[34m"
# define C_RESET "\033[0m"

typedef struct s_table
{
	int	philo_number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	min_lunches;
}	t_table;

// Table

t_table		*get_table(int ac, char **av);
void		*free_table(t_table *t);

// Utilities

int			ft_atoi(const char *nptr);
int			ft_strcmp(const char *s1, const char *s2);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_isspace(int c);
int			ft_isdigit(int c);

// Display and error handling

int			is_valid_input(int ac, char **av);
int			put_help_message(int ac);
int			errmsg(const char *s1, const char *s2, const char *s3, int s);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(const char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putendl_fd(const char *s, int fd);
const char	*arg_label(int i);

#endif