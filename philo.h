/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbomber <pbomber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 15:21:22 by pbomber           #+#    #+#             */
/*   Updated: 2022/05/29 15:23:24 by pbomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int					id;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					count_eat;
	int					l_fork;
	int					r_fork;
	long long			time_start;
	long long			last_eat;
	struct s_global		*arg;
}		t_philo;

typedef struct s_global
{
	int				count_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_of_lunch;
	int				flag_of_death;
	long long		time_start;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	t_philo			*philo;
}		t_global;

long long	ft_atoi(const char *str);
long long	get_timestamp(void);
void		ft_usleep(long long time);
int			ft_free(t_global *global);
void		ft_destroy_mutex(t_global *global);

int			check_arg(int ac, char **av);
t_global	*init_global(int ac, char **av);
int			mem_allocate(t_global *global);
int			init_philo(t_global *global);

void		philo_print(t_global	*global, t_philo *philo, char *str);
int			philo_eating(t_global *global, t_philo *philo);
void		philo_sleeping(t_global *global, t_philo *philo);
void		philo_thinking(t_global *global, t_philo *philo);

#endif

// 21 290 100 100
// 50 210 100 100
// 199 2000 600 60
// time ./philo ... - исполняемый файл должен исполняться
// столько, сколько жил философ, который умер.