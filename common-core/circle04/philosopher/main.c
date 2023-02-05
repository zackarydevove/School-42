/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:48:38 by zdevove           #+#    #+#             */
/*   Updated: 2023/02/03 10:07:20 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void    free_all(t_data *data)
{
    int i;

    i = data->nb_philo + 1;
    while (i--)
        pthread_mutex_destroy(&data->fork[i - 1]);
    free(data->philo);
    free(data->fork);
    free(data);   
}

int main(int ac, char **av)
{
    t_data  *data;

    if (ac > 1 && ac < 7)
    {
        if (!check_av(av))
            return (printf("Invalid arguments\n"), 0);
        data = malloc(sizeof(t_data));
        if (!data)
            return (0);
        if (!data_init(data, av))
            return (printf("Error\nData_init error\n"), 0);
        if (!philo_init(data))
            return (free_all(data), printf("Error\nPhilo_init error\n"), 0);
        free_all(data);
    }
    else
        printf("Error\nNeed 4 or 5 arguments\n");
    return (0);
}
