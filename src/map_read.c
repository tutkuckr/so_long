/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:17:52 by tcakir-y          #+#    #+#             */
/*   Updated: 2025/03/20 17:35:44 by tcakir-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	open_file(char *map_name)
{
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		error(2);
	return (fd);
}

void	set_row_col(char *map_name, t_map_vars *vars)
{
	int		fd;
	char	*line_read;

	fd = open_file(map_name);
	line_read = get_next_line(fd);
	if (!line_read)
		return (close(fd), error(10));
	vars->col_amount = (int)ft_strlen(line_read) - 1;
	vars->row_amount = 0;
	while (line_read != NULL)
	{
		(vars->row_amount)++;
		free(line_read);
		line_read = get_next_line(fd);
	}
	free(line_read);
	close(fd);
}

void	map_read(char *map_name, t_map_vars *vars)
{
	char	*line_read;
	int		fd;
	int		i;

	fd = open_file(map_name);
	i = 0;
	line_read = get_next_line(fd);
	vars->map = malloc(sizeof(char *) * ((vars->row_amount) + 1));
	if (!vars->map)
		return (close(fd), error(8));
	while (line_read != NULL)
	{
		if (line_read[ft_strlen(line_read) - 1] == '\n')
			line_read[ft_strlen(line_read) - 1] = '\0';
		vars->map[i] = malloc(sizeof(char) * (ft_strlen(line_read) + 1));
		if (!vars->map[i])
			return (close(fd), ft_free_map(vars), error(8));
		ft_strlcpy(vars->map[i], line_read, ft_strlen(line_read) + 1);
		i++;
		free(line_read);
		line_read = get_next_line(fd);
	}
	vars->map[i] = NULL;
	free(line_read);
	close(fd);
}
