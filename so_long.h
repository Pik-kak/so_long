/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:54:01 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/23 10:54:14 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "libft/libft.h"

# define BUFFER_SIZE 1000
# define MOVE		32

typedef struct s_textures
{
	mlx_texture_t	*floor;
	mlx_texture_t	*wall;
	mlx_texture_t	*collec;
	mlx_texture_t	*player;
	mlx_texture_t	*exit;
}						t_textures;

typedef struct s_images
{
	mlx_image_t	*floor;
	mlx_image_t	*wall;
	mlx_image_t	*collec;
	mlx_image_t	*player;
	mlx_image_t	*exit;
	char		*string;
}					t_images;

typedef struct s_position
{
	int	y;
	int	x;
}		t_position;

typedef struct s_map
{
	char				*name;
	int					height;
	int					length;
	char				**plan;
	int					exit_count;
	int					player_count;
	int					collec_count;
	struct s_position	player;
	struct s_position	exit;
}								t_map;

typedef struct s_game
{
	mlx_t				*mlx;
	struct s_textures	*textrs;
	struct s_images		*imag;
	mlx_image_t			*string_image;
	mlx_image_t			*floor;
	int					window_h;
	int					window_l;
	int					collec_count;
	int					collec;
	int					moves_count;
	char				**game_map;
}									t_game;

void	flood_fill(t_map *map);
void	check_map(t_map *map);
void	error(const char *message);
void	error_map(char *message, t_map *map);
size_t	ft_strlen_mod(const char *str);
void	free_map(char **map);
void	get_textures(t_game *game);
void	get_images(t_game *game);
void	draw_map(t_map *map, t_game *game, t_images *image);
void	map_size(t_game *game, char **map);
void	input_hook(mlx_key_data_t keydata, void *param);
void	check_collectibles(t_game *game);
#endif
