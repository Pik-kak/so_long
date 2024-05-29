/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:31:08 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/10 15:15:18 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_up(t_game *game)
{
	if (game->game_map[game->imag->player->instances->y / 32 - 1]
		[game->imag->player->instances->x / 32] != '1')
	{
		game->imag->player->instances->y -= MOVE;
		game->moves_count++;
		ft_printf("MOVES: %i\n", game->moves_count);
	}
}

void	move_down(t_game *game)
{
	if (game->game_map[game->imag->player->instances->y / 32 + 1]
		[game->imag->player->instances->x / 32] != '1')
	{
		game->imag->player->instances->y += MOVE;
		game->moves_count++;
		ft_printf("MOVES: %i\n", game->moves_count);
	}
}

void	move_right(t_game *game)
{
	if (game->game_map[game->imag->player->instances->y / 32]
		[game->imag->player->instances->x / 32 + 1] != '1')
	{
		game->imag->player->instances->x += MOVE;
		game->moves_count++;
		ft_printf("MOVES: %i\n", game->moves_count);
	}
}

void	move_left(t_game *game)
{
	if (game->game_map[game->imag->player->instances->y / 32]
		[game->imag->player->instances->x / 32 - 1] != '1')
	{
		game->imag->player->instances->x -= MOVE;
		game->moves_count++;
		ft_printf("MOVES: %i\n", game->moves_count);
	}
}

void	input_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if ((keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		|| (keydata.key == MLX_KEY_UP && keydata.action == MLX_RELEASE))
		move_up(game);
	if ((keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		|| (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_RELEASE))
		move_down(game);
	if ((keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		|| (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE))
		move_right(game);
	if ((keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		|| (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE))
		move_left(game);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(game->mlx);
	check_collectibles(game);
}
