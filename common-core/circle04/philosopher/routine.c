/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:42:24 by zdevove           #+#    #+#             */
/*   Updated: 2023/02/03 10:33:28 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

unsigned int timestamp(void)   // get time in ms
{
    struct timeval tv;
    
    gettimeofday(&tv, 0);
    return ((tv.tv_sec * (unsigned long)1000) + (tv.tv_usec / 1000));    // convert sec and usec to ms
    
}

void    ft_sleep(unsigned long time_to_x, t_data *data)
{
    unsigned long start;
    
    start = timestamp();
    while (!data->stop)
    {
        if (timestamp() - start >= time_to_x)    // it means we waited enough time
            break;                               // so we break and keep reading the code
        usleep(data->nb_philo * 2);
    }
}

void	philo_print(char *msg, t_philo *philo, int unlock)
{
	unsigned int	time;

	time = timestamp() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->writing);
	if (!philo->data->stop && !philo->data->max_ate)
		printf("%d %d %s\n", time, philo->num, msg);
	if (unlock)
		pthread_mutex_unlock(&philo->data->writing);
}

void    *routine(void *params)
{
    t_philo *philo;

    philo = (t_philo *)params;
    if (philo->num % 2 == 0 && philo->data->nb_philo > 1)
        usleep(philo->data->time_to_eat / 50);
    while (!philo->data->stop && !philo->data->max_ate)
    {
        pthread_mutex_lock(&philo->data->fork[philo->lfork]);   // lock left fork, if left fork already taken, thread will wait
        philo_print("has taken a fork", philo, 1);
        pthread_mutex_lock(&philo->data->fork[philo->rfork]); // lock right fork
        philo_print("has taken a fork", philo, 1);
        pthread_mutex_lock(&philo->data->meal);
        philo_print("is eating", philo, 1);

        philo->last_time_he_eat = timestamp();  // get time of the last time he eat
        pthread_mutex_unlock(&philo->data->meal);  // unlock meal
        ft_sleep(philo->data->time_to_eat, philo->data);  // philo is eating time to eat
        philo->eat_time++;

        pthread_mutex_unlock(&philo->data->fork[philo->lfork]); // unlock left fork
        pthread_mutex_unlock(&philo->data->fork[philo->rfork]); // unlock right fork

        philo_print("is sleeping", philo, 1);
		ft_sleep(philo->data->time_to_sleep, philo->data);  // philo is sleeping time to sleep
		philo_print("is thinking", philo, 1);
    }
    return (0);
}

  


int is_dead(t_philo *philo)
{
    int i;

    while (!philo->data->max_ate)
    {
        i = -1;
        while (++i < (int)philo->data->nb_philo && !philo->data->stop)
        {
            pthread_mutex_lock(&philo->data->meal);
            if (timestamp() - philo->last_time_he_eat >= philo->data->time_to_die)
            {
                philo_print("died", &philo[i], 0);
                philo->data->stop = 1;
            }
            pthread_mutex_unlock(&philo->data->meal);
        }
        if (philo->data->stop)
            return (0);
        i = 0;
        while (philo->data->nb_must_eat && i < (int)philo->data->nb_philo
            && philo[i].eat_time >= (int)philo->data->nb_must_eat)
            i++;
        philo->data->max_ate = (i == (int)philo->data->nb_philo);
    }
    return (1);
}
