/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:19:10 by sbelabba          #+#    #+#             */
/*   Updated: 2023/05/24 18:19:11 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_dir_start(t_game *game)
{
	game->player.dirx = 0;
	game->player.diry = -1;
	game->player.planex = 0.66;
	game->player.planey = 0;
	if (game->map[game->player.x] && game->map[game->player.x][game->player.y] == 'W')
	{
		game->player.dirx = -1;
		game->player.diry = 0;
		game->player.planex = 0;
		game->player.planey = -0.66;
	}
	if (game->map[game->player.x] && game->map[game->player.x][game->player.y] == 'E')
	{
		game->player.dirx = 1;
		game->player.diry = 0;
		game->player.planex = 0;
		game->player.planey = 0.66;
	}
	if (game->map[game->player.x] && game->map[game->player.x][game->player.y] == 'S')
	{
		game->player.dirx = 0;
		game->player.diry = 1;
		game->player.planex = -0.66;
		game->player.planey = 0;
	}
}

void	set_screen(t_game *game)
{
	game->screen.height = 720;
	game->screen.length = 1480;
}

double	find_x(char **map, t_game *img)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] == '0' || map[i][j] && map[i][j] == '1' || map[i][j] && map[i][j] == ' ')
			j++;
		if (map[i][j] && map[i][j] != '0' && map[i][j] && map[i][j] != '1' && map[i][j] && map[i][j] != ' ')
			return (j + 0.5);
		i++;
	}
	return (0);
}

double	find_y(char **map, t_game *img)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] == '0' || map[i][j] && map[i][j] == '1' || map[i][j] && map[i][j] == ' ')
			j++;
		if (map[i][j] && map[i][j] != '0' && map[i][j] && map[i][j] != '1' && map[i][j] && map[i][j] != ' ')
			return (i + 0.5);
		i++;
	}
	return (0);
}
