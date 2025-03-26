/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:37:02 by tcakir-y          #+#    #+#             */
/*   Updated: 2025/03/20 18:48:13 by tcakir-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map(t_map_vars *vars)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	check_if_rectangular(vars);
	check_map_variables(vars, x, y);
	if (vars->player != 1 || vars->exit != 1 || vars->collectible == 0)
		return (ft_free_map(vars), error(3));
	check_ones(vars);
	check_valid_path(vars);
}

// Map must contain 1 E, at least 1 C, and 1 P to be valid.
void	check_map_variables(t_map_vars *var, int x, int y)
{
	while (x < var->row_amount)
	{
		y = 0;
		while (y < var->col_amount)
		{
			if (var->map[x][y] == 'P')
			{
				var->player++;
				ft_memcpy(var->p_l, (int []){x, y}, (sizeof(int) * 2));
			}
			else if (var->map[x][y] == 'E')
			{
				var->exit++;
				ft_memcpy(var->e_l, (int []){x, y}, (sizeof(int) * 2));
			}
			else if (var->map[x][y] == 'C')
				var->collectible++;
			else if (var->map[x][y] == 'X')
				ft_memcpy(var->x_l, (int []){x, y}, (sizeof(int) * 2));
			else if ((var->map[x][y] != '0') && (var->map[x][y] != '1'))
				return (ft_free_map(var), error(4));
			y++;
		}
		x++;
	}
}

// Each line should be the same size to be rectangular
void	check_if_rectangular(t_map_vars *vars)
{
	int	line_len;
	int	i;

	line_len = (int)ft_strlen(vars->map[0]);
	i = 1;
	while (vars->map[i] != NULL)
	{
		if ((int)ft_strlen(vars->map[i]) != line_len)
			return (ft_free_map(vars), error(5));
		i++;
	}
}

// Check if first and last line consists of ones
// Check if each line start & end with a one
void	check_ones(t_map_vars *vars)
{
	int	i;

	vars->col_amount = ft_strlen(vars->map[0]);
	i = 0;
	while (i < vars->col_amount)
	{
		if (vars->map[0][i] != '1' || vars->map[vars->row_amount - 1][i] != '1')
			return (ft_free_map(vars), error(6));
		i++;
	}
	i = 0;
	while (i < vars->row_amount)
	{
		if (vars->map[i][0] != '1' || vars->map[i][vars->col_amount - 1] != '1')
			return (ft_free_map(vars), error(6));
		i++;
	}
}

/// @brief checks if map name ends as ".ber"
/// @param map_name argv[1]
/// @return if it cannot find ".ber" returns 0
void	check_map_name(char *map_name)
{
	size_t	map_name_len;

	map_name_len = ft_strlen(map_name);
	if (map_name_len < 4
		|| ft_strncmp((map_name + map_name_len - 4), ".ber", 4) != 0)
		return (error(1));
}
