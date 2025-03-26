/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:43:16 by tcakir-y          #+#    #+#             */
/*   Updated: 2025/03/25 15:31:14 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// void	print_map(t_map_vars *var)
// {
// 	int i = 0;
// 	int j = 0;;

// 	while (var->map[i][j] != '\0')
// 	{
// 		j = 0;
// 		while (var->map[i][j] != '\0')
// 		{
// 			printf("%c", var->map[i][j]);
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	error_messages(const char **error_messages)
{
	error_messages[0] = "mlx error!";
	error_messages[1] = "Enter a valid map name!";
	error_messages[2] = "Cannot open the file!";
	error_messages[3] = "One of map characters is not correct(E,P,C)";
	error_messages[4] = "Invalid map character";
	error_messages[5] = "Map not rectangular";
	error_messages[6] = "Map not surrounded by 1s";
	error_messages[7] = "Collectible or Exit not reachable";
	error_messages[8] = "Malloc error!";
	error_messages[9] = "Map not initiated";
	error_messages[10] = "GNL";
	error_messages[11] = "mlx_init failed";
	error_messages[12] = "image reading has failed";
}

void	error(int error_code)
{
	const char	*error_msg[20];

	perror("Error\n");
	error_messages(error_msg);
	if (error_code >= 0 && error_code <= 12)
		ft_printf("%s", error_msg[error_code]);
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	t_map_vars	variables;

	if (argc != 2)
		error(1);
	check_map_name(argv[1]);
	ft_bzero(&variables, sizeof(variables));
	set_row_col(argv[1], &variables);
	map_read(argv[1], &variables);
	if (variables.map == NULL)
		return (ft_free_map(&variables), error(9), 1);
	check_map(&variables);
	game_init(&variables);
	return (0);
}

/*
* Check map file's name
* Set all bytes of variables to 0 & variables.map = NULL with bzero
* Read from the map file and parse into map_vars
* Check map variables
*/
