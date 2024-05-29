/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:59:22 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/08 14:23:04 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_textures(t_game *game)
{
	game->textrs = ft_calloc(1, sizeof(struct s_textures));
	game->textrs->floor = mlx_load_png("./textures/grass.png");
	game->textrs->wall = mlx_load_png("./textures/hedge.png");
	game->textrs->collec = mlx_load_png("./textures/mushrooms.png");
	game->textrs->player = mlx_load_png("./textures/pippin.png");
	game->textrs->exit = mlx_load_png("./textures/hole.png");
}

void	get_images(t_game *game)
{
	game->imag = ft_calloc(1, sizeof(t_images));
	game->imag->floor = mlx_texture_to_image(game->mlx, game->textrs->floor);
	game->imag->wall = mlx_texture_to_image(game->mlx, game->textrs->wall);
	game->imag->collec = mlx_texture_to_image(game->mlx, game->textrs->collec);
	game->imag->player = mlx_texture_to_image(game->mlx, game->textrs->player);
	game->imag->exit = mlx_texture_to_image(game->mlx, game->textrs->exit);
	mlx_delete_texture(game->textrs->floor);
	mlx_delete_texture(game->textrs->wall);
	mlx_delete_texture(game->textrs->collec);
	mlx_delete_texture(game->textrs->player);
	mlx_delete_texture(game->textrs->exit);
}

void	draw_floor(t_map *map, t_game *game, t_images *image)
{
	int	x;
	int	y;

	y = 0;
	while (map->plan[y])
	{
		x = 0;
		while (map->plan[y][x])
		{
			mlx_image_to_window(game->mlx, image->floor, x * 32, y * 32);
			if (map->plan[y][x] == '1')
				mlx_image_to_window(game->mlx, image->wall, x * 32, y * 32);
			if (map->plan[y][x] == 'E')
				mlx_image_to_window(game->mlx, image->exit, x * 32, y * 32);
			x++;
		}
		y++;
	}
}

void	draw_map(t_map *map, t_game *game, t_images *image)
{
	int	x;
	int	y;

	draw_floor(map, game, image);
	y = 0;
	while (map->plan[y])
	{
		x = 0;
		while (map->plan[y][x])
		{
			if (map->plan[y][x] == 'C')
				mlx_image_to_window(game->mlx, image->collec, x * 32, y * 32);
			if (map->plan[y][x] == 'P')
				mlx_image_to_window(game->mlx, image->player, x * 32, y * 32);
			x++;
		}
		y++;
	}
}
