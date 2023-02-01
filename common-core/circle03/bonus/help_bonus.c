/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 11:20:12 by zdevove           #+#    #+#             */
/*   Updated: 2023/01/29 17:36:38 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	free_matrix(char **matrix, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	copy_map(t_data *data)
{
	char	**map;
	int		i;

	i = 0;
	map = malloc((data->nb_line + 1) * sizeof(char *));
	if (!map)
		return (0);
	while (i < data->nb_line)
	{
		map[i] = ft_strdup(data->matrix[i]);
		i++;
	}
	map[i] = 0;
	i = ft_backtracking(map, data, data->p_i, data->p_j);
	free_matrix(map, data->nb_line);
	if (!i)
		return (0);
	return (1);
}

int	free_hook(t_data *data)
{
	free_all(data);
	return (exit(0), 0);
}

char	*print_steps(int n)
{
	char	*str;
	int		nb;
	int		i;

	nb = n;
	i = 0;
	while (nb)
	{
		nb /= 10;
		i++;
	}
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (0);
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i--] = n % 10 + 48;
		n /= 10;
	}
	return (str);
}

void	*ft_create_img(t_data *data, char c)
{
	if (c == '0' || c == 'P')
		return (data->img_floor);
	else if (c == '1')
		return (data->img_wall);
	else if (c == '2')
		return (data->img_enemy[data->idx_e]);
	else if (c == 'C')
		return (data->img_consumable);
	else if (c == 'E')
		return (data->img_exit);
	ft_putendl_fd("Error\nNot a 0 1 C P or E", 2);
	return (NULL);
}
