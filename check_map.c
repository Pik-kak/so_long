/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:55:28 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/10 15:19:53 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_size(t_game *game, char **map)
{
	int	i;

	i = 0;
	game->window_l = ft_strlen(map[0]) * 32;
	while (map[i])
		i++;
	game->window_h = i * 32;
}

void	check_characters(t_map *map)
{
	int	i;
	int	ii;

	i = 0;
	ii = 0;
	while (map->plan[i] != NULL)
	{
		while (map->plan[i][ii] != '\0')
		{
			if (map->plan[i][ii] == 'E')
				map->exit_count++;
			if (map->plan[i][ii] == 'P')
				map->player_count++;
			if (map->plan[i][ii] == 'C')
				map->collec_count++;
			if (map->plan[i][ii] != '0' && map->plan[i][ii] != '1' && \
				map->plan[i][ii] != 'E' && map->plan[i][ii] != 'P' && \
				map->plan[i][ii] != 'C')
				error_map("Map not valid", map);
			ii++;
		}
		i++;
		ii = 0;
	}
}

void	check_shape_and_walls(t_map *map)
{
	int	i;

	i = 1;
	while (map->plan[i])
	{
		if (map->length != (int)ft_strlen_mod(map->plan[i]))
			error_map("Map not valid", map);
		i++;
	}
	i = 0;
	while (i < map->length)
	{
		if (map->plan[0][i] != '1' || map->plan[map->height - 1][i] != '1')
			error_map("Hole in the wall", map);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		if (map->plan[i][0] != '1' || map->plan[i][map->length - 1] != '1')
			error_map("Hole in the wall", map);
		i++;
	}
}

char	**check_file_and_read(t_map *map)
{
	char	*line;
	char	*all_lines;
	int		fd;

	line = ("");
	all_lines = ft_strdup("");
	fd = open(map->name, O_RDONLY);
	if (fd < 0)
		error("Error opening file");
	while (line)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[0] == '\n')
		{
			error("Map not valid");
			free(all_lines);
		}
		all_lines = ft_strjoin(all_lines, line);
		free(line);
	}
	free(line);
	close(fd);
	return (ft_split(all_lines, '\n'));
}

void	check_map(t_map *map)
{
	map->plan = check_file_and_read(map);
	check_shape_and_walls(map);
	check_characters(map);
	if (map->exit_count != 1 || map->player_count != 1 || map->collec_count < 1)
		error_map("Wrong amount of players/exits/collectables", map);
	flood_fill(map);
}
