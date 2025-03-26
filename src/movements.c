/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:36:01 by tcakir-y          #+#    #+#             */
/*   Updated: 2025/03/25 15:35:38 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	counter(t_map_vars *var)
{
	char	*step;
	int		x;
	int		y;

	step = ft_itoa(var->movement);
	if (!step)
		return (ft_free_everything(var, 3));
	x = 10;
	y = 20;
	mlx_put_image_to_window(var->data->mlx,
		var->data->win, var->data->wall.img, 0, 0);
	mlx_string_put(var->data->mlx, var->data->win, x, y, 0xFFFFFF, step);
	free(step);
}

void	update_enemy_loc(t_map_vars *var, int x, int y)
{
	usleep(300000);
	var->map[var->x_l[0]][var->x_l[1]] = '0';
	mlx_put_image_to_window(var->data->mlx, var->data->win,
		var->data->bg.img, (TILE * var->x_l[1]), (TILE * var->x_l[0]));
	var->x_l[0] += x;
	var->x_l[1] += y;
	var->map[var->x_l[0]][var->x_l[1]] = 'X';
	mlx_put_image_to_window(var->data->mlx, var->data->win,
		var->data->en.img, (TILE * var->x_l[1]), (TILE * var->x_l[0]));
}

void	update_player_loc(t_map_vars *var, int x, int y)
{
	var->map[var->p_l[0]][var->p_l[1]] = '0';
	mlx_put_image_to_window(var->data->mlx, var->data->win,
		var->data->bg.img, (TILE * var->p_l[1]), (TILE * var->p_l[0]));
	var->p_l[0] += x;
	var->p_l[1] += y;
	var->map[var->p_l[0]][var->p_l[1]] = 'P';
	mlx_put_image_to_window(var->data->mlx, var->data->win,
		var->data->pl.img, (TILE * var->p_l[1]), (TILE * var->p_l[0]));
	ft_printf("%d\n", var->movement);
	counter(var);
	var->movement++;
}

int	is_valid_move_pl(int keycode, t_map_vars *var)
{
	int	x;
	int	y;

	x = var->p_l[0];
	y = var->p_l[1];
	if (keycode == UP || keycode == ARROW_UP)
		x--;
	else if (keycode == DOWN || keycode == ARROW_DOWN)
		x++;
	else if (keycode == RIGHT || keycode == ARROW_RIGHT)
		y++;
	else if (keycode == LEFT || keycode == ARROW_LEFT)
		y--;
	if (var->map[x][y] == 'C')
		var->collected++;
	else if (var->map[x][y] == '1')
		return (0);
	else if (var->map[x][y] == 'E' && var->collected != var->collectible)
		return (0);
	else if ((var->map[x][y] == 'E' && var->collected == var->collectible)
		|| var->map[x][y] == 'X')
		return (-1);
	return (1);
}

int	is_valid_move_en(t_map_vars *var, int movement)
{
	int	x;
	int	y;

	x = var->x_l[0];
	y = var->x_l[1];
	if (movement == 0)
		x--;
	else if (movement == 1)
		x++;
	else if (movement == 2)
		y++;
	else if (movement == 3)
		y--;
	if (var->map[x][y] == '1' || var->map[x][y] == 'C'
		|| var->map[x][y] == 'E')
		return (0);
	else if (var->map[x][y] == 'P')
		return (-1);
	return (1);
}
// if exit -> check if collectibles are collected 
// if coll -> update the amount collected and compare with total
