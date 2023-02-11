/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:00:58 by zdevove           #+#    #+#             */
/*   Updated: 2023/02/03 10:33:36 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H

# define PHILOSOPHER_H

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_data t_data;

typedef struct  s_philo {
    pthread_t pthread;
    int num;
    int eat_time;
    unsigned long last_time_he_eat;
    int lfork;
    int rfork;
    t_data *data;
}               t_philo;

typedef struct s_data {
    t_philo  *philo;
    pthread_mutex_t *fork;
    pthread_mutex_t meal;
    pthread_mutex_t writing;
    unsigned int nb_philo;   // nb de philosopher
    unsigned int time_to_die;    // time to die
    unsigned int time_to_eat;    // time to eat
    unsigned int time_to_sleep;    // time to sleep
    unsigned int nb_must_eat;   // nb of time each philo must eat (optionnal)
    unsigned int max_ate;
    unsigned int start_time;
    int stop;
}               t_data;


int check_av(char **av);
int data_init(t_data *data, char **av);
int mutex_init(t_data *data);
int philo_init(t_data *data);

void    *routine(void *params);
void    ft_sleep(unsigned long time_to_x, t_data *data);

int is_dead(t_philo *philo);
unsigned int timestamp(void);
int	ft_atoi(const char *str);

void    free_all(t_data *data);



#endif
