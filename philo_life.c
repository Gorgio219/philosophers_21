/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbomber <pbomber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 15:21:13 by pbomber           #+#    #+#             */
/*   Updated: 2022/05/29 15:23:43 by pbomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_global	*global, t_philo *philo, char *str)
{
	if (global->flag_of_death)
		return ;
	pthread_mutex_lock(&global->print);
	if (global->flag_of_death)
		return ;
	printf("%lld %d %s\n",
		get_timestamp() - philo->time_start, philo->id, str);
	pthread_mutex_unlock(&global->print);
}

int	philo_eating(t_global *global, t_philo *philo)
{
	if (global->flag_of_death)
		return (1);
	pthread_mutex_lock(&global->fork[philo->l_fork]);
	philo_print(global, philo, "has taken a fork_l");
	if (global->count_philo == 1)
		return (pthread_mutex_unlock(\
			&global->fork[global ->philo->l_fork]), 1);
	pthread_mutex_lock(&global->fork[philo->r_fork]);
	philo_print(global, philo, "has taken a fork_r");
	philo_print(global, philo, "is eating");
	philo->count_eat++;
	philo->last_eat = get_timestamp();
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&global->fork[philo->l_fork]);
	pthread_mutex_unlock(&global->fork[philo->r_fork]);
	return (0);
}

void	philo_sleeping(t_global *global, t_philo *philo)
{
	if (global->flag_of_death)
		return ;
	philo_print(global, philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	philo_thinking(t_global *global, t_philo *philo)
{
	if (global->flag_of_death)
		return ;
	philo_print(global, philo, "is thinking");
}
