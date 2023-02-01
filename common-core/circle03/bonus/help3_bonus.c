/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help3_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:09:46 by zdevove           #+#    #+#             */
/*   Updated: 2023/01/30 16:20:46 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	set_enemy_img2(t_data *data)
{
	data->img_enemy[6] = mlx_xpm_file_to_image(data->mlx, \
	"images/enemy/enemy6.xpm", &data->width, &data->height);
	data->img_enemy[7] = mlx_xpm_file_to_image(data->mlx, \
	"images/enemy/enemy7.xpm", &data->width, &data->height);
}

int	check_line(char *line)
{
	if (line[0] == '\n')
	{
		free(line);
		return (0);
	}
	return (1);
}
