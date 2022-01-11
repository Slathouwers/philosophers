/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 10:52:26 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/11 12:23:21 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_action(t_philo *p, time_t ts, const char *s);
void	carefully_oversleep(int ms);
int		ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*get_lunch_name(int index);

void	print_action(t_philo *p, time_t ts, const char *s)
{
	sem_wait(p->d->sem_printer);
	printf("%ld %d %s\n", ts - p->d->tstamp_start, p->id + 1, s);
	if (!p->dead)
		sem_post(p->d->sem_printer);
}

void	carefully_oversleep(int ms)
{
	long	time;

	time = get_tstamp();
	usleep(ms * 920);
	while (get_tstamp() < time + ms)
		usleep(50);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (*str++)
		i++;
	return (i);
}

char	*get_lunch_name(int index)
{
	char	*nbr;
	char	*lname;

	nbr = ft_itoa(index);
	lname = ft_strjoin("lunch_", nbr);
	free(nbr);
	return (lname);
}
