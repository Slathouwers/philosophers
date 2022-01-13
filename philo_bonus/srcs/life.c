/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 10:26:43 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/13 13:57:39 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks(t_philo *p);
void	eat(t_philo *p);
void	go_to_sleep(t_philo *p);
void	think(t_philo *p);
void	*life(void *philosopher);

void	take_forks(t_philo *p)
{
	const t_dinner	*d = p->d;

	sem_wait(d->sem_forks);
	print_action(p, get_tstamp(), "has taken a fork");
	sem_wait(d->sem_forks);
	print_action(p, get_tstamp(), "has taken a fork");
	sem_wait(p->sem_lunch_lock);
}

void	eat(t_philo *p)
{
	const t_dinner	*d = p->d;

	p->tstamp_last_meal = get_tstamp();
	print_action(p, get_tstamp(), "is eating");
	sem_post(p->sem_n_meals);
	sem_post(p->sem_lunch_lock);
	carefully_oversleep(d->t_to_eat);
	sem_post(d->sem_forks);
	sem_post(d->sem_forks);
}

void	go_to_sleep(t_philo *p)
{
	const t_dinner	*d = p->d;

	print_action(p, get_tstamp(), "is sleeping");
	carefully_oversleep(d->t_to_sleep);
}

void	think(t_philo *p)
{
	print_action(p, get_tstamp(), "is thinking");
}

void	*life(void *philosopher)
{
	t_philo	*p;

	p = (t_philo *)philosopher;
	if (p->id % 2)
		carefully_oversleep(3);
	while (!p->dead)
	{
		take_forks(p);
		eat(p);
		go_to_sleep(p);
		think(p);
	}
	return (NULL);
}
