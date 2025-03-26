/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:35:34 by tcakir-y          #+#    #+#             */
/*   Updated: 2025/03/20 20:41:18 by tcakir-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// upper_bound = 3, lower_bound = 0
// rand() % (upper_bound - lower_bound + 1) + lower_bound;
int	enemy_movement(t_map_vars *var)
{
	int	movement;

	movement = rand() % 4;
	if (is_valid_move_en(var, movement) == 1)
	{
		if (movement == 0)
			update_enemy_loc(var, -1, 0);
		else if (movement == 1)
			update_enemy_loc(var, 1, 0);
		else if (movement == 2)
			update_enemy_loc(var, 0, 1);
		else if (movement == 3)
			update_enemy_loc(var, 0, -1);
	}
	else if (is_valid_move_en(var, movement) == -1)
	{
		ft_free_everything(var, 3);
		exit(0);
	}
	return (0);
}
