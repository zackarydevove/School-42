/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 11:12:17 by zdevove           #+#    #+#             */
/*   Updated: 2023/01/30 15:44:01 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	player_data(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->steps_count = 0;
	while (i < data->nb_line)
	{
		j = 0;
		while (data->matrix[i][j] && data->matrix[i][j] != '\n')
		{
			if (data->matrix[i][j] == 'P')
			{
				data->p_j = j;
				data->p_i = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	img_player(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
		data->img_player[i++] = 0;
	i = 0;
	data->img_player[0] = mlx_xpm_file_to_image(data->mlx, \
	"images/player1.xpm", &data->width, &data->height);
	data->img_player[1] = mlx_xpm_file_to_image(data->mlx, \
	"images/player2.xpm", &data->width, &data->height);
	data->img_player[2] = mlx_xpm_file_to_image(data->mlx, \
	"images/player3.xpm", &data->width, &data->height);
	data->img_player[3] = mlx_xpm_file_to_image(data->mlx, \
	"images/player4.xpm", &data->width, &data->height);
	while (i < 4)
		if (data->img_player[i++] == 0)
			return (0);
	return (1);
}

int	img_init(t_data *data)
{
	data->img_floor = 0;
	data->img_wall = 0;
	data->img_consumable = 0;
	data->img_exit = 0;
	data->img_floor = mlx_xpm_file_to_image(data->mlx, \
	"images/floor.xpm", &data->width, &data->height);
	if (data->img_floor == 0)
		return (0);
	data->img_wall = mlx_xpm_file_to_image(data->mlx, \
	"images/wall.xpm", &data->width, &data->height);
	if (data->img_wall == 0)
		return (0);
	data->img_consumable = mlx_xpm_file_to_image(data->mlx, \
	"images/consumable.xpm", &data->width, &data->height);
	if (data->img_consumable == 0)
		return (0);
	data->img_exit = mlx_xpm_file_to_image(data->mlx, \
	"images/exit.xpm", &data->width, &data->height);
	if (data->img_exit == 0)
		return (0);
	if (!img_player(data))
		return (0);
	return (1);
}

int	put_value_in_data(t_data *data, char *map_path)
{
	data->matrix = ft_create_matrix(data, map_path);
	if (data->matrix == 0)
		return (ft_putendl_fd("Error\nNot valid file", 2), \
		free(data->center), free(data), 0);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 32 * 32, 32 * 32, "SO_LONG");
	data->height = 0;
	data->width = 0;
	data->c = 0;
	data->e = 0;
	data->p = 0;
	data->flag_e = 0;
	data->counter = 0;
	data->idx_p = 0;
	data->idx_e = 0;
	if (!img_init(data) || !set_enemy_img(data))
		return (ft_putendl_fd("Error\nImage not valid", 2), free_all(data), 0);
	get_max_column(data);
	player_data(data);
	return (1);
}

int	malloc_data_center(t_data **data)
{
	(*data) = malloc(sizeof(t_data));
	if (!(*data))
		return (0);
	(*data)->center = malloc(sizeof(t_center));
	if (!(*data)->center)
		return (free((*data)), 0);
	(*data)->center->idx_down = 0;
	(*data)->center->idx_up = 0;
	(*data)->center->idx_left = 0;
	(*data)->center->idx_right = 0;
	return (1);
}
