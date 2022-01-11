/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3..c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 09:06:49 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/11 13:05:24 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*ft_itoa(int n);
char	*ft_strjoin(char *s1, char *s2);

static size_t	ft_nbr_len(int nbr)
{
	size_t	len;

	len = 0;
	if (nbr <= 0)
		len++;
	while (nbr)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static unsigned int	to_un(int n, int *sign)
{
	unsigned int	un;

	if (n < 0)
	{
		*sign = -1;
		un = (unsigned int) - n;
	}
	else
		un = n;
	return (un);
}

char	*ft_itoa(int n)
{
	int				len;
	int				sign;
	char			*c;
	unsigned int	un;

	sign = 0;
	un = to_un(n, &sign);
	len = ft_nbr_len(n);
	c = (char *)malloc(sizeof(char) * len + 1);
	if (c == NULL)
		return (0);
	c[len] = '\0';
	len--;
	while (len >= 0)
	{
		c[len--] = '0' + (un % 10);
		un /= 10;
	}
	if (sign == -1)
		c[0] = '-';
	return (c);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*join;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	while (s1[i])
		join[j++] = s1[i++];
	i = 0;
	while (s2[i])
		join[j++] = s2[i++];
	join[j] = '\0';
	return (join);
}
