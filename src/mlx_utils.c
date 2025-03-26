/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:04:24 by tcakir-y          #+#    #+#             */
/*   Updated: 2025/03/25 15:32:32 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*filename(int val)
{
	char	*path[15];

	path[0] = "textures/bg.xpm";
	path[1] = "textures/wall.xpm";
	path[2] = "textures/player.xpm";
	path[3] = "textures/collectible.xpm";
	path[4] = "textures/exit.xpm";
	path[5] = "textures/enemy.xpm";
	return (path[val]);
}

/// @brief convert xpm to img, then get data addr
void	load_xpm_files(t_map_vars *var)
{
	t_img_data	*xpm_array[5];
	int			i;

	xpm_array[0] = &var->data->bg;
	xpm_array[1] = &var->data->wall;
	xpm_array[2] = &var->data->pl;
	xpm_array[3] = &var->data->col;
	xpm_array[4] = &var->data->exit;
	i = 0;
	while (i < 5)
	{
		load_xpm(var, xpm_array[i], i);
		i++;
	}
	if (!(var->x_l[0] == 0 && var->x_l[1] == 0))
		load_xpm(var, &var->data->en, 5);
	else
		var->data->en.img = NULL;
}

void	load_xpm(t_map_vars *v, t_img_data *xpm_arr, int i)
{
	xpm_arr->img = mlx_xpm_file_to_image(v->data->mlx,
			filename(i), &v->width, &v->height);
	if (!xpm_arr->img)
		return (ft_free_map(v), error(12));
	xpm_arr->addr = mlx_get_data_addr(xpm_arr->img, &xpm_arr->bits_per_pixel,
			&xpm_arr->line_length, &xpm_arr->endian);
}

void	xpm_to_window(t_map_vars *var, int y, int x)
{
	if (var->map[x][y] == '0')
		mlx_put_image_to_window(var->data->mlx, var->data->win,
			var->data->bg.img, (TILE * y), (TILE * x));
	else if (var->map[x][y] == '1')
		mlx_put_image_to_window(var->data->mlx, var->data->win,
			var->data->wall.img, (TILE * y), (TILE * x));
	else if (var->map[x][y] == 'P')
		mlx_put_image_to_window(var->data->mlx, var->data->win,
			var->data->pl.img, (TILE * y), (TILE * x));
	else if (var->map[x][y] == 'C')
		mlx_put_image_to_window(var->data->mlx, var->data->win,
			var->data->col.img, (TILE * y), (TILE * x));
	else if (var->map[x][y] == 'E')
		mlx_put_image_to_window(var->data->mlx, var->data->win,
			var->data->exit.img, (TILE * y), (TILE * x));
	else if (var->map[x][y] == 'X')
		mlx_put_image_to_window(var->data->mlx, var->data->win,
			var->data->en.img, (TILE * y), (TILE * x));
}

void	pixels_on_screen(t_map_vars *var)
{
	int	y;
	int	x;

	y = 0;
	while (y < var->col_amount)
	{
		x = 0;
		while (x < var->row_amount)
		{
			xpm_to_window(var, y, x);
			x++;
		}
		y++;
	}
}
