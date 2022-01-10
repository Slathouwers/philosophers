/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 10:26:43 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/10 18:32:09 by slathouw         ###   ########.fr       */
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
	if (p->id % 2 == 0 && p->id + 1 < p->d->n_philos)
	{
		pthread_mutex_lock(p->r_fork);
		print_action(p, get_tstamp(), "has taken a fork");
		pthread_mutex_lock(p->l_fork);
		print_action(p, get_tstamp(), "has taken a fork");
		pthread_mutex_lock(&p->mealtime_lock);
	}
	else
	{
		pthread_mutex_lock(p->l_fork);
		print_action(p, get_tstamp(), "has taken a fork");
		pthread_mutex_lock(p->r_fork);
		print_action(p, get_tstamp(), "has taken a fork");
		pthread_mutex_lock(&p->mealtime_lock);
	}
}

void	eat(t_philo *p)
{
	p->tstamp_last_meal = get_tstamp();
	print_action(p, get_tstamp(), "is eating");
	pthread_mutex_unlock(&p->mealtime_lock);
	p->n_meals++;
	carefully_oversleep(p->d->t_to_eat);
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(p->r_fork);
}

void	go_to_sleep(t_philo *p)
{
	print_action(p, get_tstamp(), "is sleeping");
	carefully_oversleep(p->d->t_to_sleep);
}

void	think(t_philo *p)
{
	print_action(p, get_tstamp(), "is thinking");
}

void	*life(void *philosopher)
{
	t_philo	*p;

	p = (t_philo *)philosopher;
	while (!p->d->finished)
	{
		take_forks(p);
		eat(p);
		go_to_sleep(p);
		think(p);
	}
	return (NULL);
}
