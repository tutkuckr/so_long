/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:27:46 by tcakir-y          #+#    #+#             */
/*   Updated: 2025/03/25 16:05:59 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include "libft.h"
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE 70
# define UP      119
# define DOWN    115
# define LEFT    97
# define RIGHT   100
# define ESC     65307
# define ARROW_UP 65362
# define ARROW_DOWN 65364
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img_data;

typedef struct s_mlx_data
{
	t_img_data	bg;
	t_img_data	col;
	t_img_data	pl;
	t_img_data	exit;
	t_img_data	en;
	t_img_data	wall;
	void		*mlx;
	void		*win;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_mlx_data;

typedef struct s_map_variables
{
	char		**map;
	int			player;
	int			exit;
	int			collectible;
	int			collected;
	int			x;
	int			y;
	int			row_amount;
	int			col_amount;
	int			p_l[2];
	int			e_l[2];
	int			x_l[2];
	int			width;
	int			height;
	int			movement;
	t_mlx_data	*data;
}				t_map_vars;

// main.c
void	error(int error_code);
void	error_messages(const char **error_messages);

// check_map.c
void	check_map(t_map_vars *vars);
void	check_map_variables(t_map_vars *var, int x, int y);
void	check_if_rectangular(t_map_vars *vars);
void	check_ones(t_map_vars *vars);
void	check_map_name(char *map_name);

// check_valid_path.c
void	dfs(t_map_vars	*var, int row, int col);
void	copy_map(t_map_vars *temp, t_map_vars *vars);
int		check_visited(t_map_vars *vars);
void	check_valid_path(t_map_vars *vars);

// ft_free.c
void	ft_free_map(t_map_vars *vars);
void	ft_free_everything(t_map_vars *var, int mlx);

// map_read.c
int		open_file(char *map_name);
void	set_row_col(char *map_name, t_map_vars *vars);
void	map_read(char *map_name, t_map_vars *vars);

// mlx_func.c
int		close_window(t_map_vars *vars);
int		key_hook(int keycode, t_map_vars *var);
void	game_init(t_map_vars *var);

// mlx_utils.c
char	*filename(int val);
void	load_xpm_files(t_map_vars *var);
void	load_xpm(t_map_vars *v, t_img_data *xpm_arr, int i);
void	xpm_to_window(t_map_vars *var, int y, int x);
void	pixels_on_screen(t_map_vars *var);

// movements.c
int		is_valid_move_pl(int keycode, t_map_vars *var);
int		is_valid_move_en(t_map_vars *var, int movement);
void	update_player_loc(t_map_vars *var, int x, int y);
void	update_enemy_loc(t_map_vars *var, int x, int y);
void	counter(t_map_vars *var);

// enemy.c
int		enemy_movement(t_map_vars *var);

#endif
// #ifdef __APPLE__  // macOS keycodes
// 	# define UP      13
// 	# define DOWN    1
// 	# define LEFT    0
// 	# define RIGHT   2
// 	# define ESC     53
// 	# define ARROW_UP 126
// 	# define ARROW_DOWN 125
// 	# define ARROW_LEFT 123
// 	# define ARROW_RIGHT 124
// #else  // Linux keycodes
// 	# define UP      119
// 	# define DOWN    115
// 	# define LEFT    97
// 	# define RIGHT   100
// 	# define ESC     65307
// 	# define ARROW_UP 65362
// 	# define ARROW_DOWN 65364
// 	# define ARROW_LEFT 65361
// 	# define ARROW_RIGHT 65363
// #endif