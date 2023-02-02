/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:48:38 by zdevove           #+#    #+#             */
/*   Updated: 2023/02/02 11:46:54 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void    free_all(t_data *data)
{
    int i;

    i = data->nb_philo + 1;
    while (i--)
        if (data->fork[i])
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
            return (ft_putendl_fd("Invalid arguments", 2), 0);
        data = malloc(sizeof(t_data));
        if (!data)
            return (0);
        if (!data_init(data))
            return (0);
        if (!philo_init(data))
            return (free_all(data), 0);
        free_all(data);
    }
    return (0);
}


