/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:34:54 by tcakir-y          #+#    #+#             */
/*   Updated: 2025/03/25 15:36:41 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/// @brief mark the cell as Visited, explore adjacent->top bottom left right
/// @param var copied map 
/// @param row current row
/// @param col current col
void	dfs(t_map_vars	*var, int row, int col)
{
	if (row < 0 || row >= var->row_amount || col < 0 || col >= var->col_amount
		|| var->map[row][col] == '1' || var->map[row][col] == 'V')
		return ;
	if (var->map[row][col] == 'E')
	{
		var->map[row][col] = 'R';
		return ;
	}
	var->map[row][col] = 'V';
	dfs(var, row - 1, col);
	dfs(var, row + 1, col);
	dfs(var, row, col - 1);
	dfs(var, row, col + 1);
}

void	copy_map(t_map_vars *temp, t_map_vars *vars)
{
	int		i;
	int		j;

	i = 0;
	temp->map = malloc(sizeof(char *) * ((vars->row_amount) + 1));
	if (!temp->map)
		return (ft_free_map(temp), error(8));
	while (i < vars->row_amount)
	{
		temp->map[i] = malloc(sizeof(char) * (vars->col_amount + 1));
		if (!temp->map[i])
			return (ft_free_map(temp), error(8));
		j = 0;
		while (vars->map[i][j])
		{
			temp->map[i][j] = vars->map[i][j];
			j++;
		}
		temp->map[i][j] = '\0';
		i++;
	}
	temp->map[i] = NULL;
	temp->row_amount = vars->row_amount;
	temp->col_amount = vars->col_amount;
}

int	check_visited(t_map_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->row_amount)
	{
		j = 0;
		while (j < vars->col_amount && vars->map[i][j])
		{
			if (vars->map[i][j] == 'C' || vars->map[i][j] == 'E')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

// row & col -1(index) -1(outer wall) = -2
void	check_valid_path(t_map_vars *vars)
{
	t_map_vars	temp;
	int			row;
	int			col;

	row = vars->p_l[0];
	col = vars->p_l[1];
	ft_bzero(&temp, sizeof(temp));
	copy_map(&temp, vars);
	dfs(&temp, row, col);
	if (check_visited(&temp))
		return (ft_free_map(vars), ft_free_map(&temp), error(7));
	ft_free_map(&temp);
}
