/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:16:18 by ael-maar          #+#    #+#             */
/*   Updated: 2023/02/24 12:09:37 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

time_t	timestamp_in_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	death_or_done(t_philos *philo)
{// protect
	int	is_done;

	is_done = 0;
	pthread_mutex_lock(&(philo->info_philos->state_guard));
	if (philo->info_philos->a_philo_died == 1)
		is_done = 1;
	if (philo->info_philos->is_all_eaten == 1)
		is_done = 1;
	pthread_mutex_unlock(&(philo->info_philos->state_guard));
	return (is_done);
}

void	log_sleep(char *message, int sleeptime, t_philos *philo, int isdied)
{
	time_t	current_time;

	current_time = timestamp_in_ms() + sleeptime;
	pthread_mutex_lock(&(philo->info_philos->printf_guard));
	if (!death_or_done(philo))
	{
		printf("%ld %d %s\n", timestamp_in_ms() - philo->info_philos->running_time, philo->philo_num, message);
	}
	pthread_mutex_unlock(&(philo->info_philos->printf_guard));
	while (timestamp_in_ms() < current_time)
		usleep(10);
}

void	*run_actions(void *philo_id)
{
	t_philos	*philo = (t_philos *)philo_id;

	while (death_or_done(philo) == 0)
	{
		log_sleep("is thinking", 0, philo, philo->info_philos->a_philo_died);
		pthread_mutex_lock(&(philo->info_philos->forks[philo->philo_num]));
		log_sleep("has taken a fork", 0, philo, philo->info_philos->a_philo_died);
		if (philo->info_philos->philo_len == 1)
		{
			pthread_mutex_unlock(&(philo->info_philos->forks[philo->philo_num]));
			break ;
		}
		pthread_mutex_lock(&(philo->info_philos->forks[(philo->philo_num + 1) % philo->info_philos->philo_len]));
		log_sleep("has taken a fork", 0, philo, philo->info_philos->a_philo_died);
		log_sleep("is eating", philo->info_philos->time_to_eat, philo, philo->info_philos->a_philo_died);
		// data guard protection for every philo
		pthread_mutex_lock(&(philo->data_guard));
		philo->eat_times--;
		pthread_mutex_unlock(&(philo->data_guard));
		// state guard protection for shared data
		pthread_mutex_lock(&(philo->info_philos->state_guard));
		philo->info_philos->asreal[philo->philo_num] = timestamp_in_ms();
		pthread_mutex_unlock(&(philo->info_philos->state_guard));
		pthread_mutex_unlock(&(philo->info_philos->forks[philo->philo_num]));
		pthread_mutex_unlock(&(philo->info_philos->forks[(philo->philo_num + 1) % philo->info_philos->philo_len]));
		log_sleep("is sleeping", philo->info_philos->time_to_sleep, philo, philo->info_philos->a_philo_died);
	}
	return (NULL);
}

void	create_threads_and_run(t_philos *philos, t_info *info)
{
	int	i;
	int	is_ate;

	i = 0;
	while (i < info->philo_len)
	{
		philos[i].info_philos = info;
		philos[i].philo_num = i;
		philos[i].eat_times = info->g_eat_times;
		philos[i].info_philos->asreal[i] = timestamp_in_ms();
		pthread_mutex_init(&(philos[i].data_guard), NULL);
		pthread_create(&philos[i].thread, NULL, run_actions, (void *)&philos[i]);
		usleep(100);
		++i;
	}
	while (death_or_done(philos) == 0)
	{
		i = 0;
		is_ate = 1;
		while (i < info->philo_len)
		{
			if ((timestamp_in_ms() - philos[i].info_philos->asreal[i]) >= info->time_to_die)
			{
				info->a_philo_died = 1;
				pthread_mutex_lock(&(info->printf_guard));
				printf("%ld %d %s\n", timestamp_in_ms() - info->running_time, philos[i].philo_num, "has died");
				pthread_mutex_unlock(&(info->printf_guard));
				break ;
			}
			if (info->is_all_eaten != -1 && philos[i++].eat_times > 0)
				is_ate = 0;
			++i;
		}
		if (info->is_all_eaten != -1 && is_ate == 1)
			info->is_all_eaten = 1;
	}
}

int	main(int argc, char *argv[])
{
	t_info			*info;
	t_philos		*philos;

	if (argc > 4)
	{
		info = generate_info_struct(argc, argv);
		if (info)
		{
			philos = malloc(atoi(argv[1]) * sizeof(t_philos));
			if (philos)
			{
				create_threads_and_run(philos, info);
				int i = 0;
				while (i < info->philo_len)
					pthread_join(philos[i++].thread, NULL);
				for (int j = 0; j < info->philo_len; j++)
					pthread_mutex_destroy(&(info->forks[j]));
				pthread_mutex_destroy(&(info->printf_guard));
				return (0);
			}
		}
	}
	return (0);
}
