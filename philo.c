/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbomber <pbomber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 15:21:19 by pbomber           #+#    #+#             */
/*   Updated: 2022/05/29 15:22:50 by pbomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_is_near(void *tmp)
{
	t_global	*global;
	t_philo		*p;
	int			i;

	global = tmp;
	p = global->philo;
	while (1)
	{
		i = -1;
		while (++i < global->count_philo)
		{
			if (global->count_of_lunch)
				if (p->count_eat == global->count_of_lunch)
					return (NULL);
			if (get_timestamp() - p[i].last_eat > p[i].time_to_die)
			{
				global->flag_of_death = 1;
				pthread_mutex_lock(&global->print);
				printf("%lld %d is died\n",
					get_timestamp() - p->time_start, p->id);
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	*start_game(void *tmp)
{
	t_philo		*philo;
	t_global	*global;

	philo = (t_philo *)tmp;
	global = philo->arg;
	if (philo->id % 2 == 0)
	{
		philo_print(global, philo, "is thinking");
		usleep(50);
	}
	while (!global->flag_of_death)
	{
		if (global->count_of_lunch)
			if (philo->count_eat == global->count_of_lunch)
				return (NULL);
		if (philo_eating(global, philo))
			return (NULL);
		philo_sleeping(global, philo);
		philo_thinking(global, philo);
	}
	return (NULL);
}

int	philo_life(t_global *global)
{
	int			i;
	pthread_t	check;

	i = -1;
	global->time_start = get_timestamp();
	while (++i < global->count_philo)
	{
		global->philo[i].time_start = global->time_start;
		global->philo[i].last_eat = global->time_start;
	}
	i = -1;
	while (++i < global->count_philo)
		pthread_create(&global->thread[i], NULL, \
		&start_game, &global->philo[i]);
	pthread_create(&check, NULL, &death_is_near, global);
	pthread_mutex_unlock(&global->print);
	pthread_join(check, NULL);
	i = -1;
	while (++i < global->count_philo)
		pthread_join(global->thread[i], NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_global	*global;

	if (check_arg(argc, argv))
		return (1);
	global = init_global(argc, argv);
	if (!global)
		return (ft_free(global));
	if (mem_allocate(global))
		return (ft_free(global));
	if (init_philo(global))
		return (ft_free(global));
	philo_life(global);
	ft_destroy_mutex(global);
	ft_free(global);
	return (0);
}
