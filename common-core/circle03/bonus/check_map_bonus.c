/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:21:06 by zdevove           #+#    #+#             */
/*   Updated: 2023/01/29 18:14:06 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_copy(char **matrix)
{
	int	i;
	int	j;

	i = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j] != '\0')
		{
			if (matrix[i][j] == 'E' || matrix[i][j] == 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_backtracking(char **matrix, t_data *data, int x, int y)
{
	if (!matrix || matrix[x][y] == '1' || matrix[x][y] == '2')
		return (0);
	else
	{
		if (matrix[x][y] == 'C')
			data->tmp_c--;
		matrix[x][y] = '1';
	}
	ft_backtracking(matrix, data, x, y - 1);
	ft_backtracking(matrix, data, x + 1, y);
	ft_backtracking(matrix, data, x, y + 1);
	ft_backtracking(matrix, data, x - 1, y);
	if (check_copy(matrix) && data->tmp_c == 0)
		return (1);
	return (0);
}

int	error_map(t_data *data)
{
	data->tmp_c = data->c;
	if (!copy_map(data))
		return (ft_putendl_fd("Error\nNo valid path", 2), 0);
	if (data->c < 1 || data->e != 1 || data->p != 1)
		return (ft_putendl_fd("Error\nMap need at least 1 	\
		collectible, 1 exit and 1 starting position", 2), 0);
	if (!check_rectangular(data))
		return (ft_putendl_fd("Error\nMap is not rectangular", 2), 0);
	return (1);
}

int	ft_check_map2(t_data *data, int i, int j)
{
	if (data->matrix[i][j] == 'C')
		data->c++;
	else if (data->matrix[i][j] == 'E')
		data->e++;
	else if (data->matrix[i][j] == 'P')
		data->p++;
	else if ((j == 0 || !data->matrix[i][j + 1] \
		|| (data->matrix[i][j + 1] == '\n') \
		|| i == 0 || i == data->nb_line - 1) \
		&& data->matrix[i][j] != '1')
		return (ft_putendl_fd("Error\n \
		Map is not surrounded by walls", 2), 0);
	else if (data->matrix[i][j] != '1' && data->matrix[i][j] != '0' \
		&& data->matrix[i][j] != '2')
		return (ft_putendl_fd("Error\nNot valid map", 2), 0);
	return (1);
}

int	ft_check_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nb_line)
	{
		j = 0;
		while (data->matrix[i][j] && data->matrix[i][j] != '\n')
		{
			if (!ft_check_map2(data, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (error_map(data));
}
