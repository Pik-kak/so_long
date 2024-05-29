/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:14:42 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/06 13:52:59 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	remove_collectible(t_game *game)
{
	int	i;
	int	count;

	i = 0;
	count = game->collec;
	while (i < count)
	{
		if (((game->imag->collec->instances[i].y == \
			game->imag->player->instances->y) && \
			(game->imag->collec->instances[i].x == \
			game->imag->player->instances->x)) && \
			game->imag->collec->instances[i].enabled == true)
		{
			count--;
			game->imag->collec->instances[i].enabled = false;
			return ;
		}
		i++;
	}
}

void	check_collectibles(t_game *game)
{
	if (game->game_map[game->imag->player->instances->y / 32]
		[game->imag->player->instances->x / 32] == 'C')
	{
		remove_collectible(game);
		game->game_map[game->imag->player->instances->y / 32]
		[game->imag->player->instances->x / 32] = '0';
		game->collec_count++;
		if (game->collec_count == game->collec)
			game->imag->exit->instances->enabled = true;
	}
	if (game->game_map[game->imag->player->instances->y / 32]
		[game->imag->player->instances->x / 32] == 'E')
	{
		if (game->collec_count == game->collec)
			mlx_close_window(game->mlx);
	}
}
