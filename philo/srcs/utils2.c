/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 10:52:26 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/13 09:19:36 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *p, time_t ts, const char *s, int forced);
void	carefully_oversleep(int ms);
int		carefully_lock_mutex(pthread_mutex_t *m, t_philo *p);

void	print_action(t_philo *p, time_t ts, const char *s, int forced)
{
	if (forced || !p->d->finished)
	{
		pthread_mutex_lock(&p->d->printer);
		printf("%ld %d %s\n", ts - p->d->tstamp_start, p->id + 1, s);
		if (!p->d->finished)
			pthread_mutex_unlock(&p->d->printer);
	}
}

void	carefully_oversleep(int ms)
{
	long	time;

	time = get_tstamp();
	usleep(ms * 920);
	while (get_tstamp() < time + ms)
		usleep(50);
}

int	carefully_lock_mutex(pthread_mutex_t *m, t_philo *p)
{
	if (p->d->finished)
		return (0);
	pthread_mutex_lock(m);
	return (1);
}
