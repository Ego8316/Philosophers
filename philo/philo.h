/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:40:17 by ego               #+#    #+#             */
/*   Updated: 2025/05/30 14:17:50 by ego              ###   ########.fr       */
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
# define MALLOC_ERR "malloc error: memory allocation failed"
# define MUTEX_ERR "mutex error: mutex initialization failed"
# define THREAD_ERR "thread error: thread creation failed"
# define COLOR_R "\033[31m"
# define COLOR_G "\033[32m"
# define COLOR_B "\033[34m"
# define COLOR_A "\033[90m"
# define COLOR_V "\033[38;5;93m"
# define C_RESET "\033[0m"

typedef enum e_status
{
	DECEASED = 0,
	FORK = 1,
	EATING = 2,
	SLEEPING = 3,
	THINKING = 4
}	t_status;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	time_t			last_meal_time;
	int				left_fork;
	int				right_fork;
	pthread_mutex_t	last_meal_lock;
	pthread_mutex_t	meals_lock;
	pthread_t		thread;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				n;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				meals_required;
	int				sim_running;
	t_philo			**philos;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	sim_running_lock;
	pthread_mutex_t	*forks;
	time_t			start_time;
	pthread_t		reaper;
}	t_table;

// Table

t_table		*get_table(int ac, char **av);

// Routines
void		*philo_routine(void *d);
void		*reaper_routine(void *d);

// Monitoring
int			is_simulation_running(t_table *table);
void		print_status(t_philo *philo, t_status status);

// Time
time_t		get_time_in_ms(void);
void		ft_usleep(time_t wait_time);
void		delay_start(time_t start_time);

// Free, join and destroy functions
void		destroy_mutexes(pthread_mutex_t *m, int size);
void		*free_array(void **arr, int size);
void		*free_philos(t_philo **p, int size);
int			join_philos(t_philo **p, int size);
void		*free_table(t_table *t);

// Utilities

int			ft_strcmp(const char *s1, const char *s2);
void		*ft_calloc(size_t nmemb, size_t size);
void		swap_int(int *a, int *b);
int			ft_atoi(const char *nptr);
int			ft_isspace(int c);
int			ft_isdigit(int c);

// Display and error handling

int			is_valid_input(int ac, char **av);
int			put_help_message(int ac);
int			errmsg(const char *s1, const char *s2, const char *s3, int s);
void		*errmsg_null(const char *s);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(const char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putendl_fd(const char *s, int fd);
const char	*arg_label(int i);

#endif