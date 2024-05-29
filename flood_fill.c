/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:18:53 by pik-kak           #+#    #+#             */
/*   Updated: 2024/05/23 11:05:18 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood(t_map *map, t_position *player_pos, char **temp_map)
{
	struct s_position	newposition;

	if (player_pos->x < 0 || player_pos->x >= map->height || \
		player_pos->y < 0 || player_pos->y >= map->length || \
		(temp_map[player_pos->x][player_pos->y] != '0' && \
		temp_map[player_pos->x][player_pos->y] != 'C' && \
		temp_map[player_pos->x][player_pos->y] != 'E' && \
		temp_map[player_pos->x][player_pos->y] != 'P'))
		return ;
	temp_map[player_pos->x][player_pos->y] = 'F';
	newposition.x = player_pos->x - 1;
	newposition.y = player_pos->y;
	flood(map, &newposition, temp_map);
	newposition.x = player_pos->x + 1;
	newposition.y = player_pos->y;
	flood(map, &newposition, temp_map);
	newposition.x = player_pos->x;
	newposition.y = player_pos->y - 1;
	flood(map, &newposition, temp_map);
	newposition.x = player_pos->x;
	newposition.y = player_pos->y + 1;
	flood(map, &newposition, temp_map);
}

void	find_player_and_exit(t_map *map)
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
			{
				map->exit.x = i;
				map->exit.y = ii;
			}
			if (map->plan[i][ii] == 'P')
			{
				map->player.x = i;
				map->player.y = ii;
			}
			ii++;
		}
		i++;
		ii = 0;
	}
}

int	go_through_map(char **map, int length)
{
	int	i;
	int	ii;

	i = 0;
	ii = 0;
	while (i < length)
	{
		while (map[i][ii] != '\0')
		{
			if (map[i][ii] != '1' && map[i][ii] != 'F' && map[i][ii] != '0')
				return (1);
			ii++;
		}
		i++;
		ii = 0;
	}
	return (0);
}

char	**make_temp_map(t_map *map, char **temp)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(map->name, O_RDONLY);
	if (fd == -1)
		error_map("Error opening file", map);
	line = get_next_line(fd);
	if (!line)
		error_map("Reading error", map);
	temp = (char **)malloc((map->length + 1) * (map->height + 1));
	while (line)
	{
		if (line[map->length] == '\n')
			line[map->length] = '\0';
		temp[i] = line;
		line = get_next_line(fd);
		i++;
	}
	temp[i] = NULL;
	close(fd);
	free(line);
	return (temp);
}

void	flood_fill(t_map *map)
{
	char				**temp_map;
	struct s_position	*player_pos;

	find_player_and_exit(map);
	temp_map = NULL;
	player_pos = malloc(sizeof(struct s_position));
	temp_map = make_temp_map(map, temp_map);
	player_pos->x = map->player.x;
	player_pos->y = map->player.y;
	flood(map, player_pos, temp_map);
	free(player_pos);
	if (temp_map[map->exit.x][map->exit.y] != 'F' || \
		go_through_map(temp_map, map->height) == 1)
	{
		free_map(temp_map);
		error_map("No path to exit/collectables", map);
	}
	free_map(temp_map);
}
