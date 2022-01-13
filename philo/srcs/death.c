/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 10:31:04 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/12 12:27:01 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*kill_philo(t_philo *p);
void	*reap_death(void *phil_arr);
int		all_finished_eating(t_philo *phil_arr);

void	*kill_philo(t_philo *p)
{
	p->dead = 1;
	p->d->finished = 1;
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(p->r_fork);
	print_action(p, get_tstamp(), "has died", 1);
	return (NULL);
}

int	all_finished_eating(t_philo *phil_arr)
{
	int			flag_finished_eating;
	int			i;
	t_dinner	*d;

	d = phil_arr[0].d;
	if (d->min_n_meals < 0)
		return (0);
	flag_finished_eating = 1;
	i = -1;
	while (++i < d->n_philos)
	{
		pthread_mutex_lock(&phil_arr[i].mealtime_lock);
		if (phil_arr[i].n_meals < d->min_n_meals)
			flag_finished_eating = 0;
		pthread_mutex_unlock(&phil_arr[i].mealtime_lock);
	}
	if (flag_finished_eating)
	{
		d->finished = 1;
		pthread_mutex_lock(&d->printer);
		printf("Philo's are full!\n");
	}
	return (flag_finished_eating);
}

void	*reap_death(void *phil_arr)
{
	t_philo			*philos;
	time_t			now;
	int				i;
	t_dinner		*d;

	philos = (t_philo *)phil_arr;
	d = philos[0].d;
	while (!d->finished)
	{
		carefully_oversleep(1);
		i = -1;
		while (++i < d->n_philos)
		{
			now = get_tstamp();
			pthread_mutex_lock(&philos[i].mealtime_lock);
			if (now - philos[i].tstamp_last_meal > d->t_to_die)
				return ((void *)kill_philo(&philos[i]));
			pthread_mutex_unlock(&philos[i].mealtime_lock);
		}
		if (all_finished_eating(philos))
			return (NULL);
	}
	return (NULL);
}
