/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 10:26:43 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/13 09:21:58 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *p);
void	eat(t_philo *p);
void	go_to_sleep(t_philo *p);
void	think(t_philo *p);
void	*life(void *philosopher);

void	take_forks(t_philo *p)
{
	if (p->id % 2 == 0 && p->id + 1 < p->d->n_philos)
	{
		if (!carefully_lock_mutex(p->r_fork, p))
			return ;
		print_action(p, get_tstamp(), "has taken a fork", 0);
		if (!carefully_lock_mutex(p->l_fork, p))
			return ;
		print_action(p, get_tstamp(), "has taken a fork", 0);
		if (!carefully_lock_mutex(&p->mealtime_lock, p))
			return ;
	}
	else
	{
		if (!carefully_lock_mutex(p->l_fork, p))
			return ;
		print_action(p, get_tstamp(), "has taken a fork", 0);
		if (!carefully_lock_mutex(p->r_fork, p))
			return ;
		print_action(p, get_tstamp(), "has taken a fork", 0);
		if (!carefully_lock_mutex(&p->mealtime_lock, p))
			return ;
	}
}

void	eat(t_philo *p)
{
	print_action(p, get_tstamp(), "is eating", 0);
	p->tstamp_last_meal = get_tstamp();
	p->n_meals++;
	pthread_mutex_unlock(&p->mealtime_lock);
	carefully_oversleep(p->d->t_to_eat);
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(p->r_fork);
}

void	go_to_sleep(t_philo *p)
{
	print_action(p, get_tstamp(), "is sleeping", 0);
	carefully_oversleep(p->d->t_to_sleep);
}

void	think(t_philo *p)
{
	print_action(p, get_tstamp(), "is thinking", 0);
}

void	*life(void *philosopher)
{
	t_philo	*p;

	p = (t_philo *)philosopher;
	while (!p->d->finished)
	{
		take_forks(p);
		if (p->d->finished)
			return (NULL);
		eat(p);
		if (p->d->finished)
			return (NULL);
		go_to_sleep(p);
		if (p->d->finished)
			return (NULL);
		think(p);
	}
	return (NULL);
}
