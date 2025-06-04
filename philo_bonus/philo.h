/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:40:17 by ego               #+#    #+#             */
/*   Updated: 2025/06/04 14:12:17 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>
# include <limits.h>

# define MAX_PHILO 200
# define MALLOC_ERR "malloc error: memory allocation failed"
# define FORK_ERR "fork error: fork failed"
# define SEM_OPEN_ERR "semaphore error: could not open semaphore"
# define SEM_UNLINK_ERR "semaphore error: could not unlink semaphore"
# define THREAD_ERR "thread error: thread creation failed"
# define FORKS_SEM_NAME "/forks_sem"
# define PRINT_SEM_NAME "/print_sem"
# define MEALS_SEM_NAME "/meals_sem"
# define LAST_MEAL_SEM_PREFIX "/last_meal_sem_"
# define BUFFER_SIZE 32
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
	pid_t			pid;
	time_t			last_meal_time;
	char			last_meal_sem_name[BUFFER_SIZE];
	int				meals_eaten;
	sem_t			*last_meal_sem;
	pthread_t		reaper;
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
	sem_t			*print_sem;
	sem_t			*forks_sem;
	sem_t			*meals_sem;
	time_t			start_time;
	pthread_t		reaper;
}	t_table;

// Table

t_table		*get_table(int ac, char **av);

// Routines
void		*philo_routine(void *d);
void		*reaper_routine(void *d);

// Monitoring
int			should_simulation_stop(t_table *table);
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
long		ft_max(long a, long b);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
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