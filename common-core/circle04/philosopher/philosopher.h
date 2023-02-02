/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:00:58 by zdevove           #+#    #+#             */
/*   Updated: 2023/02/02 12:01:42 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H

# define PHILOSOPHER_H

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct  s_philo {
    pthread_t pthread;
    int num;
    int ate_time;
    t_data *data;
}               t_philo;

typedef struct s_data {
    t_philo  *philo;
    pthread_mutex_t *fork;
    int nb_philo;   // nb de philosopher
    int time_to_die;    // time to die
    int time_to_eat;    // time to eat
    int time_to_sleep;    // time to sleep
    int nb_must_eat;   // nb of time each philo must eat (optionnal)
    int philo_eat;
    int stop;
    int dead;
}               t_data;


int	ft_atoi(const char *str);

#endif

