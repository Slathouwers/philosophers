/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 10:31:04 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/12 09:53:19 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int		ate_enough(t_philo *p);
void	reap_death(t_philo *p);
void	post_start(t_dinner *d);

int	ate_enough(t_philo *p)
{
	if (p->d->min_n_meals > 0 && p->n_meals >= p->d->min_n_meals)
		return (1);
	return (0);
}

static int	is_dead(t_philo *p)
{
	time_t	now;

	now = get_tstamp();
	sem_wait(p->sem_lunch);
	if (now - p->tstamp_last_meal > p->d->t_to_die)
	{
		p->dead = 1;
		print_action(p, get_tstamp(), "has died");
		return (1);
	}
	sem_post(p->sem_lunch);
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
		carefully_oversleep(3);
		if (is_dead(p))
			exit(EXIT_PHILO_DIED);
		if (ate_enough(p))
			exit(EXIT_ATE_ENOUGH);
	}
}

void	post_start(t_dinner *d)
{
	int	i;

	i = -1;
	while (++i < d->n_philos)
		sem_post(d->sem_start);
}
