/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:38:40 by ael-maar          #+#    #+#             */
/*   Updated: 2023/02/28 15:49:42 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include "stdio.h"

time_t	timestamp_in_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	log_sleep(char *message, int sleeptime, t_philo *philo)
{
	time_t	current_time;

	current_time = timestamp_in_ms() + sleeptime;
    // usleep(sleeptime * 1000);
    sem_wait(philo->data->printf_guard);
    printf("%ld %d %s\n", timestamp_in_ms() - philo->running_time, philo->philo_num, message);
    sem_post(philo->data->printf_guard);
	while (timestamp_in_ms() < current_time)
		usleep(10);
}

// void    death_or_done(t_philo *philo)
// {
//     int i;

//     i = 0;
//     while (i < data->philo_len)
//     {
//     if ((timestamp_in_ms() - philo->last_meal) >= philo->data->time_to_die)
//     {
//         // data->is_philo_died = 1;
//         printf("%ld %d %s\n", timestamp_in_ms() - philo->data->running_time, philo->philo_num, "has died");
//         exit(0) ; // break the loop
//     }
//         i++;
//     }
// }

void    *watch_dead(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
    {
        
        if ((timestamp_in_ms() - philo->last_meal) >= philo->data->time_to_die)
        {
            // printf("Hello?\n");
            sem_wait(philo->data->printf_guard);
            printf("%ld %d %s\n", timestamp_in_ms() - philo->running_time, philo->philo_num, "has died");
            // sem_post(philo->data->printf_guard);
            exit(0) ; // exit the process
        }
    }
}

void    run_actions(t_philo *philo)
{
    philo->running_time = timestamp_in_ms();
    pthread_create(&(philo->watch_dead), NULL, watch_dead, (void *)philo);
    pthread_detach(philo->watch_dead);
    while (1)
    {
        log_sleep("is thinking", 0, philo);
        sem_wait(philo->data->forks);
        log_sleep("has taken a fork", 0, philo);
        sem_wait(philo->data->forks);
        log_sleep("has taken a fork", 0, philo);
        log_sleep("is eating", philo->data->time_to_eat, philo);
        philo->last_meal = timestamp_in_ms();
        sem_post(philo->data->forks);
        sem_post(philo->data->forks);
        log_sleep("is sleeping", philo->data->time_to_sleep, philo);
    }
}

void    create_processes_and_run(t_philo *philo, t_shared_data *data)
{
    int     i;
    pid_t   pid;

    i = 0;
    while (i < data->philo_len)
    {
        philo[i].pid = fork();
        if (philo[i].pid == 0)
        {
            philo[i].philo_num = i;
            philo[i].data = data;
            philo[i].last_meal = timestamp_in_ms();
            run_actions(&(philo[i]));
            return ;
        }
        usleep(100);
        i++;
    }
    waitpid(-1, NULL, 0);
    // sem_post(philo->data->printf_guard);
    i = 0;
    while (i < data->philo_len)
    {
        kill(philo[i++].pid, SIGKILL);
    }
    // while (data->is_philo_died == 0)
    // {
    //     i = 0;
    //     while (i < data->philo_len)
    //     {
    //         // printf("The time for every philosopher: %ld\n", philo[i].data->asreal[i]);
    //         if ((timestamp_in_ms() - philo[i].last_meal) >= data->time_to_die)
    //         {
    //             data->is_philo_died = 1;
    //             printf("%ld %d %s\n", timestamp_in_ms() - data->running_time, i, "has died");
    //             break ; // break the loop
    //         }
    //         i++;
    //     }
    // }
    // i = 0;
    // while (i < data->philo_len)
    // {
    //     kill(philo[i++].pid, SIGINT);
    // }
}

int main(int argc, char *argv[])
{
    t_philo         *philo;
    t_shared_data   *data;
    
    if (argc > 4)
    {
        data = initialize_philo_data(argv);
        if (data)
        {
            philo = malloc(atoi(argv[1]) * sizeof(t_philo));
            if (philo)
            {
                create_processes_and_run(philo, data);
                printf("LOOOOOL IT STILL WORK\n");
            }
        }
    }
}