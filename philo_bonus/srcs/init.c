/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 10:20:57 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/11 13:56:28 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int		init_dinner(t_dinner *d, int ac, char **av);
int		init_semaphores(t_dinner *d);
int		init_philos(t_dinner *d);
void	monitor_philos(t_dinner *d);
int		launch_philos(t_dinner *d);

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
		ft_bzero(&d->philo_arr[i], sizeof(t_philo));
		d->philo_arr[i].id = i;
		d->philo_arr[i].d = d;
		d->philo_arr[i].lname = get_lunch_name(i);
		sem_unlink(d->philo_arr[i].lname);
		d->philo_arr[i].sem_lunch = sem_open(d->philo_arr[i].lname, O_CREAT,
				S_IRWXU | S_IRWXG, 1);
		if (!d->philo_arr[i].sem_lunch)
			return (0);
	}
	return (1);
}

void	monitor_philos(t_dinner *d)
{
	int	n_philos_full;
	int	exit_status;

	n_philos_full = 0;
	if (d->min_n_meals > 0)
	{
		while (n_philos_full < d->n_philos)
		{
			waitpid(-1, &exit_status, 0);
			if (WEXITSTATUS(exit_status) == EXIT_PHILO_DIED)
				break ;
			n_philos_full++;
		}
		if (n_philos_full == d->n_philos)
			printf("All philo's full..\n");
	}
	else
		waitpid(-1, &exit_status, 0);
	kill_all_philoprocs(d);
	close_semaphores(d);
}

int	launch_philos(t_dinner *d)
{
	int	i;

	i = -1;
	d->philo_arr = malloc(sizeof(t_philo) * d->n_philos);
	if (!d->philo_arr || !init_philos(d))
		return (0);
	d->tstamp_start = get_tstamp();
	while (++i < d->n_philos)
	{
		d->philo_arr[i].pid = fork();
		if (!d->philo_arr[i].pid)
			reap_death(&d->philo_arr[i]);
		else if (d->philo_arr[i].pid < 0)
			return (0);
	}
	post_start(d);
	monitor_philos(d);
	return (1);
}
