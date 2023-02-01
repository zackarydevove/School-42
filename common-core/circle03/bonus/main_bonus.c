/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:49:17 by zdevove           #+#    #+#             */
/*   Updated: 2023/01/30 16:14:02 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	**ft_malloc_matrix(t_data *data, char *map_path)
{
	char	**map;
	char	*line;
	int		i;
	int		fd;

	i = 0;
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (0);
	while (get_next_line(fd, &line))
	{
		check_line(line);
		free(line);
		i++;
	}
	if (i == 0)
		return (0);
	close(fd);
	data->nb_line = i;
	map = malloc((i + 1) * sizeof(char *));
	if (!map)
		return (0);
	return (map);
}

char	**ft_create_matrix(t_data *data, char *map_path)
{
	char	**map;
	int		i;
	int		fd;

	data->nb_line = 0;
	map = ft_malloc_matrix(data, map_path);
	if (map == 0)
		return (0);
	i = 0;
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (0);
	while (get_next_line(fd, &map[i]))
		i++;
	map[i] = "\0";
	if (!map[0])
	{
		free_matrix(map, data->nb_line);
		return (0);
	}
	return (map);
}

void	free_player_enemy_img(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->img_player[i] != 0)
			mlx_destroy_image(data->mlx, data->img_player[i]);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		if (data->img_enemy[i] != 0)
			mlx_destroy_image(data->mlx, data->img_enemy[i]);
		i++;
	}
}

void	free_all(t_data *data)
{
	free_matrix(data->matrix, data->nb_line);
	if (data->img_floor != 0)
		mlx_destroy_image(data->mlx, data->img_floor);
	if (data->img_wall != 0)
		mlx_destroy_image(data->mlx, data->img_wall);
	if (data->img_consumable != 0)
		mlx_destroy_image(data->mlx, data->img_consumable);
	if (data->img_exit != 0)
		mlx_destroy_image(data->mlx, data->img_exit);
	free_player_enemy_img(data);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->center);
	free(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (!malloc_data_center(&data))
		return (0);
	if (ac == 2)
	{
		if (!check_ber(av, data))
			return (0);
		if (!put_value_in_data(data, av[1]))
			return (0);
		if (!ft_check_map(data))
			return (free_all(data), 0);
		ft_create_map(data);
		ft_create_game(data);
	}
	else
		return (free(data->center), free(data), \
		ft_putendl_fd("Error\nNeed 1 argument only .ber map", 2), 0);
	return (free_all(data), 0);
}
