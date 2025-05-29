/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:40:17 by ego               #+#    #+#             */
/*   Updated: 2025/05/29 17:50:25 by ego              ###   ########.fr       */
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

# define MAX_PHILO 249
# define COLOR_R "\033[31m"
# define COLOR_G "\033[32m"
# define COLOR_B "\033[34m"
# define C_RESET "\033[0m"

typedef enum e_status
{
	DECEASED,
	EATING,
	SLEEPING,
	THINKING
}	t_status;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	time_t			last_meal_time;
	pthread_t		thread;
	int				left_fork;
	int				right_fork;
	t_status		status;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				n_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				meals_required;
	pthread_t		reaper;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*fork_locks;
	time_t			start_time;
	t_philo			**philos;
}	t_table;

// Table

t_table		*get_table(int ac, char **av);
void		*free_table(t_table *t);

// Time
time_t		get_time_in_ms(void);
void		ft_usleep(time_t wait_time);
void		delay_start(time_t start_time);

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