/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:21:15 by zdevove           #+#    #+#             */
/*   Updated: 2023/01/29 18:03:11 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	position_p_in_map(t_data *data)
{
	if (data->p_j < 16)
		data->center->j_p = data->p_j;
	else if (data->center->idx_right < 32)
		data->center->j_p = data->p_j;
	else if (data->p_j > data->nb_column - 17)
		data->center->j_p = 32 - (data->nb_column - data->p_j);
	if (data->p_i < 16)
		data->center->i_p = data->p_i;
	else if (data->center->idx_down < 32)
		data->center->i_p = data->p_i;
	else if (data->p_i > data->nb_line - 17)
		data->center->i_p = 32 - (data->nb_line - data->p_i);
}

void	key_hook2(t_data *data)
{
	data->center->j_p = 16;
	data->center->i_p = 16;
	if (data->matrix[data->p_i][data->p_j] == 'E')
		data->flag_e = 1;
	if (data->matrix[data->p_i][data->p_j] == 'C')
		data->c--;
	if (data->matrix[data->p_i][data->p_j] == '2' || \
		(data->matrix[data->p_i][data->p_j] == 'E' && data->c == 0))
		return (free_all(data), exit(0));
	data->matrix[data->p_i][data->p_j] = 'P';
	position_p_in_map(data);
	ft_create_map(data);
	data->steps_count++;
	ft_print_step(data, 1);
	mlx_put_image_to_window(data->mlx, data->win, \
	data->img_player[data->idx_p], data->center->j_p * 32, \
	data->center->i_p * 32);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		return (free_all(data), exit (0), 0);
	if (check_next(keycode, data) == 1)
		return (0);
	data->matrix[data->p_i][data->p_j] = '0';
	if (data->flag_e)
	{
		data->matrix[data->p_i][data->p_j] = 'E';
		data->flag_e = 0;
	}
	if (keycode == 65361 || keycode == 97)
		data->p_j--;
	else if (keycode == 65364 || keycode == 115)
		data->p_i++;
	else if (keycode == 65363 || keycode == 100)
		data->p_j++;
	else if (keycode == 65362 || keycode == 119)
		data->p_i--;
	else
		return (0);
	key_hook2(data);
	return (0);
}

int	ft_sprite(t_data *data)
{
	data->counter++;
	if (data->idx_p > 3)
		data->idx_p = 0;
	if (data->idx_e > 7)
		data->idx_e = 0;
	if (data->counter > 6500)
	{
		position_p_in_map(data);
		ft_create_map(data);
		mlx_put_image_to_window(data->mlx, data->win, \
		data->img_player[data->idx_p], data->center->j_p * 32, \
		data->center->i_p * 32);
		ft_print_step(data, 0);
		data->counter = 0;
		data->idx_p++;
		data->idx_e++;
	}
	return (0);
}

void	ft_create_game(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, \
	data->img_player[data->idx_p], data->p_j * 32, data->p_i * 32);
	mlx_key_hook(data->win, key_hook, data);
	mlx_hook(data->win, 17, 0, free_hook, data);
	mlx_loop_hook(data->mlx, ft_sprite, data);
	mlx_loop(data->mlx);
}
