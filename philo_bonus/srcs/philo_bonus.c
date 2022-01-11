/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 13:54:58 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/11 13:11:58 by slathouw         ###   ########.fr       */
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
		if (ft_strlen(av[i]) > 11 || (ft_strlen(av[i]) == 11
				&& ft_strcmp(av[i], "42949667295") > 0) || !ft_is_nbr(av[i])
			|| !ft_atoi(av[i]) || ft_atoi(av[i]) < 1)
			return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_dinner	dinner;

	if (!valid_args(ac, av) || !init_dinner(&dinner, ac, av))
		return (err("Error: Invalid args\n"));
	if (!init_semaphores(&dinner))
		return (err("Error: Could not open semaphores"));
	if (!launch_philos(&dinner))
		return (err("Error: faild to launch philo processes"));
	return (0);
}
