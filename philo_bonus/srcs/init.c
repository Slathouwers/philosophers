/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 10:20:57 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/13 14:42:30 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int		init_dinner(t_dinner *d, int ac, char **av);
int		init_semaphores(t_dinner *d);
int		init_philos(t_dinner *d);

int	init_dinner(t_dinner *d, int ac, char **av)
{
	ft_bzero(d, sizeof(t_dinner));
	d->n_philos = ft_atoi(av[1]);
	d->t_to_die = ft_atoi(av[2]);
	d->t_to_eat = ft_atoi(av[3]);
	d->t_to_sleep = ft_atoi(av[4]);
	if (ac == 5)
		d->min_n_meals = -1;
	else
		d->min_n_meals = ft_atoi(av[5]);
	return (1);
}

int	init_semaphores(t_dinner *d)
{
	sem_unlink("printer");
	d->sem_printer = sem_open("printer", O_CREAT, S_IRWXU | S_IRWXG, 1);
	sem_unlink("start");
	d->sem_start = sem_open("start", O_CREAT, S_IRWXU | S_IRWXG, 0);
	sem_unlink("forks");
	d->sem_forks = sem_open("forks", O_CREAT, S_IRWXU | S_IRWXG, d->n_philos);
	if (!d->sem_forks || !d->sem_printer || !d->sem_start)
		return (0);
	return (1);
}

int	init_philos(t_dinner *d)
{
	int		i;

	i = -1;
	while (++i < d->n_philos)
	{
		carefully_oversleep(2);
		ft_bzero(&d->philo_arr[i], sizeof(t_philo));
		d->philo_arr[i].id = i;
		d->philo_arr[i].d = d;
		d->philo_arr[i].lname = get_lunch_name(i);
		sem_unlink(d->philo_arr[i].lname);
		d->philo_arr[i].sem_lunch_lock = sem_open(d->philo_arr[i].lname,
				O_CREAT, S_IRWXU | S_IRWXG, 1);
		if (!d->philo_arr[i].sem_lunch_lock)
			return (0);
		d->philo_arr[i].nname = get_lunch_name(i + d->n_philos);
		sem_unlink(d->philo_arr[i].nname);
		d->philo_arr[i].sem_n_meals = sem_open(d->philo_arr[i].nname,
				O_CREAT, S_IRWXU | S_IRWXG, 0);
		if (!d->philo_arr[i].sem_lunch_lock)
			return (0);
	}
	return (1);
}
