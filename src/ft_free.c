/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:56:28 by tcakir-y          #+#    #+#             */
/*   Updated: 2025/03/25 12:08:09 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free_map(t_map_vars *vars)
{
	int	i;

	i = 0;
	if (vars->map == NULL)
		return ;
	while (vars->map[i])
	{
		free(vars->map[i]);
		i++;
	}
	free(vars->map);
	vars->map = NULL;
}

/*
mlx == 1 -> if var->data->mlx malloc fails
mlx == 2 -> when var->data->win malloc fails
mlx == 3 -> when ESC is pressed
 */
void	ft_free_everything(t_map_vars *var, int mlx)
{
	ft_free_map(var);
	if (mlx == 1)
	{
		free(var->data);
	}
	else if (mlx == 2)
	{
		mlx_destroy_display(var->data->mlx);
		free(var->data->mlx);
		free(var->data);
	}
	else if (mlx == 3)
	{
		mlx_destroy_window(var->data->mlx, var->data->win);
		mlx_destroy_image(var->data->mlx, var->data->bg.img);
		mlx_destroy_image(var->data->mlx, var->data->exit.img);
		mlx_destroy_image(var->data->mlx, var->data->wall.img);
		mlx_destroy_image(var->data->mlx, var->data->col.img);
		mlx_destroy_image(var->data->mlx, var->data->pl.img);
		if (!(var->x_l[0] == 0 && var->x_l[1] == 0))
			mlx_destroy_image(var->data->mlx, var->data->en.img);
		mlx_destroy_display(var->data->mlx);
		free(var->data->mlx);
		free(var->data);
	}
}
