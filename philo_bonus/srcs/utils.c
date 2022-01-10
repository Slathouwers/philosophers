/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 14:45:56 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/10 18:32:20 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

time_t	get_tstamp(void);
int		ft_atoi(const char *str);
int		ft_is_nbr(char *str);
int		err(const char *s);
void	ft_bzero(void *s, size_t n);

time_t	get_tstamp(void)
{
	struct timeval	t;
	time_t			tstamp;

	gettimeofday(&t, NULL);
	tstamp = 1000 * t.tv_sec + t.tv_usec / 1000;
	return (tstamp);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	i;
	int	num;

	if (!str)
		return (0);
	i = 0;
	sign = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sign);
}

int	ft_is_nbr(char *str)
{
	while (*str)
	{
		if (!('0' <= *str && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

int	err(const char *s)
{
	printf("%s", s);
	return (EXIT_FAILURE);
}

void	ft_bzero(void *s, size_t n)
{
	if (!s)
		return ;
	memset(s, 0, n);
}
