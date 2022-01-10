/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 13:31:43 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/10 09:29:50 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
# include <pthread.h>

typedef struct s_philo	t_philo;
typedef struct s_dinner	t_dinner;

struct s_philo
{
	int				id;
	time_t			tstamp_last_meal;
	int				n_meals;
	int				dead;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	mealtime_lock;
	t_dinner		*d;
};

struct s_dinner
{
	int				n_philos;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	time_t			tstamp_start;
	int				finished;
	int				min_n_meals;
	pthread_mutex_t	*fork_arr;
	pthread_mutex_t	printer;
	t_philo			*philo_arr;
	pthread_t		*life_threads;
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

/*INIT.c*/
int		init_dinner(t_dinner *d, int ac, char **av);
int		init_mutex(t_dinner *d);
int		init_philos(t_dinner *dinner);
int		init_threads(t_dinner *d);

/*LIFE.c*/
void	take_forks(t_philo *p);
void	eat(t_philo *p);
void	go_to_sleep(t_philo *p);
void	think(t_philo *p);
void	*life(void *philosopher);

/*DEATH.c*/
void	kill_philo(t_philo *p);
void	*reap_death(void *phil_arr);
int		all_finished_eating(t_philo *phil_arr);

/*FREE_DESTROY.c*/
void	destroy_mutex(t_dinner *d);
void	free_all(t_dinner *d);

#endif