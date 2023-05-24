/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:53:26 by sbelabba          #+#    #+#             */
/*   Updated: 2023/05/24 17:53:27 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_hitbox_down(t_game *game)
{
	int	x;
	int	y;

	x = (int)(game->x - (game->player.dirx * 0.05));
	y = (int)(game->y - (game->player.diry * 0.05));
	if (game->map[y] && game->map[y][x] && game->map[y][x] == '1')
		return (0);
	return (1);
}

int	check_hitbox_up(t_game *game)
{
	int	x;
	int	y;

	x = (int)(game->x + (game->player.dirx * 0.05));
	y = (int)(game->y + (game->player.diry * 0.05));
	if (game->map[y] && game->map[y][x] && game->map[y][x] == '1')
		return (0);
	return (1);
}

void	move_up(t_game *game)
{
	if (check_hitbox_up(game))
	{
		game->x = game->x + (game->player.dirx * 0.05);
		game->y = game->y + (game->player.diry * 0.05);
	}
}

void	move_down(t_game *game)
{
	if (check_hitbox_down(game))
	{
		game->x = game->x - (game->player.dirx * 0.05);
		game->y = game->y - (game->player.diry * 0.05);
	}
}
