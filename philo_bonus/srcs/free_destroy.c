/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 10:27:51 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/10 18:34:01 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_mutex(t_dinner *d);
void	free_all(t_dinner *d);

void	destroy_mutex(t_dinner *d)
{
	int	i;

	i = -1;
	while (++i < d->n_philos)
	{
		pthread_mutex_unlock(&d->philo_arr[i].mealtime_lock);
		pthread_mutex_destroy(&d->philo_arr[i].mealtime_lock);
		pthread_mutex_unlock(&d->fork_arr[i]);
		pthread_mutex_destroy(&d->fork_arr[i]);
	}
	pthread_mutex_unlock(&d->printer);
	pthread_mutex_destroy(&d->printer);
}

void	free_all(t_dinner *d)
{
	if (d->fork_arr)
		free(d->fork_arr);
	if (d->philo_arr)
		free(d->philo_arr);
	if (d->life_threads)
		free(d->life_threads);
}
