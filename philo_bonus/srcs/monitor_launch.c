/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_launch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:40:25 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/13 15:28:27 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	monitor_philos(t_dinner *d);
int		launch_philos(t_dinner *d);

static void	*monitor_death_thread(void *dinner)
{
	int	exit_status;

	waitpid(-1, &exit_status, 0);
	if (WEXITSTATUS(exit_status) == EXIT_PHILO_DIED
		&& ((t_dinner *)dinner)->full_detected == 0)
		((t_dinner *)dinner)->death_detected = 1;
	sem_post(((t_dinner *)dinner)->philo_arr[0].sem_n_meals);
	return (NULL);
}

static void	*monitor_full_thread(void *dinner)
{
	t_dinner	*d;
	int			i;
	int			*n_meals_arr;
	int			n_full;

	d = (t_dinner *)dinner;
	n_meals_arr = (int *)malloc(sizeof(int) * d->n_philos);
	ft_bzero(n_meals_arr, sizeof(int) * d->n_philos);
	n_full = 0;
	while (n_full < d->n_philos && !d->death_detected)
	{
		i = -1;
		while (++i < d->n_philos && !d->death_detected)
		{
			sem_wait(d->philo_arr[i].sem_n_meals);
			n_meals_arr[i]++;
			if (n_meals_arr[i] == d->min_n_meals && !d->death_detected)
				n_full++;
		}
	}
	d->full_detected = 1;
	printf("All philo's full..\n");
	free(n_meals_arr);
	return (NULL);
}

void	monitor_philos(t_dinner *d)
{
	pthread_t	monitor_death;
	pthread_t	monitor_full;

	pthread_create(&monitor_death, NULL, &monitor_death_thread, d);
	pthread_detach(monitor_death);
	if (d->min_n_meals > 0)
	{
		pthread_create(&monitor_full, NULL, &monitor_full_thread, d);
		pthread_detach(monitor_full);
	}
	while (!d->death_detected && !d->full_detected)
		;
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
