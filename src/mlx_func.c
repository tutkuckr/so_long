/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:08:19 by tutku             #+#    #+#             */
/*   Updated: 2025/03/25 15:33:32 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(t_map_vars *vars)
{
	ft_free_everything(vars, 3);
	exit (0);
}

int	key_hook(int keycode, t_map_vars *var)
{
	if (is_valid_move_pl(keycode, var) == 1)
	{
		if (keycode == ESC)
		{
			ft_free_everything(var, 3);
			exit(0);
		}
		else if (keycode == UP || keycode == ARROW_UP)
			update_player_loc(var, -1, 0);
		else if (keycode == DOWN || keycode == ARROW_DOWN)
			update_player_loc(var, 1, 0);
		else if (keycode == RIGHT || keycode == ARROW_RIGHT)
			update_player_loc(var, 0, 1);
		else if (keycode == LEFT || keycode == ARROW_LEFT)
			update_player_loc(var, 0, -1);
	}
	else if (is_valid_move_pl(keycode, var) == -1)
	{
		ft_free_everything(var, 3);
		exit(0);
	}
	return (0);
}

//Ensure mlx_xpm_file_to_image() is called before mlx_get_data_addr()
void	game_init(t_map_vars *var)
{
	var->movement = 1;
	var->collected = 0;
	var->width = TILE * (var->col_amount);
	var->height = TILE * (var->row_amount);
	var->data = malloc (sizeof(t_mlx_data));
	if (!var->data)
		return (ft_free_map(var), error(8));
	var->data->mlx = mlx_init();
	if (!var->data->mlx)
		return (ft_free_everything(var, 1), error(11));
	var->data->win = mlx_new_window(var->data->mlx,
			var->width, var->height, "NOT_SO_LONG!");
	if (!var->data->win)
		return (ft_free_everything(var, 2), error(11));
	load_xpm_files(var);
	pixels_on_screen(var);
	mlx_key_hook(var->data->win, key_hook, var);
	mlx_hook(var->data->win, 17, 0, close_window, var);
	if (!(var->x_l[0] == 0 && var->x_l[1] == 0))
		mlx_loop_hook(var->data->mlx, enemy_movement, var);
	mlx_loop(var->data->mlx);
	ft_free_everything(var, 3);
}
