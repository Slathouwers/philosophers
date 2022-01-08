/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 13:31:43 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/08 13:53:14 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
/*for memset()*/

# include <stdio.h>
/*for printf()*/
# include <stdlib.h> 
/*for malloc(), free()*/
# include <unistd.h>
/*for usleep()*/
# include <sys/time.h>
/*for gettimeofday()*/
# include <pthread.h>
/*for pthread_create() pthread_join() pthread_detach(), pthread_mutex_init()
	pthread_mutex_destroy(), pthread_mutex_lock(), pthread_mutex_unlock()*/


#endif