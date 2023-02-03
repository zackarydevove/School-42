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
    printf("ms: %lu", tv.tv_sec * 1000 + tv.tv_usec / 1000);
    return (tv.tv_sec * 1000 + (tv.tv_usec / 1000));    // convert sec and usec to ms
    
}

void    ft_sleep(unsigned int time_to_x, t_data *data)
{
    unsigned long start = timestamp();
    while (!data->stop)
    {
        if (timestamp() - start == time_to_x)    // it means we waited enough time
            break;                               // so we break and keep reading the code
        usleep(data->nb_philo * 2);
    }
}



void    *routine(t_philo *philo)
{
    if (philo->num % 2 == 0)
        usleep(philo->data->time_to_eat / 10);
    while (!is_dead(philo) && philo->data->max_ate)
    {
        printf("pick left fork");
        pthread_mutex_lock(&philo->data->fork[philo->num]);   // lock left fork, if left fork already taken, thread will wait
        printf("pick right fork");
        pthread_mutex_lock(&philo->data->fork[(philo->num + 1) % philo->num]); // lock right fork
        printf("philosopher is eating");
        pthread_mutex_lock(&philo->data->meal);
        philo->last_time_he_eat = timestamp();  // get time of the last time he eat
        ft_sleep(philo->data->time_to_eat, philo->data);  // philo is eating time to eat
        philo->eat_time++;
        pthread_mutex_unlock(&philo->data->meal);  // unlock meal
        pthread_mutex_unlock(&philo->data->fork[philo->num]); // unlock left fork
        pthread_mutex_unlock(&philo->data->fork[(philo->num + 1) % philo->num]); // unlock right fork
        printf("philosopher finish eating");
        printf("philosopher is sleeping");
        ft_sleep(philo->data->time_to_sleep, philo->data);  // philo is sleeping time to sleep
        printf("philosopher is thinking"); // philo is thinking
    }
    return (0);
}

  


int is_dead(t_philo *philo)
{
    int i;

    i = -1;
    while (++i < (int)philo->data->nb_philo)
    {
        if (timestamp() - philo->last_time_he_eat >= philo->data->time_to_die)
        {
            printf("philo is dead");
            philo->data->stop = 1;
            return (0);
        }
    }
    return (1);
}
