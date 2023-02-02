/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:42:24 by zdevove           #+#    #+#             */
/*   Updated: 2023/02/02 12:01:32 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

unsigned long timestamp(unsigned long time, t_philo *philo)
{
    unsigned long   start = get_time();
    while (!data->stop)
    {
        if (get_time() - start >= time)
            break;
        usleep(data->nb_philo * 2);
    }
}



void    *routine(t_philo philo)
{
    pthread_t   tmp;
    unsigned long   time;

    time = gettimeoftheday
    if (philo->num % 2 == 0)
        usleep(philo->data->time_eat / 10);
    while (!is_dead(philo) && data->max_ate)
    {
        printf("pick left fork");
        pthread_mutex_lock(&data->fork[i], 0);   // lock left fork, if left fork already taken, thread will wait
        if (compare time)   // if waited to long, die
        
        printf("pick right fork");
        pthread_mutex_lock(&data->fork[(i + 1) % i], 0); // lock right spoon
        if (compare time)   // if waited to long, die

        pthread_mutex_lock(&data->meal);
        printf("philosopher is eating");
        usleep time to eat  // philo is eating
        
        
        philo->ate_time++;
        pthread_mutex_unlock(&data->meal);
        pthread_mutex_unlock(&data->fork[i], 0) // unlock left fork
        pthread_mutex_unlock(&data->fork[(i + 1) % i]) // unlock right fork
        printf("philosopher finish eating")
        
        printf("philosopher is thinking")
        usleep time to sleep // philo is sleeping
        // stop
    }
    return (0);
}

int is_eating()
{
       
}

    // printf("%d %d has taken a fork\n")
    // if // didnt eat for ttd ms, then die
    // printf("%d %d is eating\n")
    // printf("%d %d is sleeping\n")
    // printf("%d %d is thinking\n")
    


int is_dead(t_philo *philo, int nb)
{
    pthread_mutex_lock(&philo->data->dead)
    if (nb)
        philo->data->stop = 1;
    if (philo->data->stop)
        return (pthread_mutex_unlock(&philo->data->dead), 1);
    return (pthread_mutex_unlock(&philo->data->dead), 0);
    
}

void    *check_death(t_philo philo)
{
    
}
