/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:48:01 by zdevove           #+#    #+#             */
/*   Updated: 2023/01/29 18:20:58 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_max_column(t_data *data)
{
	int	i;

	i = 0;
	while (data->matrix[0][i] != '\n')
		i++;
	data->nb_column = i;
}

void	center_player_height(t_data *data)
{
	if (data->p_i < 16 || data->nb_line < 32)
	{
		data->center->idx_up = 0;
		if (data->nb_line < 32)
			data->center->idx_down = data->nb_line - 1;
		else
			data->center->idx_down = 31;
	}
	else if (data->p_i > (data->nb_line - 17))
	{
		data->center->idx_up = data->nb_line - 32;
		data->center->idx_down = data->nb_line - 1;
	}
	else
	{
		data->center->idx_up = data->p_i - 16;
		data->center->idx_down = data->p_i + 15;
	}
}

void	center_player_width(t_data *data)
{
	if (data->p_j < 16 || data->nb_column < 32)
	{
		data->center->idx_left = 0;
		if (data->nb_column < 32)
			data->center->idx_right = data->nb_column - 1;
		else
			data->center->idx_right = 31;
	}
	else if (data->p_j > (data->nb_column -17))
	{
		data->center->idx_left = data->nb_column - 32;
		data->center->idx_right = data->nb_column - 1;
	}
	else
	{
		data->center->idx_left = data->p_j - 16;
		data->center->idx_right = data->p_j + 15;
	}
}

void	ft_create_map(t_data *data)
{
	center_player_height(data);
	center_player_width(data);
	put_center_player_on_window(data);
}

void	put_center_player_on_window(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i <= data->center->idx_down - data->center->idx_up)
	{
		j = 0;
		while (j <= data->center->idx_right - data->center->idx_left)
		{
			mlx_put_image_to_window(data->mlx, data->win, \
					ft_create_img(data, data->matrix[data->center->idx_up + i] \
			[data->center->idx_left + j]), j * 32, i * 32);
			j++;
		}
		i++;
	}
}
