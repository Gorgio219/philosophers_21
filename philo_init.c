/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbomber <pbomber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 15:21:07 by pbomber           #+#    #+#             */
/*   Updated: 2022/05/29 15:23:52 by pbomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Error: Wrong number of arguments.\n");
		return (1);
	}
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0
		|| ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0
		|| (ac == 6 && ft_atoi(av[5]) <= 0))
	{
		printf("Error: Wrong arguments.\n");
		return (1);
	}
	return (0);
}

t_global	*init_global(int ac, char **av)
{
	t_global	*arg;

	arg = malloc(sizeof(t_global));
	if (!arg)
		return (NULL);
	arg->count_philo = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	arg->count_of_lunch = 0;
	if (ac == 6)
		arg->count_of_lunch = ft_atoi(av[5]);
	arg->flag_of_death = 0;
	arg->time_start = 0;
	pthread_mutex_init(&arg->print, NULL);
	arg->thread = NULL;
	arg->philo = NULL;
	arg->fork = NULL;
	return (arg);
}

int	mem_allocate(t_global *global)
{
	global->philo = malloc(sizeof(t_philo) * global->count_philo);
	if (!global->philo)
		return (1);
	global->fork = malloc(sizeof(pthread_mutex_t) * global->count_philo);
	if (!global->fork)
		return (1);
	global->thread = malloc(sizeof(pthread_t) * global->count_philo);
	if (!global->thread)
		return (1);
	return (0);
}

int	init_philo(t_global *global)
{
	int	i;

	i = 0;
	while (i < global->count_philo)
	{
		global->philo[i].id = i + 1;
		global->philo[i].time_to_die = global->time_to_die;
		global->philo[i].time_to_eat = global->time_to_eat;
		global->philo[i].time_to_sleep = global->time_to_sleep;
		global->philo[i].count_eat = 0;
		global->philo[i].l_fork = i;
		if (i < global->count_philo - 1)
			global->philo[i].r_fork = i + 1;
		else
			global->philo[i].r_fork = 0;
		global->philo[i].last_eat = 0;
		global->philo[i].arg = global;
		i++;
	}
	i = 0;
	while (i < global->count_philo)
		if (pthread_mutex_init(&global->fork[i++], NULL))
			return (1);
	return (0);
}
