/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:05:32 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/10 15:15:38 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	error(const char *message)
{
	ft_printf("Error\n");
	ft_printf("%s\n", message);
	exit (1);
}

void	error_map(char *message, t_map *map)
{
	ft_printf("Error\n");
	ft_printf("%s\n", message);
	free_map(map->plan);
	exit (1);
}

size_t	ft_strlen_mod(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}
