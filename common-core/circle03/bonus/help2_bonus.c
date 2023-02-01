/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:10:49 by zdevove           #+#    #+#             */
/*   Updated: 2023/01/30 16:17:38 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_next(int keycode, t_data *data)
{
	if (((keycode == 65361 || keycode == 97) \
		&& data->matrix[data->p_i][data->p_j - 1] == '1') \
			|| ((keycode == 65364 || keycode == 115) \
			&& data->matrix[data->p_i + 1][data->p_j] == '1') \
			|| ((keycode == 65363 || keycode == 100) \
			&& data->matrix[data->p_i][data->p_j + 1] == '1') \
			|| ((keycode == 65362 || keycode == 119) \
			&& data->matrix[data->p_i - 1][data->p_j] == '1'))
		return (1);
	return (0);
}

int	check_rectangular(t_data *data)
{
	int	i;
	int	j;

	if (data->nb_line == data->nb_column)
		return (0);
	i = 0;
	while (i < data->nb_line)
	{
		j = 0;
		while (data->matrix[i][j] && data->matrix[i][j] != '\n')
			j++;
		if (j != data->nb_column)
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_step(t_data *data, int flg)
{
	char	*ptr;
	char	*str;

	ptr = print_steps(data->steps_count);
	str = ft_strjoin("steps count: ", ptr);
	if (flg == 1)
		ft_putendl_fd(str, 1);
	mlx_string_put(data->mlx, data->win, 16, 16, 0xFFFFFF, str);
	free(str);
	free(ptr);
}

int	set_enemy_img(t_data *data)
{
	int	i;

	i = 0;
	while (i < 8)
		data->img_enemy[i++] = 0;
	i = 0;
	data->img_enemy[0] = mlx_xpm_file_to_image(data->mlx, \
	"images/enemy/enemy0.xpm", &data->width, &data->height);
	data->img_enemy[1] = mlx_xpm_file_to_image(data->mlx, \
	"images/enemy/enemy1.xpm", &data->width, &data->height);
	data->img_enemy[2] = mlx_xpm_file_to_image(data->mlx, \
	"images/enemy/enemy2.xpm", &data->width, &data->height);
	data->img_enemy[3] = mlx_xpm_file_to_image(data->mlx, \
	"images/enemy/enemy3.xpm", &data->width, &data->height);
	data->img_enemy[4] = mlx_xpm_file_to_image(data->mlx, \
	"images/enemy/enemy4.xpm", &data->width, &data->height);
	data->img_enemy[5] = mlx_xpm_file_to_image(data->mlx, \
	"images/enemy/enemy5.xpm", &data->width, &data->height);
	set_enemy_img2(data);
	while (i < 8)
		if (data->img_enemy[i++] == 0)
			return (0);
	return (1);
}

int	check_ber(char **av, t_data *data)
{
	char	*str;

	if (ft_strlen(av[1]) >= 4)
		str = ft_substr(av[1], ft_strlen(av[1]) - 4, 4);
	else
		return (free(data->center), free(data), \
		ft_putendl_fd("Error\nNot valid file", 2), 0);
	if (ft_strncmp(str, ".ber", 4) != 0)
		return (free(data->center), free(data), free(str), \
		ft_putendl_fd("Error\nNot .ber file", 2), 0);
	free(str);
	return (1);
}
