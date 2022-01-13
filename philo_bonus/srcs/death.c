/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 10:31:04 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/13 13:51:35 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	reap_death(t_philo *p);
void	post_start(t_dinner *d);

static int	is_dead(t_philo *p)
{
	time_t	now;

	now = get_tstamp();
	sem_wait(p->sem_lunch_lock);
	if (now - p->tstamp_last_meal > p->d->t_to_die)
	{
		p->dead = 1;
		print_action(p, get_tstamp(), "has died");
		return (1);
	}
	sem_post(p->sem_lunch_lock);
	return (0);
}

void	reap_death(t_philo *p)
{
	pthread_t	life_thread;
	const int	alive = 1;

	sem_wait(p->d->sem_start);
	p->tstamp_last_meal = get_tstamp();
	if (pthread_create(&life_thread, NULL, &life, p)
		|| pthread_detach(life_thread))
		exit(EXIT_ERROR);
	while (alive)
	{
		carefully_oversleep(1);
		if (is_dead(p))
			exit(EXIT_PHILO_DIED);
	}
}

void	post_start(t_dinner *d)
{
	int	i;

	i = -1;
	while (++i < d->n_philos)
		sem_post(d->sem_start);
}
