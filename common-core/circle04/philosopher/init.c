/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 07:49:18 by zdevove           #+#    #+#             */
/*   Updated: 2023/02/03 10:19:57 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


int check_av(char **av)
{
    int i;
    int j;

    i = 1;
    while (av[i])
    {
        j = 0;
        if (!ft_atoi(av[i]) || ft_atoi(av[i]) < 0)
            return (0);
        while (av[i][j])
        {
            if (av[i][j] < '0' && av[i][j] > '9')
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

int data_init(t_data *data, char **av) // init data info
{
    data->philo = malloc(data->nb_philo * sizeof(t_philo)); // create an array of philo data structure (thread)
    if (!data->philo)
        return (0);
    data->nb_philo = (unsigned int) ft_atoi(av[1]); // nb of philosopher and forks
    data->time_to_die = (unsigned int) ft_atoi(av[2]);  // time to die (in ms)
    data->time_to_eat = (unsigned int) ft_atoi(av[3]);  // time to eat (in ms)
    data->time_to_sleep = (unsigned int) ft_atoi(av[4]);  // time to sleep (in ms)
    if (av[5])
        data->nb_must_eat = (unsigned int) ft_atoi(av[5]);  // number of times each philosopher must eat (optional)
    else
        data->nb_must_eat = 0;
    data->max_ate = 0;
    printf("nb_p: %d\nttd: %d\ntte: %d\ntts: %d\n", data->nb_philo, data->time_to_die, data->time_to_eat, data->time_to_sleep);
    return (mutex_init(data));
}


int mutex_init(t_data *data) // create mutex fork
{
    int i;
    
    i = -1;
    data->fork = malloc(data->nb_philo * sizeof(pthread_mutex_t));
    if (!data->fork)
        return (free(data->philo), 0);
    while (++i < (int)data->nb_philo)
        if (pthread_mutex_init(&data->fork[i], 0))
            return (free_all(data), 0);
    if (pthread_mutex_init(&data->meal, 0))
        return (free_all(data), 0);
    if (pthread_mutex_init(&data->writing, 0))
        return (free_all(data), 0);
    return (1);
}

int philo_init(t_data *data)
{
    int i = -1;
    data->start_time = timestamp();
    while (++i < (int)data->nb_philo)    // create thread philo
    {
        data->philo[i].num = i + 1;    // son numero est i + 1
        data->philo[i].eat_time = 0;
        data->philo[i].data = data;
        data->philo[i].last_time_he_eat = timestamp();
        if (pthread_create(&data->philo[i].pthread, 0, routine, &data->philo[i])) // une fois tout initialise, lancer la routine   if != 0 return (0);
            return (0);
    }
    is_dead(data->philo);
    pthread_mutex_unlock(&data->writing);
    i = -1;
    while (i++ < (int)data->nb_philo)    // join thread
        if (pthread_join(data->philo[i].pthread, 0) != 0)
            return (0);
    return (1);
}
