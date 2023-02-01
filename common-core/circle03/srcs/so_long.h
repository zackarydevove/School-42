/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:01:19 by zdevove           #+#    #+#             */
/*   Updated: 2023/01/30 16:14:43 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>

typedef struct s_center {
	int	idx_up;
	int	idx_down;
	int	idx_left;
	int	idx_right;
	int	j_p;
	int	i_p;
}		t_center;

typedef struct s_data {
	char		**matrix;
	void		*mlx;
	void		*win;
	void		*img_floor;
	void		*img_wall;
	void		*img_consumable;
	void		*img_player;
	void		*img_exit;
	int			c;
	int			e;
	int			p;
	int			height;
	int			width;
	int			nb_line;
	int			nb_column;
	int			p_j;
	int			p_i;
	int			steps_count;
	int			flag_e;
	int			tmp_c;
	t_center	*center;
}		t_data;

// Free

void	free_matrix(char **matrix, int len);
int		free_hook(t_data *data);
void	free_all(t_data *data);

// Init

int		put_value_in_data(t_data *data, char *map_path);
int		malloc_data_center(t_data **data);
char	**ft_create_matrix(t_data *data, char *map_path);
char	**ft_malloc_matrix(t_data *data, char *map_path);
int		img_init(t_data *data);
void	player_data(t_data *data);
int		check_line(char *line);

// Check_map

int		check_ber(char **av, t_data *data);
int		copy_map(t_data *data);
int		ft_check_map(t_data *data);
int		error_map(t_data *data);
int		ft_backtracking(char **matrix, t_data *data, int x, int y);
int		check_copy(char **matrix);
int		check_rectangular(t_data *data);

// Create_map

void	*ft_create_img(t_data *data, char c);
void	get_max_column(t_data *data);
void	center_player_width(t_data *data);
void	center_player_height(t_data *data);
void	ft_create_map(t_data *data);
void	put_center_player_on_window(t_data *data);

// Create_game

void	ft_create_game(t_data *data);
int		key_hook(int keycode, t_data *data);
void	key_hook2(t_data *data);
char	*print_steps(int n);
int		check_next(int keycode, t_data *data);
void	position_p_in_map(t_data *data);

#endif
