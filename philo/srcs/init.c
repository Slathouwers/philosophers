/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 10:20:57 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/10 09:16:56 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_dinner(t_dinner *d, int ac, char **av);
int	init_mutex(t_dinner *d);
int	init_philos(t_dinner *dinner);
int	init_threads(t_dinner *d);

int	init_dinner(t_dinner *d, int ac, char **av)
{
	ft_bzero(d, sizeof(t_dinner));
	d->n_philos = ft_atoi(av[1]);
	d->t_to_die = ft_atoi(av[2]);
	d->t_to_eat = ft_atoi(av[3]);
	d->t_to_sleep = ft_atoi(av[4]);
	d->finished = 0;
	if (ac == 5)
		d->min_n_meals = -1;
	else
		d->min_n_meals = ft_atoi(av[5]);
	return (1);
}

int	init_mutex(t_dinner *d)
{
	int				n_philos;
	pthread_mutex_t	*forks;

	n_philos = d->n_philos;
	forks = malloc(sizeof(pthread_mutex_t) * n_philos);
	if (!forks)
		return (0);
	while (n_philos--)
		pthread_mutex_init(&forks[n_philos], NULL);
	pthread_mutex_init(&d->printer, NULL);
	d->fork_arr = forks;
	return (1);
}

int	init_philos(t_dinner *dinner)
{
	int		i;
	t_philo	*phil_arr;

	i = -1;
	phil_arr = (t_philo *) malloc(sizeof(t_philo) * dinner->n_philos);
	if (!phil_arr)
	{
		if (dinner->fork_arr)
			free(dinner->fork_arr);
		return (0);
	}
	while (++i < dinner->n_philos)
	{
		ft_bzero(&phil_arr[i], sizeof(t_philo));
		phil_arr[i].id = i;
		phil_arr[i].l_fork = &dinner->fork_arr[i];
		phil_arr[i].r_fork = &dinner->fork_arr[(i + 1) % dinner->n_philos];
		phil_arr[i].d = dinner;
		pthread_mutex_init(&phil_arr[i].mealtime_lock, NULL);
	}
	dinner->philo_arr = phil_arr;
	return (1);
}

int	init_threads(t_dinner *d)
{
	int			n_philos;
	pthread_t	*life_threads;
	pthread_t	grim_reaper;

	n_philos = d->n_philos;
	d->tstamp_start = get_tstamp();
	life_threads = (pthread_t *) malloc(sizeof(pthread_t) * n_philos);
	if (!life_threads)
	{
		free_all(d);
		return (0);
	}
	while (n_philos--)
	{
		d->philo_arr[n_philos].tstamp_last_meal = get_tstamp();
		pthread_create(&life_threads[n_philos], NULL,
			&life, (void *)&d->philo_arr[n_philos]);
		pthread_detach(life_threads[n_philos]);
	}
	pthread_create(&grim_reaper, NULL, &reap_death, (void *)d->philo_arr);
	pthread_join(grim_reaper, NULL);
	//reap_death(d->philo_arr);
	d->life_threads = life_threads;
	return (1);
}
