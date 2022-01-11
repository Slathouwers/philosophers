/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 13:31:43 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/11 13:13:13 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/*
Memleak on detached threads: 
https://stackoverflow.com/questions/20893358/
a-detached-pthread-causes-memory-leaks
*/
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <pthread.h>
# include <signal.h>
# include <fcntl.h>
# include <semaphore.h>

# define EXIT_ATE_ENOUGH	42
# define EXIT_PHILO_DIED	43
# define EXIT_ERROR			44

typedef struct s_philo	t_philo;
typedef struct s_dinner	t_dinner;

struct s_philo
{
	int				id;
	pid_t			pid;
	time_t			tstamp_last_meal;
	int				n_meals;
	int				dead;
	sem_t			*sem_lunch;
	char			*lname;
	t_dinner		*d;
};

struct s_dinner
{
	int				n_philos;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				min_n_meals;
	time_t			tstamp_start;
	sem_t			*sem_forks;
	sem_t			*sem_start;
	sem_t			*sem_printer;
	t_philo			*philo_arr;
};

/*UTILS.c*/
time_t	get_tstamp(void);
int		ft_atoi(const char *str);
int		ft_is_nbr(char *str);
int		err(const char *s);
void	ft_bzero(void *s, size_t n);

/*UTILS2.c*/
void	print_action(t_philo *p, time_t ts, const char *s);
void	carefully_oversleep(int ms);
int		ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*get_lunch_name(int index);

/*UTILS3.c*/
char	*ft_itoa(int n);
char	*ft_strjoin(char *s1, char *s2);

/*INIT.c*/
int		init_dinner(t_dinner *d, int ac, char **av);
int		init_semaphores(t_dinner *d);
int		init_philos(t_dinner *d);
void	monitor_philos(t_dinner *d);
int		launch_philos(t_dinner *d);

/*LIFE.c*/
void	take_forks(t_philo *p);
void	eat(t_philo *p);
void	go_to_sleep(t_philo *p);
void	think(t_philo *p);
void	*life(void *philosopher);

/*DEATH.c*/
int		ate_enough(t_philo *p);
void	reap_death(t_philo *p);
void	post_start(t_dinner *d);

/*FREE_DESTROY.c*/
void	kill_all_philoprocs(t_dinner *d);
void	close_semaphores(t_dinner *d);
void	free_all(t_dinner *d);

#endif