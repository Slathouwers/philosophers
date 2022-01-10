/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 13:54:58 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/10 18:32:14 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	valid_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (0);
	while (++i < ac)
		if (!ft_is_nbr(av[i]) || !ft_atoi(av[i]) || ft_atoi(av[i]) < 1)
			return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_dinner	dinner;

	if (!valid_args(ac, av) || !init_dinner(&dinner, ac, av))
		return (err("Error: Invalid args\n"));
	if (!init_mutex(&dinner) || !init_philos(&dinner))
		return (err("Error: out of memory\n"));
	if (!init_threads(&dinner))
		return (err("Failed to create threads"));
	destroy_mutex(&dinner);
	free_all(&dinner);
	return (0);
}
