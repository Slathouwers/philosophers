/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 10:27:51 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/13 13:58:29 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all_philoprocs(t_dinner *d);
void	close_semaphores(t_dinner *d);
void	free_all(t_dinner *d);

void	kill_all_philoprocs(t_dinner *d)
{
	int	i;

	i = -1;
	while (++i < d->n_philos)
		kill(d->philo_arr[i].pid, SIGKILL);
	i = -1;
	while (++i < d->n_philos)
	{
		sem_close(d->philo_arr[i].sem_lunch_lock);
		sem_unlink(d->philo_arr[i].lname);
		free(d->philo_arr[i].lname);
		d->philo_arr[i].lname = NULL;
		sem_close(d->philo_arr[i].sem_n_meals);
		sem_unlink(d->philo_arr[i].nname);
		free(d->philo_arr[i].nname);
		d->philo_arr[i].nname = NULL;
	}
	free(d->philo_arr);
	d->philo_arr = NULL;
}

void	close_semaphores(t_dinner *d)
{
	sem_close(d->sem_forks);
	sem_unlink("forks");
	sem_close(d->sem_start);
	sem_unlink("start");
	sem_close(d->sem_printer);
	sem_unlink("printer");
}

void	free_all(t_dinner *d)
{
	int	i;

	i = -1;
	if (!d)
		return ;
	if (!d->philo_arr)
		return ;
	while (++i < d->n_philos)
		if (d->philo_arr[i].lname)
			free(d->philo_arr[i].lname);
	free(d->philo_arr);
	d->philo_arr = NULL;
}
