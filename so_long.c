/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:53:30 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/10 15:16:13 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_measurements(t_map *map)
{
	int		fd;
	char	*line;

	fd = open(map->name, O_RDONLY);
	if (fd == -1)
		error("Error opening file");
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		error("No map?");
	}
	map->length = ft_strlen_mod(line);
	while (line)
	{
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	init_game(t_map *map, t_game *game)
{
	game->moves_count = 0;
	game->game_map = map->plan;
	game->collec = map->collec_count;
	game->collec_count = 0;
	game->mlx = mlx_init(game->window_l, game->window_h, "so_long", true);
	if (!game->mlx)
		error(mlx_strerror(mlx_errno));
	get_textures(game);
	get_images(game);
	draw_map(map, game, game->imag);
	mlx_key_hook(game->mlx, &input_hook, game);
	mlx_loop(game->mlx);
	free_map(map->plan);
	free(game->textrs);
	free(game->imag);
}

int	check_file_type(t_map *map)
{
	char			*file_name;
	char			*file_type;
	unsigned int	i;

	i = 0;
	file_type = ".ber";
	file_name = ft_strrchr(map->name, '.');
	if (!file_name)
		return (1);
	while (file_name[i] != '\0' && file_type[i] == file_name[i])
		i++;
	return (file_name[i] - file_type[i]);
}

void	init_map(t_map *map, char *name)
{
	map->name = name;
	if (check_file_type(map) != 0)
		error("Wrong file type");
	map->exit_count = 0;
	map->player_count = 0;
	map->collec_count = 0;
	map->height = 0;
	map->length = 0;
	get_measurements(map);
	map->player.x = 0;
	map->player.y = 0;
}

int	main(int argc, char *argv[])
{
	t_map	map;
	t_game	game;

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	if (argc == 2)
	{
		init_map(&map, argv[1]);
		check_map(&map);
		map_size(&game, map.plan);
		init_game(&map, &game);
	}
	else
		error("Wrong number of arguments");
	mlx_terminate(game.mlx);
}
